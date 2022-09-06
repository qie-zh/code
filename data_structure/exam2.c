//判断两棵树是不是一样

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct TreeNode *Tree;
struct TreeNode{
    int Data;
    Tree Left,Right;
    int flag;
};

Tree NewNode(int D){
    Tree T;

    T = (Tree)malloc(sizeof(struct TreeNode));
    T->Data = D;
    T->Right = T->Left = NULL;
    T->flag = 0;

    return T;
}


Tree Insert(Tree T, int D){

    if(!T ){
        T = NewNode(D);
    }
    else{
        if(T->Data > D){
            T->Left = Insert(T->Left,D);
        }
        else{
            T->Right = Insert(T->Right,D);
        }
    }
    return T;

}

Tree MakeTree(int N){
    Tree T;
    int i,D;

    scanf("%d",&D);
    T = NewNode(D);
    for(i = 1; i < N; i++){
        scanf("%d",&D);
        T = Insert(T,D);
    }
    return T;

}


int Check(Tree T, int X){
    

    if(T->flag){                            //已被访问的元素
        if(T->Data > X) return Check(T->Left,X);
        else if(T->Data < X) return Check(T->Right,X);
        else return 0;
    }
    else{                                 //未被访问的元素
        if(T->Data == X){
            T->flag = 1;
            return 1;                       //返回值为1表示可以查找到节点
        }
        else return 0;
    }
}

int Judge(Tree T, int N){
    int D,flag = 0,test;

    scanf("%d",&D);                //判断头节点
    if(T->Data != D) flag = 1;      //不相同flag=1
    else T->flag = 1;
    test = D;

    for(int i = 1; i < N; i++){
        scanf("%d",&D);
        test = D;
        test = Check(T,D);
        if((!flag) && (!test)){
            flag = 1;
        }
    }

    if(flag) return 0;
    else return 1;
}

void ResetT( Tree T){
    if(T->Left) ResetT(T->Left);
    if(T->Right) ResetT(T->Right);
    T->flag = 0;
}

void FreeTree(Tree T){
    if(T->Left) FreeTree(T->Left);
    if(T->Right) FreeTree(T->Right);
    free(T);
}

void print_T(Tree T){
    if( T ){
        printf(" %d ",T->Data);
        print_T(T->Right);
        print_T(T->Left);
    }
}



void main(){
    int N,L;
    Tree T;
    
    scanf("%d",&N);          //节点个数

    while(N){
        scanf("%d",&L);      //需要判断的树的个数
        T = MakeTree(N);        //获取输入构造树

        for(int i = 0;i < L; i++){
            if(Judge(T,N)) {
                printf("yes\n");
            }
            else {
                printf("no\n");
            }
            ResetT(T);
        }

        FreeTree(T);
        scanf("%d",&N);
    }



}