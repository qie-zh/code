//建立最小堆(链表)和哈夫曼树

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
    HuffmanTree *Elements;
    int Size;       //当前大小
    int Capacity;   //最大容量
};

HuffmanTree NewNode( int data){
    HuffmanTree TN;

    TN = (HuffmanTree)malloc(sizeof( struct TreeNode));
    TN->Left = TN->Right = NULL;

    TN->Weight = data;

    return TN;
}

MinHeap CreatMinHeap( int MaxSize ){

    MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));

    H->Elements = (HuffmanTree*)malloc((MaxSize + 1) * sizeof(HuffmanTree));         //从1开始存放数据
    H->Size = 0;
    H->Capacity = MaxSize;

    HuffmanTree T = NewNode(0);

    T->Weight = -1;     //设为最小值,作为哨兵元素

    H->Elements[0] = T;          //把哨兵元素放到第一个位置

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

void Insert( MinHeap H, HuffmanTree X){
    int i;

    if ( Isfull(H)){
        printf("fulled");
        return;
    }

    i = ++H->Size; // i指向插入后堆的最后一个元素

    for(; H->Elements[i/2]->Weight > X->Weight; i/=2){// i/2 是父节点，如果插入元素比父节点小
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = X;
}

HuffmanTree DeleteMin(MinHeap H){//从最小堆取出并删除值
    int Parent, Child;
    HuffmanTree MinItem, temp = NULL;


    if( IsEmpty(H)){
        printf("empty");
        return NULL;
    }

    MinItem = H->Elements[1];

    temp = H->Elements[H->Size--];  //保留最后的一个元素，并且堆的大小减1

    for(Parent = 1; Parent*2 <= H->Size; Parent = Child){//如果2*parent大于size表示没有左儿子更没有右儿子，child=parent表示移动到小儿子并且继续比较
        Child = Parent*2;                                                  //左儿子，右儿子parent*2+1
        if((Child != H->Size) && (H->Elements[Child]->Weight > H->Elements[Child +1]->Weight)){//child等于size表示没有右儿子就不用比较
            Child++;   //child指向更小的儿子
        }
        if(temp->Weight <= H->Elements[Child]->Weight) break;  //如果比小的儿子还要小表示找到位置
        else H->Elements[Parent] = H->Elements[Child];
    }//循环结束表示找到合适的位置

    H->Elements[Parent] = temp;

    return MinItem;
}

void PercDown( MinHeap H, int p){//p表示最后一个元素
    int Parent, Child;
    HuffmanTree X;

    X = H->Elements[p];

    for(Parent = p; Parent*2 <= H->Size; Parent = Child){

        Child = Parent*2;

        if((Child != H->Size) && (H->Elements[Child]->Weight > H->Elements[Child +1]->Weight)){     //比较左子树和右子树大小,child表示小的儿子，如果child等于size表示只有左儿子没有右儿子不用参与比较
            Child++;//儿子中较小的那个
        }

        if( X->Weight <= H->Elements[Child]->Weight) break;          //比父节点小，交换位置
        else{
            H->Elements[Parent] = H->Elements[Child];
        }
        
    }
    H->Elements[Parent] = X;

}

void BuildMinHeap( MinHeap H, int *nums){
    int i;
    HuffmanTree temp;
    

    for( i = 0; i < H->Capacity/2; i++){
        temp = NewNode(nums[i]);

        H->Elements[i+1] = temp;
        H->Size++;
    }

    for (i = H->Size/2; i > 0; i--){
        PercDown(H,i);

    }
    
}

void PrintHeap( MinHeap H){
    printf("-----打印堆----\n");

    for(int i = 1; i <= H->Size; i++){
        printf("%d ",H->Elements[i]->Weight);
        if((i == 1) || (i == 3) || (i == 7)) printf("\n");
    }
    printf("\n");
}

HuffmanTree Huffman(MinHeap H, int* num){

    int i;
    HuffmanTree T;

    for( i = 1; i < H->Size; i++){
        T = NewNode(0);
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);

        T->Weight = T->Left->Weight + T->Right->Weight;

        Insert(H,T);
    }
    T = DeleteMin(H);

    return T;
}

void PreOrderTraversal(HuffmanTree BST){

    if( BST ){

        printf("%d ",BST->Weight);     //先访问根节点

        PreOrderTraversal(BST->Left);  //再访问左子树

        PreOrderTraversal(BST->Right); //最后访问右子树

    }
}

void main(){

    MinHeap H;
    HuffmanTree T;

    int nums[4] = {1,5,2,6};

    
    H = CreatMinHeap(4*2);
    BuildMinHeap(H,nums);
    PrintHeap(H);
    //printf("---删除元素---\n%d\n ",DeleteMin(H)->Right);
    //PrintHeap(H);
    T = Huffman(H,nums);
    printf("---先序遍历---");
    PreOrderTraversal(T);


    
}