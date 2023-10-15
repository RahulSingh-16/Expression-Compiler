/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
//Write your code below this line
void preorder(SymNode* root, vector<string>& vec){
    if (root==NULL) return;
    preorder(root->left, vec);
    vec.push_back(root->key);
    preorder(root->right, vec);
}

EPPCompiler::EPPCompiler(){
    memory_size=0;
    output_file="";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size=mem_limit;
    output_file=out_file;
    for (int i=0;i<mem_limit;i++){
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    std::fstream Object;
    Object.open(output_file,std::ios::out | std::ios::trunc);
    for(int i=0;i<code.size();i++){
        targ.parse(code[i]);
        ExprTreeNode* now=targ.expr_trees[targ.expr_trees.size()-1];
        if(now->left->type=="DEL"){
            vector<string> v=generate_targ_commands();
            write_to_file(v);
        }
        else if(now->left->type=="RET"){
            vector<string> v=generate_targ_commands();
            write_to_file(v);
            break;
        }
        else{
            ExprTreeNode* a=now->left;
            int i= targ.symtable->search(now->left->id);
            if (i==-2){
            int idx=least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->insert(a->id);
            targ.symtable->assign_address(a->id,idx);
            }
            vector<string> v=generate_targ_commands();
            write_to_file(v);
        }
        
    }
}

vector<string> cal(SymbolTable* symtable,ExprTreeNode* root){
    vector<string> result;
    if(root->type=="VAL"){
        result.push_back("PUSH "+std::to_string(root->num));
    }
    else if(root->type=="VAR"){
        result.push_back("PUSH mem["+std::to_string(symtable->search(root->id))+"]");
    }
    else{
        vector<string> l=cal(symtable,root->left);
        vector<string> r=cal(symtable,root->right);
        for (int i=0;i<r.size();i++){
            result.push_back(r[i]);
        }
        for (int i=0;i<l.size();i++){
            result.push_back(l[i]);
        }
        
        result.push_back(root->type);
    }
    return result;
}
vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* now=targ.expr_trees[targ.expr_trees.size()-1];
    vector<string> result;
    if(now->left->type=="DEL"){
            int i=targ.symtable->search(now->right->id);
            if(i!=-2){
            least_mem_loc.push_heap(i);
            targ.symtable->remove(now->right->id);
            result.push_back("DEL = mem["+std::to_string(i)+"]");
            }
    }
    else if(now->left->type=="RET"){
            result=cal(targ.symtable,now->right);
            result.push_back("RET = POP");
    }
    else{
        result=cal(targ.symtable,now->right);
         int i=targ.symtable->search(now->left->id);
         result.push_back("mem["+std::to_string(i)+"] = POP");  
    }
    
    return result;
}

void EPPCompiler::write_to_file(vector<string> commands){
std::fstream Object;
Object.open(output_file,std::ios::out | std::ios::app);
if(Object.is_open()){
    for(int i=0;i<commands.size();i++){
        Object << commands[i] <<std::endl;
    }
    Object.close();
}
else{
    
}
}
EPPCompiler::~EPPCompiler(){
  
}