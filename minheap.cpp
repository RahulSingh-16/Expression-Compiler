/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
//Write your code below this line
MinHeap::MinHeap(){
    size=0;
    root=NULL;
}

void MinHeap::push_heap(int num){
    HeapNode* newinsert;
    if(root==NULL){
        HeapNode* a= new HeapNode(num);
        newinsert=a;
        root=a;
        size++;
    }
    else{
        HeapNode** qarr= new HeapNode*[size];
        int f=0;
        int b=0;
        qarr[b++]=root;
        while(f!=b){
            HeapNode* a=qarr[f++];
            qarr[f-1]=NULL;
            if(a->left!=NULL and a->right!=NULL){
                qarr[b++]=a->left;
                qarr[b++]=a->right;
            }
            else{
                if(a->left==NULL){
                    HeapNode* newnode= new HeapNode(num);
                    newinsert=newnode;
                    a->left=newnode;
                    a->left->par=a;
                }
                else{
                    HeapNode* newnode= new HeapNode(num);
                    newinsert=newnode;
                    a->right=newnode;
                    a->right->par=a;
                }
                break;
            }
        }
        while(f!=b){
            qarr[f++]=NULL;
        }
        delete[] qarr;
        size++;
    }
    while(newinsert->par!=NULL){
        if(newinsert->par->val>newinsert->val){
            int temp= newinsert->val;
            newinsert->val=newinsert->par->val;
            newinsert->par->val=temp;
        }
        newinsert=newinsert->par;
    }
}

int MinHeap::get_min(){
    if(root==NULL){
        return -2;
    }
    else{
        return root->val;
    }
}

void heapifydown(HeapNode* root){
    if (root==NULL){
        return;
    }
    else{
        if(root->left==NULL and root->right==NULL){
            return;
        }
        else if(root->left!=NULL and root->right==NULL){
            if(root->val>root->left->val){
                int temp=root->left->val;
                root->left->val=root->val;
                root->val=temp;
            }
            return;
        }
        else{
            int l=root->left->val;
            int r=root->right->val;
            int cur=root->val;
            int min=cur;
            if(cur>l){
                min=l;
            }
            if(r<min){
                min=r;
            }
            if(min==cur){
                return;
            }
            else if(min==l){
                root->val=l;
                root->left->val=cur;
                heapifydown(root->left);
            }
            else{
                root->val=r;
                root->right->val=cur;
                heapifydown(root->right);
            }
        }
    }
}
void MinHeap::pop(){
    HeapNode* newinsert;
    if(root==NULL){

    }
    else{
        HeapNode** qarr= new HeapNode*[size];
        int f=0;
        int b=0;
        qarr[b++]=root;
        while(f!=b){
            HeapNode* a=qarr[f++];
            qarr[f-1]=NULL;
            if(f==b and a->left==NULL and a->right==NULL){
                newinsert=a;
            }
            else{
               if(a->left!=NULL){
                qarr[b++]=a->left;
                } 
                if(a->right!=NULL){
                qarr[b++]=a->right;
                }
            }  
        }
        delete[] qarr;
    }
    root->val=newinsert->val;
    if(newinsert==root){
        root=NULL;
    }
    else{
        if(newinsert->par->left==newinsert){
            newinsert->par->left=NULL;
        }
        else{
            newinsert->par->right=NULL;
        }
    }
    newinsert->par=NULL;
    delete newinsert;
    size--;
    heapifydown(root);
}
MinHeap::~MinHeap(){
    if(root!=NULL){
        delete root;
        root=NULL;
    }
}

// /* Do NOT add/remove any includes statements from this header file */
// /* unless EXPLICTLY clarified on Piazza. */
// #include "minheap.h"

// //Write your code below this line

// MinHeap::MinHeap(){

// }

// void MinHeap::push_heap(int num){

// }

// int MinHeap::get_min(){

// }

// void MinHeap::pop(){

// }

// MinHeap::~MinHeap(){

// }