/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */


#include "symtable.h"
//Write your code below this line
SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}
int getheight(SymNode* a){
    if(a==NULL){
        return -1;
    }
    else{
        return a->height;
    }
}
int getbalance(SymNode* a){
    if(a==NULL){
        return 0;
    }
    if(a->left==NULL and a->right==NULL){
        return 0;
    }
    else if(a->left==NULL and a->right!=NULL){
        return -1*(1+getheight(a->right));
    }
    else if(a->left!=NULL and a->right==NULL){
        return (1+getheight(a->left));
    }
    else{
        return getheight(a->left)-getheight(a->right);
    }
}
SymNode* ins( SymNode* root,string k){
    if(root==NULL){
        root= new SymNode(k);
        return root;
    }
    else{
        if(k<root->key){
            if(root->left==NULL){
                root->left= ins(root->left,k);
                root->left->par=root;
                root->height=max(root->height,1+root->left->height);
            }
            else{
                root->left=ins(root->left,k);
                root->left->par=root;
                root->height=max(root->height,1+root->left->height);
                
            }
        }
        else{
            if(root->right==NULL){
                root->right= ins(root->right,k);
                root->right->par=root;
                root->height=max(root->height,1+root->right->height);
            }
            else{
                root->right=ins(root->right,k);
                root->right->par=root;
                root->height=max(root->height,1+root->right->height);
            }
        }
        int a= getbalance(root);
        if(a>1){
        if(getheight(root->left->left)>getheight(root->left->right)){
            if(root->par==NULL){
                root=root->LeftLeftRotation();
            }
            else{
                if(root->par->left==root){
                    SymNode* temp=root->par;
                    root=root->LeftLeftRotation();
                    temp->left=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
                else{
                    SymNode* temp=root->par;
                    root=root->LeftLeftRotation();
                    temp->right=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
            }
        }
        else{
            if(root->par==NULL){
                root=root->LeftRightRotation();
            }
            else{
                if(root->par->left==root){
                    SymNode* temp=root->par;
                    root=root->LeftRightRotation();
                    temp->left=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
                else{
                    SymNode* temp=root->par;
                    root=root->LeftRightRotation();
                    temp->right=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
            }
        }
        SymNode* htup=root->par;
        while(htup!=NULL){
            htup->height=1+max(getheight(htup->left),getheight(htup->right));
            htup=htup->par;
        }
        }
        else if (a<-1){
           if(getheight(root->right->left)>getheight(root->right->right)){
            if(root->par==NULL){
                root=root->RightLeftRotation();
            }
            else{
                if(root->par->left==root){
                    SymNode* temp=root->par;
                    root=root->RightLeftRotation();
                    temp->left=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
                else{
                    SymNode* temp=root->par;
                    root=root->RightLeftRotation();
                    temp->right=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
            }
        }
        else{
            if(root->par==NULL){
                root=root->RightRightRotation();
            }
            else{
                if(root->par->left==root){
                    SymNode* temp=root->par;
                    root=root->RightRightRotation();
                    temp->left=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
                else{
                    SymNode* temp=root->par;
                    root=root->RightRightRotation();
                    temp->right=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
            }
        } 
        SymNode* htup=root->par;
        while(htup!=NULL){
            htup->height=1+max(getheight(htup->left),getheight(htup->right));
            htup=htup->par;
        }
        }
        else{
            
        }
        return root;
    }
}
void SymbolTable::insert(string k){
    root=ins(root,k);
    size++;

}

SymNode* del(SymNode* root,string k){
    if (root == NULL){
        
    }
    if (root->key > k) {
        root->left = del(root->left, k);
        root->height=1+max(getheight(root->left),getheight(root->right));
    }
    else if (root->key < k) {
        root->right = del(root->right, k);
        root->height=1+max(getheight(root->left),getheight(root->right));
    }
    else{
    if (root->left == NULL) {
        SymNode* temp = root->right;
        if(temp!=NULL){
        temp->par=root->par;
        }
        root->right=NULL;
        delete root;
        root=temp;
    }
    else if (root->right == NULL) {
        SymNode* temp = root->left;
        if (temp!=NULL){
        temp->par=root->par;
        }
        root->left=NULL;
        delete root;
        root=temp;
    }
    else {
        SymNode* Parent = root;
        SymNode* suc = root->right;
        while (suc->left != NULL){
            Parent = suc;
            suc = suc->left;
        }
        if (Parent != root){
            Parent->left = suc->right;
            if(suc->right!=NULL){
            suc->right->par=Parent;
            }
        }
        else{
            Parent->right = suc->right;
            if(suc->right!=NULL){
            suc->right->par=Parent;
            }
        }
        root->key = suc->key;
        root->address=suc->address;
        suc->left=NULL;
        suc->right=NULL;
        delete suc;
        while(Parent!=root){
            Parent->height=1+max(getheight(Parent->left),getheight(Parent->right));
            int a= getbalance(Parent);
            if(a>1){
            if(getheight(Parent->left->left)>getheight(Parent->left->right)){
                if(Parent->par==NULL){
                    Parent=Parent->LeftLeftRotation();
                }
                else{
                    if(Parent->par->left==Parent){
                        SymNode* temp= Parent->par;
                        Parent=Parent->LeftLeftRotation();
                        temp->left=Parent;
                        Parent->par->height=1+max(getheight(Parent->par->left),getheight(Parent->par->right));
                    }
                    else{
                        SymNode* temp= Parent->par;
                        Parent=Parent->LeftLeftRotation();
                        temp->right=Parent;
                        Parent->par->height=1+max(getheight(Parent->par->left),getheight(Parent->par->right));
                    }
                }
            }
            else{
                if(Parent->par==NULL){
                    Parent=Parent->LeftRightRotation();
                }
                else{
                    if(Parent->par->left==Parent){
                        SymNode* temp= Parent->par;
                        Parent=Parent->LeftRightRotation();
                        temp->left=Parent;
                        Parent->par->height=1+max(getheight(Parent->par->left),getheight(Parent->par->right));
                    }
                    else{
                        SymNode* temp= Parent->par;
                        Parent=Parent->LeftRightRotation();
                        temp->right=Parent;
                        Parent->par->height=1+max(getheight(Parent->par->left),getheight(Parent->par->right));
                    }
                }
            }
            SymNode* htup=Parent->par;
            while(htup!=NULL){
            htup->height=1+max(getheight(htup->left),getheight(htup->right));
            htup=htup->par;
            }
            }
            else if (a<-1){
            if(getheight(Parent->right->left)>getheight(Parent->right->right)){
                if(Parent->par==NULL){
                    Parent=Parent->RightLeftRotation();
                }
                else{
                    if(Parent->par->left==Parent){
                        SymNode* temp=Parent->par;
                        Parent=Parent->RightLeftRotation();
                        temp->left=Parent;
                        Parent->par->height=1+max(getheight(Parent->par->left),getheight(Parent->par->right));
                    }
                    else{
                        SymNode* temp=Parent->par;
                        Parent=Parent->RightLeftRotation();
                        temp->right=Parent;
                        Parent->par->height=1+max(getheight(Parent->par->left),getheight(Parent->par->right));
                    }
                }
            }
            else{
                if(Parent->par==NULL){
                    Parent=Parent->RightRightRotation();
                }
                else{
                    if(Parent->par->left==Parent){
                        SymNode* temp=Parent->par;
                        Parent=Parent->RightRightRotation();
                        temp->left=Parent;
                        Parent->par->height=1+max(getheight(Parent->par->left),getheight(Parent->par->right));
                    }
                    else{
                        SymNode* temp=Parent->par;
                        Parent=Parent->RightRightRotation();
                        temp->right=Parent;
                        Parent->par->height=1+max(getheight(Parent->par->left),getheight(Parent->par->right));
                    }
                }
            } 
            SymNode* htup=Parent->par;
            while(htup!=NULL){
            htup->height=1+max(getheight(htup->left),getheight(htup->right));
            htup=htup->par;
            }
            }
            else{
                
            }
            if(Parent->par==nullptr){

            }
            Parent=Parent->par;
        }
        root->height=1+max(getheight(root->left),getheight(root->right));
        
    }
    }
    int a= getbalance(root);
        if(a>1){
        if(getheight(root->left->left)>getheight(root->left->right)){
            if(root->par==NULL){
                root=root->LeftLeftRotation();
            }
            else{
                if(root->par->left==root){
                    SymNode* temp=root->par;
                    root=root->LeftLeftRotation();
                    temp->left=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
                else{
                    SymNode* temp=root->par;
                    root=root->LeftLeftRotation();
                    temp->right=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
            }
        }
        else{
            if(root->par==NULL){
                root=root->LeftRightRotation();
            }
            else{
                if(root->par->left==root){
                    SymNode* temp=root->par;
                    root=root->LeftRightRotation();
                    temp->left=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
                else{
                    SymNode* temp=root->par;
                    root=root->LeftRightRotation();
                    temp->right=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
            }
        }
        SymNode* htup=root->par;
        while(htup!=NULL){
            htup->height=1+max(getheight(htup->left),getheight(htup->right));
            htup=htup->par;
        }
        }
        else if (a<-1){
           if(getheight(root->right->left)>getheight(root->right->right)){
            if(root->par==NULL){
                root=root->RightLeftRotation();
            }
            else{
                if(root->par->left==root){
                    SymNode* temp=root->par;
                    root=root->RightLeftRotation();
                    temp->left=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
                else{
                    SymNode* temp=root->par;
                    root=root->RightLeftRotation();
                    temp->right=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
            }
        }
        else{
            if(root->par==NULL){
                root=root->RightRightRotation();
            }
            else{
                if(root->par->left==root){
                    SymNode* temp=root->par;
                    root=root->RightRightRotation();
                    temp->left=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
                else{
                    SymNode* temp=root->par;
                    root=root->RightRightRotation();
                    temp->right=root;
                    root->par->height=1+max(getheight(root->par->left),getheight(root->par->right));
                }
            }
        } 
        SymNode* htup=root->par;
        while(htup!=NULL){
            htup->height=1+max(getheight(htup->left),getheight(htup->right));
            htup=htup->par;
        }
        }
        else{
            
        }
        return root;
}

void SymbolTable::remove(string k){
    root=del(root,k);
    size--;
}

int sear(SymNode* root,string k){
if(root==NULL){
        return -2;
    }
    else{
        if(root->key==k){
            return root->address;
        }
        else if(root->key>k){
            return sear(root->left,k);
        }
        else{
            return sear(root->right,k);
        }
    }
}
int SymbolTable::search(string k){
    return sear(root,k);
}

void assign(SymNode*root,string k,int idx){
    if(root==NULL){
        return;
    }
    else{
        if(root->key==k){
            //cout<<"there";
            root->address=idx;
        }
        else if(root->key>k){
            //cout<<"here";
            assign(root->left,k,idx);
        }
        else{
            //cout<<"right";
            assign(root->right,k,idx);
        }
    }
}
 
void SymbolTable::assign_address(string k,int idx){
    assign(root,k,idx);
}
int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    if(root!=NULL){
        delete root;
        root=NULL;
    }
}