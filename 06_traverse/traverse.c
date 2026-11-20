#include <stdio.h>
#include "traverse.h"
#include "lstack.h"
#include <stdlib.h>

#define MAX_NODES 100

static int *value;
static int *left;
static int *middle;
static int *right;

void SetBT(int* V,int* L,int* R){
     value=V;
     left=L;
     right=R;
     middle = NULL; 
}

void SetTT(int* V,int* L,int *M,int* R){
     value=V;
     left=L;
     middle=M;
     right=R;
}

void inorder(int root){
     if(left[root]!=0)inorder(left[root]);
     printf("%d ",value[root]);
     if(right[root]!=0)inorder(right[root]);
}

void preorder(int root){
     printf("%d ",value[root]);
     if(left[root]!=0)preorder(left[root]);
     if(right[root]!=0)preorder(right[root]);
}

void postorder(int root){
     if(left[root]!=0)postorder(left[root]);
     if(right[root]!=0)postorder(right[root]);
     printf("%d ",value[root]);
}

void levelorder(int root){
    if (root == 0) return;

    int queue[MAX_NODES];
    int head = 0;
    int tail = 0;
    
    queue[tail++] = root;

    while (head != tail) {
        int v = queue[head++];

        printf("%d ", value[v]);

        if (left[v] != 0) {
            if (tail >= MAX_NODES) {
                fprintf(stderr, "\nWarning: levelorder queue overflow!\n");
                return;
            }
            queue[tail++] = left[v];
        }

        if (right[v] != 0) {
            if (tail >= MAX_NODES) {
                fprintf(stderr, "\nWarning: levelorder queue overflow!\n");
                return;
            }
            queue[tail++] = right[v];
        }
    }
}

void inorderNR(int v){
     LStack S;
     S = CreateStack();
LT:  while(left[v]!=0){
           Push(v,S);
           v=left[v];
         }
NODE:printf("%d ",value[v]);
     if(right[v]!=0){
          v=right[v];
          goto LT;
          }
     if(!IsEmptyStack(S)){
          v=Top(S);
          Pop(S);
          goto NODE;
     }
     RemoveStack( &S );
}

void preorderNR(int v){
    if (v == 0) return;

    LStack S = CreateStack();
    Push(v, S);

    while (!IsEmptyStack(S)) {
        v = Top(S);
        Pop(S);

        printf("%d ", value[v]);

        if (right[v] != 0) {
            Push(right[v], S);
        }

        if (left[v] != 0) {
            Push(left[v], S);
        }
    }

    RemoveStack(&S);
}

void preorderTT(int root){
    if (root == 0) return;

    printf("%d ", value[root]);
    if (left[root] != 0) preorderTT(left[root]);
    if (middle[root] != 0) preorderTT(middle[root]);
    if (right[root] != 0) preorderTT(right[root]);
}

void postorderTT(int root){
    if (root == 0) return;

    if (left[root] != 0) postorderTT(left[root]);
    if (middle[root] != 0) postorderTT(middle[root]);
    if (right[root] != 0) postorderTT(right[root]);
    printf("%d ", value[root]);
}

void levelorderNQ(int root) { }
void printlevel(int index, int level) { }
void printlevelTT(int index, int level) { }
void MyPrintf(const char *format, ...) { }