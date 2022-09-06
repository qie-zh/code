#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct LNode *List;
struct LNode{
    int data;
    List Next;
};


int Length( List PtrL){    //链表长度
    List p = PtrL;
    int j = 0;
    while(p){
        p = p->Next;
        j++;
    }
    return j;
}

List FindKth( int k, List PtrL){                 //按序号查找 k表示序号
    List p = PtrL;
    int i = 1;
    while(p->Next !=NULL && i < k){
        p = p->Next;
        i++;
    }
    if(i == k){
        return p;
    }
    else return NULL;
}

List Find(int x, List PtrL){             //按数值查找
    List p = PtrL;
    while(p != NULL && p->data != x){
        p = p->Next;
    }
    return p;
}


List Insert(int x, int i, List PtrL){              //插入操作，x表示数据，i表示序号
    List p,s;
    if(i == 1){                                     //插在第一个位置，头指针变为s
        s = (List)malloc(sizeof(struct LNode));
        s->data = x;
        s->Next = PtrL;
        return s;
    }

    p = FindKth(i-1, PtrL);                         //找到i-1个节点
    if(p == NULL){
        printf("error!!");
        return NULL;
    }
    else{
        s = (List)malloc(sizeof(struct LNode));
        s->data = x;
        s->Next = p->Next;
        p->Next = s;
        return PtrL; 
    }
}

List Delete(int i, List PtrL){                      //删除某一个数据
    List p,s;
    if(i == 1){                                     //如果是第一个节点
        s = PtrL;
        if(PtrL != NULL) PtrL =  PtrL->Next;
        else return NULL;
        free(s);
        return PtrL;
    }
    p = FindKth(i-1,PtrL);
    if(p == NULL){
        printf("error!");
        return NULL;
    }
    else if(p->Next == NULL){
        printf("error!!");
        return NULL;
    }
    else{
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
}

void printf_L(List PtrL){
    List p;
    for(int i = 1; i <= Length(PtrL); i++){
        p = FindKth(i,PtrL);
        printf("%d  ", p->data);
    }
}

void main(){
    //List p = (List)malloc(sizeof(struct LNode));
    //p->data = 18;
    //p->Next = NULL;

    List p = NULL;                                   //头指针
    List s = NULL;

    List p1 = (List)malloc(sizeof(struct LNode));
    p1->data = 1;
    p1->Next = NULL;
    p = p1;

    for(int i = 2; i < 5; i++){
        p = Insert(i*2,i,p);
    }

    p = Delete(2,p);

    /*List p2 = (List)malloc(sizeof(struct LNode));
    p2->data = 3;
    p2->Next = NULL;
    p1->Next = p2;

    List p3 = (List)malloc(sizeof(struct LNode));
    p3->data = 9;
    p3->Next = NULL;
    p2->Next = p3;*/

    //printf("%d\n",Length(p));

    //s = FindKth(2,p);
    //printf("%d ",s->data);

    printf_L(p);


}