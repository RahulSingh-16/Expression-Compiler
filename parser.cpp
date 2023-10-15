///* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

#include "parser.h"
//Write your code below this line

Parser::Parser(){
    symtable= new SymbolTable();
}
string read(string k){
    if(k=="+"){
        return "ADD";
    }
    else if(k=="-"){
        return "SUB";
    }
    else if(k=="*"){
        return "MUL";
    }
    else if(k=="/"){
        return "DIV";
    }
    else if(k=="%"){
        return "MOD";
    }
    else{
        if(k[0]=='-'){
        bool is_val=true;
        for (int i=1;i<int(k.size());i++){
        int a= int(k[i])-int('0');
        if(a>9 or a<0){
            is_val=false;
            break;
        }
        }
        if(is_val){
            return "VAL";
        }
        else{
            return "VAR";
        }
        }
        else{
           bool is_val=true;
        for (int i=0;i<int(k.size());i++){
        int a= int(k[i])-int('0');
        if(a>9 or a<0){
            is_val=false;
            break;
        }
        }
        if(is_val){
            return "VAL";
        }
        else{
            return "VAR";
        } 
        }
    }
}
ExprTreeNode* par(vector<string> code,int start,int end){
    if(start>end){
        return NULL;
    }
    else if(start==end){
        string s=read(code[start]);
        if(s=="VAL"){
            int f=std::stoi(code[start]);
            ExprTreeNode* a=new ExprTreeNode(s,f);
            return a;
        }
        else{
            ExprTreeNode* a=new ExprTreeNode();
            a->type=s;
            a->id=code[start];
            return a;
        }
    }
    else {
        if(code[start+1]!="("){
            string rep=read(code[start+2]);
            ExprTreeNode* c=new ExprTreeNode();
            c->type=rep;
            string s=read(code[start+1]);
            if(s=="VAL"){
               int f=std::stoi(code[start+1]);
            ExprTreeNode* a=new ExprTreeNode(s,f);
            c->left=a;
            }
            else{
            ExprTreeNode* a=new ExprTreeNode();
            a->type=s;
            a->id=code[start+1];
            c->left=a;
            }
            
            c->right=par(code,start+3,end-1);
            return c;  
        }
        else{
            int count=0;
            int end_index;
            for (int i=start+2;i<end;i++){
                if(code[i]=="("){
                    count++;
                }
                else if(code[i]==")"){
                    count--;
                }
                if(count==-1){
                    end_index=i;
                    break;
                }
            }
            string rep=read(code[end_index+1]);
            ExprTreeNode* c=new ExprTreeNode();
            c->type=rep;
            c->left=par(code,start+1,end_index);
            c->right=par(code,end_index+2,end-1);
            return c;
        }
    }
}
void Parser::parse(vector<string> expression){
ExprTreeNode* r= new ExprTreeNode();
r->type="Assign";
r->left= new ExprTreeNode();
if(expression[0]=="del"){
    r->left->type="DEL";
}
else if(expression[0]=="ret"){
    r->left->type="RET";
}
else{
r->left->type="VAR";
r->left->id=expression[0];
}
r->right=par(expression,2,expression.size()-1);
expr_trees.push_back(r);
}

Parser::~Parser(){
    delete symtable;
    int n=expr_trees.size();
    for (int i=0;i<n;i++){
        ExprTreeNode* last= expr_trees[i];
        if(last!=NULL){
            delete last;
            last=NULL;
            } 
    }
    expr_trees.clear();  
}