/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="";
    num=0;
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
  type=t;
  num=v;
  id="";
  left=NULL;
  right=NULL;
}

ExprTreeNode::~ExprTreeNode(){
    if(left!=NULL){
        delete left;
        left=NULL;
    }
    if(right!=NULL){
        delete right;
        right=NULL;
    }
}