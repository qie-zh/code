//建立最小堆和哈夫曼树

#include <stdio.h>
#include <stdlib.h>

//哈夫曼树的结构体声明
typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    int Weight;
    HuffmanTree Left, Right;
};

//最小堆的结构体声明
typedef struct HeapStruct *MinHeap;
struct HeapStruct{
    int *Elements;
    int Size;       //当前大小
    int Capacity;   //最大容量
};

MinHeap Creat( int MaxSize ){

    MinHeap H = malloc(sizeof(struct HeapStruct));

    H->Elements = malloc((MaxSize + 1) * sizeof(int));         //从1开始存放数据
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = -1;          //哨兵元素

    return H;
}

int Isfull( MinHeap H){
    if(H->Size == H->Capacity) return 1;
    else return 0;
}

int IsEmpty(MinHeap H){
    if(H->Size == 0) return 1;
    else return 0;
}

void Insert( MinHeap H, int X){
    int i;

    if ( Isfull(H)){
        printf("fulled");
        return;
    }

    i = ++H->Size; // i指向插入后堆的最后一个元素

    for(; H->Elements[i/2] > X; i/=2){// i/2 是父节点，如果插入元素比父节点小
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = X;
}

int DeleteMin(MinHeap H){
    int Parent, Child;
    int MinItem, temp;


    if( IsEmpty(H)){
        printf("empty");
        return -1;
    }

    MinItem = H->Elements[1];

    temp = H->Elements[H->Size--];  //保留最后的一个元素，并且堆的大小减1

    for(Parent = 1; Parent*2 <= H->Size; Parent = Child){//如果2*parent大于size表示没有左儿子更没有右儿子，child=parent表示移动到小儿子并且继续比较
        Child = Parent*2;                                                  //左儿子，右儿子parent*2+1
        if((Child != H->Size) && (H->Elements[Child] > H->Elements[Child +1])){//child等于size表示没有右儿子就不用比较
            Child++;   //child指向更小的儿子
        }
        if(temp <= H->Elements[Child]) break;  //如果比小的儿子还要小表示找到位置
        else H->Elements[Parent] = H->Elements[Child];
    }//循环结束表示找到合适的位置

    H->Elements[Parent] = temp;

    return MinItem;
}

void PercDown( MinHeap H, int p){//p表示最后一个元素
    int Parent, Child;
    int X;

    X = H->Elements[p];

    for(Parent = p; Parent*2 <= H->Size; Parent = Child){

        Child = Parent*2;

        if((Child != H->Size) && (H->Elements[Child] > H->Elements[Child +1])){     //比较左子树和右子树大小,child表示小的儿子，如果child等于size表示只有左儿子没有右儿子不用参与比较
            Child++;
        }

        if( X <= H->Elements[Child]) break;          //比父节点小，交换位置
        else{
            H->Elements[Parent] = H->Elements[Child];
        }
        
    }
    H->Elements[Parent] = X;
}

void BuildHeap( MinHeap H, int *nums){
    int i;

    for( i = 0; i < H->Capacity; i++){
        H->Elements[i+1] = nums[i];
        H->Size++;
    }

    for (i = H->Size/2; i > 0; i--){
        PercDown(H,i);
    }
    
}

void PrintHeap( MinHeap H){
    printf("-----打印堆----\n");

    for(int i = 1; i <= H->Size; i++){
        printf("%d ",H->Elements[i]);
        if((i == 1) || (i == 3) || (i == 7)) printf("\n");
    }
}

HuffmanTree Huffman(MinHeap H, int* num){

    int i;
    HuffmanTree T;

    H = Creat(10);
    BuildHeap(H,nums);

    for( i = 1; i < H->Size; i++){
        T = malloc(sizeof(struct TreeNode));
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);

        T->Weight = T->Left->Weight + T->Right->Weight;

        Insert(H,T);
    }
    T = DeleteMin(H);

    return T;
}

void main(){

    MinHeap H;
    HuffmanTree T;

    int nums[10] = {12,52,63,34,87,23,39,92,48,70};

    T = Huffman(H,nums);

    

    /*PrintHeap(H);
    printf("\n");
    
    printf("删除元素：%d\n",DeleteMin(H));
    PrintHeap(H);
    printf("\n");

    DeleteMin(H);
    PrintHeap(H);
    printf("\n");

    Insert(H,55);
    PrintHeap(H);*/

}