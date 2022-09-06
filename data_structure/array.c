#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 20


typedef struct LNode *List;
struct LNode{
    int Data[MAXSIZE];
    int Last;
};

List makeEmpty(){
    List PtrL;
    PtrL = (List)malloc(sizeof(struct LNode));
    PtrL-> Last = -1;
    return PtrL;
}



int Find(int x, List PtrL){  //查找
    int i = 0 ;
    while (i <= PtrL->Last && PtrL->Data[i]!=x){
        i++;
    }
    if(i > PtrL->Last){
        return 1;
    }
    else return i;
}

void Insert( int x, int i, List PtrL){         //插入
    int j;
    if(PtrL->Last == MAXSIZE-1){
        printf("fulled");
        return;
    }
    if(i < 1 || i > PtrL->Last+2){
        printf("illegal");
        return;

    }

    for(i = PtrL->Last;i >= i-1; j--){
        PtrL->Data[j+1] = PtrL->Data[j];
    }
    PtrL->Data[i-1] = x;
    PtrL->Last++;
    return;

}

void Delete(int i, List PtrL){  //删除
    int j;
    if(i < 1 || i > PtrL->Last+1){
        printf("not exist");
        return;
    }

    for(int j = 0; j <= PtrL->Last; j++){
        PtrL->Data[j-1] = PtrL->Data[j];
    }
    PtrL->Last--;
    return;
}


void main(){

    List L;      //指向结构体的指针

    struct LNode L2;  //直接定义结构体

    L2.Data[1] = 2;

    printf("%d\n",L2.Data[1]);

    L = makeEmpty();
    
    for(int i = 0; i < 11; i++){
        L->Data[i] = i*2;
        L->Last = i;
    }
    for(int j = 0; j < L->Last; j++){
        printf("%d.%d  ",j,L->Data[j]);
    }
}




