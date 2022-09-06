#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxSize 5

typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode{
    int Data;
    BinTree Left;
    BinTree Right;
};


typedef struct SNode *Stack;
struct SNode{
    BinTree Data[MaxSize];
    int Top;
};


typedef struct QNode *Queue;
struct QNode
{
    BinTree Data[MaxSize];
    int rear;                  //指向最后一个元素
    int front;                  //指向第一个元素前
};


void PreOrderTraversal( BinTree BT){                      //递归先序遍历
    if(BT){
        printf("%d ",BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}

void InOrderTraversal( BinTree BT){                      //递归中序遍历
    if(BT){
        InOrderTraversal(BT->Left);
        printf("%d ",BT->Data);
        InOrderTraversal(BT->Right);
    }
}

void PostOrderTraversal( BinTree BT){                      //递归后序遍历
    if(BT){
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        printf("%d ",BT->Data);
    }
}

/*----------------------堆栈操作-------------------------*/
void Push(Stack Ptrs, BinTree BT){
    if(Ptrs->Top == MaxSize - 1){
        printf("fulled");
        return;
    }
    else{
        Ptrs->Data[++(Ptrs->Top)] = BT;
        return;
    }
}


BinTree Pop(Stack Ptrs){
    if(Ptrs->Top == -1){
        printf("empty");
        return NULL;
    }
    else{
        return (Ptrs->Data[(Ptrs->Top)--]);
    }
}

void InOrderTraversal_Recursion(BinTree BT){        //堆栈遍历
    BinTree T = BT;
    struct SNode s;
    Stack S = &s;

    while(T || (S->Top != -1) ){
        while(T){
            Push(S,T);
            //printf("%d ", T->Data);                //先序
            T = T->Left;
        }
        if(S->Top != -1){
            T = Pop(S);
            printf("%d ", T->Data);               //中序
            T = T->Right;
        }
    }

}

/*---------------------队列操作----------------------------*/
void AddQ(Queue PtrQ, BinTree BT){
    if((PtrQ->rear+1) % MaxSize == PtrQ->front){
        printf("fulled");
        return;
    }
    PtrQ->rear = (PtrQ->rear + 1) % MaxSize;
    PtrQ->Data[PtrQ->rear] = BT; 
}

BinTree DeleteQ(Queue PtrQ){
    if(PtrQ->front == PtrQ->rear){
        printf("empty");
        return NULL;
    }
    else{
        PtrQ->front = (PtrQ->front + 1) % MaxSize;
        return PtrQ->Data[PtrQ->front];
    }
}

void print_q(Queue PtrQ){
    int i;
    
    for(i = PtrQ->front + 1; (i % MaxSize) != PtrQ->rear + 1; i++){
        printf("%d ",PtrQ->Data[i]->Data);
    }

}


void LevelOrderTraversal( BinTree BT){             //层序遍历，输出一个节点入队左右节点
    BinTree T;

    struct QNode q;
    q.rear = -1;
    q.front = -1;
    Queue Q = &q;

    if( !BT ) return;
    AddQ(Q, BT);

    while( Q->front != Q->rear ){
        T = DeleteQ(Q);
        printf("%d ",T->Data);
        if(T->Left) AddQ(Q, T->Left);
        if(T->Right) AddQ(Q, T->Right);
    }
    print_q(Q);

}

/*-------------------树操作-------------------------------*/

Position Find( int x, BinTree BST){                      //二叉搜索树查找操作，左子树比根节点小，右子树比根节点大
    if( !BST){
        return NULL;
    }
    if( x > BST->Data){
        return Find(x, BST->Right);
    }
    else if( x < BST->Data){
        return Find( x, BST->Left);
    }
    else{
        return BST;
    }
}

Position FindMin(BinTree BST){                            //查找最小值，递归
    if( !BST){
        return NULL;
    }
    else if( !BST->Left){
        return BST;
    }
    else{
        return FindMin( BST->Left);
    }
}

Position FindMax( BinTree BST){                             //查找最大值，迭代
    if( BST){
        while(BST->Right) BST = BST->Right;
    }
    return BST;
}

BinTree Insert( int x, BinTree BST){
    if( !BST){
        BST = malloc(sizeof(struct TreeNode));
        BST->Data = x;
        BST->Left = BST->Right = NULL;
    }
    else{
        if( x < BST->Data){
            BST->Left = Insert(x, BST->Left);
        }
        else if( x > BST->Data){
            BST->Right = Insert(x, BST->Right);
        }
    }
    return BST;
}

BinTree DeleteTree(int x, BinTree BST){
    Position Tmp;
    if( !BST) printf("not found");
    else if( x < BST->Data) BST->Left = DeleteTree(x, BST->Left);
    else if( x > BST->Data) BST->Right = DeleteTree(x, BST->Right);

    else{                             //找到要删除的节点，并进行操作
        if(BST->Left && BST->Right){    //左右子树都不空
            Tmp = FindMin( BST->Right);
            BST->Data = Tmp->Data;
            BST->Right = DeleteTree(BST->Data, BST->Right);
        }
        else{
            Tmp = BST;
            if(!BST->Left){
                BST = BST->Right;
            }
            else if(!BST->Right){
                BST = BST->Left;
            }
            free(Tmp);
        }
    }
    return BST;
}

void main(){
    int Data[8] = {23,54,78,34,51,32,12,72};

    struct TreeNode b;
    b.Data = 50;
    b.Left = b.Right = NULL;

    BinTree BST = &b;
    for(int i = 0; i < 7; i++){
        BST = Insert(Data[i],BST); 
    }
    LevelOrderTraversal(BST);
    BST = DeleteTree(54,BST);
    printf("\n");
    LevelOrderTraversal(BST);

    //遍历
    /*printf("preorder:\n");
    PreOrderTraversal(BST);
    printf("\ninorder:\n");
    InOrderTraversal(BST);
    printf("\npostorder:\n");
    PostOrderTraversal(BST);
    printf("\nlevel order:\n");
    LevelOrderTraversal(BST);*/

    //printf("\ninorder used stack:\n");
    //InOrderTraversal_Recursion(BST);

    //找大小
    //printf("\nmin: %d\n",FindMin(BST)->Data);
    //printf("\nmax:%d\n",FindMax(BST)->Data);
    
}

