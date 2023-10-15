/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"
//Write your code below this line
HeapNode::HeapNode(){
    val=0;
    par=NULL;
    left=NULL;
    right=NULL;
}

HeapNode::HeapNode(int _val){
    val= _val;
    par=NULL;
    left=NULL;
    right=NULL;
}

HeapNode::~HeapNode(){
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


// /* Do NOT add/remove any includes statements from this header file */
// /* unless EXPLICTLY clarified on Piazza. */
// #include "heapnode.h"

// //Write your code below this line

// HeapNode::HeapNode(){

// }

// HeapNode::HeapNode(int _val){

// }

// HeapNode::~HeapNode(){
  
// }