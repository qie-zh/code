//堆是根节点大于所有子节点的树
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxData 100

typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    int *Elements;
    int Size;
    int Capacity;
};


MaxHeap Creat( int MaxSize ){

    MaxHeap H = malloc(sizeof(struct HeapStruct));

    H->Elements = malloc((MaxSize + 1) * sizeof(int));         //从1开始存放数据
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MaxData;          //哨兵元素

    return H;
}

int Isfull( MaxHeap H){
    if(H->Size == H->Capacity) return 1;
    else return 0;
}

int IsEmpty(MaxHeap H){
    if(H->Size == 0) return 1;
    else return 0;
}

void Insert( MaxHeap H, int X){
    int i;

    if ( Isfull(H)){
        printf("fulled");
        return;
    }

    i = ++H->Size;

    for(; H->Elements[i/2] < X; i/=2){
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = X;
}

int DeleteMax(MaxHeap H){
    int Parent, Child;
    int MaxItem, temp;


    if( IsEmpty(H)){
        printf("empty");
        return -1;
    }

    MaxItem = H->Elements[1];

    temp = H->Elements[H->Size--];

    for(Parent = 1; Parent*2 <= H->Size; Parent = Child){
        Child = Parent*2;                                                  //左儿子，右儿子parent*2+1
        if((Child != H->Size) && (H->Elements[Child] < H->Elements[Child +1])){
            Child++;
        }
        if(temp >= H->Elements[Child]) break;
        else H->Elements[Parent] = H->Elements[Child];
    }

    H->Elements[Parent] = temp;
    return MaxItem;
}

void PercDown( MaxHeap H, int p){
    int Parent, Child;
    int X;

    X = H->Elements[p];

    for(Parent = p; Parent*2 <= H->Size; Parent = Child){

        Child = Parent*2;

        if((Child != H->Size) && (H->Elements[Child] < H->Elements[Child +1])){     //比较左子树和右子树大小,child表示大的儿子，如果child等于size表示只有左儿子没有右儿子不用参与比较
            Child++;
        }

        if( X >= H->Elements[Child]) break;          //比父节点大，交换位置
        else{
            H->Elements[Parent] = H->Elements[Child];
        }
        
    }
    H->Elements[Parent] = X;
}

void BuildHeap( MaxHeap H, int *nums){
    int i;

    for( i = 0; i < H->Capacity; i++){
        H->Elements[i+1] = nums[i];
        H->Size++;
    }

    for (i = H->Size/2; i > 0; i--){
        PercDown(H,i);
    }
    
}

void PrintHeap( MaxHeap H){

    for(int i = 1; i <= H->Size; i++){
        printf("%d ",H->Elements[i]);
        if((i == 1) || (i == 3) || (i == 7)) printf("\n");
    }
}

void main(){

    MaxHeap H;
    int nums[10] = {12,52,63,34,87,23,39,92,48,70};

    H = Creat(10);
    BuildHeap(H,nums);

    /*for(int i = 0; i <= H->Capacity; i++){
        H->Elements[i+1] = nums[i];
        H->Size++;
    }*/

    PrintHeap(H);
    printf("\n");
    
    DeleteMax(H);
    PrintHeap(H);
    printf("\n");

    DeleteMax(H);
    PrintHeap(H);
    printf("\n");

    Insert(H,55);
    PrintHeap(H);

    //printf("%d",H->Elements[2]);



}