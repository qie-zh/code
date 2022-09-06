#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxSize 5   //最大存放n-1

struct QNode
{
    int Data[MaxSize];
    int rear;                  //指向最后一个元素
    int front;                  //指向第一个元素前
};
typedef struct QNode *Queue;

void AddQ(Queue PtrQ, int i){
    if((PtrQ->rear+1) % MaxSize == PtrQ->front){
        printf("fulled");
        return;
    }
    PtrQ->rear = (PtrQ->rear + 1) % MaxSize;
    PtrQ->Data[PtrQ->rear] = i; 
}

int DeleteQ(Queue PtrQ){
    if(PtrQ->front == PtrQ->rear){
        printf("empty");
        return -1;
    }
    else{
        PtrQ->front = (PtrQ->front + 1) % MaxSize;
        return PtrQ->Data[PtrQ->front];
    }
}

void print_q(Queue PtrQ){
    int i;
    
    for(i = PtrQ->front + 1; (i % MaxSize) != PtrQ->rear + 1; i++){
        printf("%d ",PtrQ->Data[i]);
    }

}


void main(){
    struct QNode q;
    q.rear = -1;
    q.front = -1;
    Queue p = &q;

    AddQ(p,1);
    AddQ(p,2);
    AddQ(p,3);
    DeleteQ(p);
    DeleteQ(p);
    AddQ(p,4);

    printf("front = %d, rear = %d\n",p->front,p->rear);
    print_q(p);
    

}