/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key="";
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    par=NULL;
    left=NULL;  
    right=NULL;
}

int getht(SymNode* a){
    if(a==NULL){
        return -1;
    }
    else{
        return a->height;
    }
}
SymNode* SymNode::LeftLeftRotation(){
        SymNode* parent= par;
        SymNode* l=left;
        SymNode* r=left->right;
        SymNode* curr =left->par;
        l->right=curr;
        curr->par=l;
        curr->left=r;
        l->par=parent;
        if(r!=NULL){
        r->par=curr;
        }
        curr->height=1+max(getht(curr->left),getht(curr->right));
        l->height=1+max(getht(l->left),getht(l->right));
        return l;
}

SymNode* SymNode::RightRightRotation(){
        SymNode* parent= par;
        SymNode* l=right;
        SymNode* r=right->left;
        SymNode* curr =this;
        l->left=curr;
        curr->par=l;
        curr->right=r;
        l->par=parent;
        if(r!=NULL){
        r->par=curr;
        }
        curr->height=1+max(getht(curr->left),getht(curr->right));
        l->height=1+max(getht(l->left),getht(l->right));
        return l;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* parent=par;
    SymNode* l=left;
    SymNode* lr=left->right;
    SymNode* lrr=lr->right;
    SymNode* lrl=lr->left;
    SymNode* curr=left->par;
    lr->right=curr;
    curr->par=lr;
    lr->left=l;
    l->par=lr;
    curr->left=lrr;
    if(lrr!=NULL){
    lrr->par=curr;
    }
    l->right=lrl;
    if(lrl!=NULL){
    lrl->par=l;
    }
    lr->par=parent;
    curr->height=1+max(getht(curr->left),getht(curr->right));
    l->height=1+max(getht(l->left),getht(l->right));
    lr->height=1+max(getht(lr->left),getht(lr->right));
    return lr;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* parent=par;
    SymNode* r=right;
    SymNode* rl=right->left;
    SymNode* rll=rl->left;
    SymNode* rlr=rl->right;
    SymNode* curr=right->par;
    rl->left=curr;
    curr->par=rl;
    rl->right=r;
    r->par=rl;
    curr->right=rll;
    if(rll!=NULL){
    rll->par=curr;
    }
    r->left=rlr;
    if(rlr!=NULL){
    rlr->par=r;
    }
    rl->par=parent;
    curr->height=1+max(getht(curr->left),getht(curr->right));
    r->height=1+max(getht(r->left),getht(r->right));
    rl->height=1+max(getht(rl->left),getht(rl->right));
    return rl;
}

SymNode::~SymNode(){
    if(left!=NULL){
        delete left;
        left=NULL;
    }
    if(right!=NULL){
        delete right;
        right=NULL;
    }
    par=NULL;
}