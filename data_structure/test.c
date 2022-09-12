#include<stdio.h>

#include<stdlib.h>
#include<stdbool.h>

#define MinData -1

typedef struct TreeNode *HuffmanTree;//哈夫曼树类型

struct TreeNode{

int Weight;  //结点权值

HuffmanTree Left;//指向左子树

HuffmanTree Right;//指向右子树

}HuffmanNode;//定义新的结构变量

  

typedef struct HeapStruct *MinHeap;

struct HeapStruct{

HuffmanTree *Data;  //存储堆元素的数组  存储时从下标1开始

int Size;  //堆的当前元素的个数

int Capacity;  //堆的最大容量

};

 

HuffmanTree NewHuffmanNode();

//构造新的哈夫曼树

MinHeap CreateMinHeap(int MaxSize);

//创建容量为MaxSize的最小堆

bool Insert(MinHeap H,HuffmanTree item);

//将元素item插入到最小堆H中

HuffmanTree DeleteMin(MinHeap H);

//从最小堆H中取出权值为最小的元素，并删除一个结点

MinHeap BuildMinHeap(MinHeap H);

//将H->data[]按权值调整为最小堆

HuffmanTree Huffman(MinHeap H);

//最小堆构造哈夫曼树

void PreOrderTraversal(HuffmanTree BST);

//先序遍历哈夫曼树

 

int main()

{

    int i,N;

    MinHeap h;

    HuffmanTree T,BT = NULL;

 

    printf("输入叶子结点的个数:\n");

    scanf("%d",&N);

    h = CreateMinHeap(2*N);  //创建最小堆

    printf("输入%d个叶子结点对应的权值:\n",N);

    for(i=1; i<=N; i++){/*最小堆元素赋值*/

        T = NewHuffmanNode();

        scanf("%d",&(T->Weight));

        h->Data[++(h->Size)] = T;

    }

    BT = Huffman(h);  //构造哈夫曼树

    printf("先序遍历此哈夫曼树:\n");

    PreOrderTraversal(BT);  //先序遍历哈夫曼树

 

    return 0;

 }

  /*哈夫曼树构造算法*/

 HuffmanTree Huffman(MinHeap H)

 {/*假设H->Size个权值已经存在H->data[]->Weight里*/

  int i,n;

HuffmanTree T;

 

BuildMinHeap( H );  //将H->data[]按权值调整为最小堆

/*此处必须将H->Size的值交给num,因为后面做DeleteMin()和 Insert()函数会改变H->Size的值*/

n = H->Size;
printf("%d",n);     

for(i=1; i<n; i++){  //做 H->Size-1次合并

    T = NewHuffmanNode();  //建立一个新的根结点

    T->Left = DeleteMin(H);  //从最小堆中删除一个节点，作为新T的左子结点

    T->Right = DeleteMin(H);  //从最小堆中删除一个节点，作为新T的右子结点

    T->Weight = T->Left->Weight+T->Right->Weight;  //计算新权值

    Insert(H,T);  //将新T插入到最小堆

}

T = DeleteMin(H);

 

return T;

  }

  

//先序遍历哈夫曼树

void PreOrderTraversal(HuffmanTree BST)

{

if( BST ){

printf("%d ",BST->Weight);     //先访问根节点

PreOrderTraversal(BST->Left);  //再访问左子树

PreOrderTraversal(BST->Right); //最后访问右子树

}

}

 

HuffmanTree NewHuffmanNode()

{

HuffmanTree BST = (HuffmanTree)malloc(sizeof(HuffmanNode));

BST->Weight = 0;

BST->Left = BST->Right = NULL;

 

return BST;

 }  

  

MinHeap CreateMinHeap(int MaxSize)

{  /*创建容量为MaxSize的最小堆*/

MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));

H->Data = (HuffmanTree *)malloc((MaxSize+1) * sizeof(HuffmanTree));

H->Size = 0;

H->Capacity = MaxSize;

HuffmanTree T = NewHuffmanNode();

T->Weight = MinData;  /*定义哨兵-为小于堆中所有可能元素权值的值，便于以后更快操作*/

H->Data[0] = T;

 

return H;

}

 //插入新增节点

bool  IsFull(MinHeap H)

{

return (H->Size == H->Capacity);

}

 

bool IsEmpty(MinHeap H)

{

return (H->Size == 0);

}

 

 

bool Insert(MinHeap H,HuffmanTree item)

{        //将元素item插入到最小堆H中

int i;

if( IsFull(H) ){

printf("最小堆已满\n");

return false;

}

i = ++H->Size;  //i指向插入后堆中的最后一个元素的位置

for(; H->Data[i/2]->Weight > item->Weight; i/=2)  //无哨兵，则增加判决条件 i>1

    H->Data[i] = H->Data[i/2];  //向下过滤结点

H->Data[i] = item;   //将item插入

 

return true;

 }

 

HuffmanTree DeleteMin(MinHeap H)

{/*从最小堆H中取出权值为最小的元素，并删除一个结点*/

int parent,child;

HuffmanTree MinItem,temp = NULL;

if( IsEmpty(H) ){

printf("最小堆为空\n");

return NULL;

}

MinItem = H->Data[1];  //取出根结点-最小的元素-记录下来

//用最小堆中的最后一个元素从根结点开始向上过滤下层结点

temp = H->Data[H->Size--];  //最小堆中最后一个元素，暂时将其视为放在了根结点

for(parent=1; parent*2<=H->Size; parent=child){

child = parent*2;

if((child != H->Size) && (H->Data[child]->Weight > H->Data[child+1]->Weight)){

/*有右儿子，并且左儿子权值大于右儿子*/

child++; //child指向左右儿子中较小者

}

if(temp->Weight > H->Data[child]->Weight){

H->Data[parent] = H->Data[child];  //向上过滤结点-temp存放位置下移到child位置

}else{

break;  //找到了合适的位置

}

}

H->Data[parent] = temp;  //temp存放到此处

 

return MinItem;

}

 

MinHeap BuildMinHeap(MinHeap H)

{

int i,parent,child;

HuffmanTree temp;

for(i=H->Size/2;i>0;i--){  //从最后一个父结点开始，直到根结点

temp = H->Data[i];

for(parent=i; parent*2<=H->Size; parent=child){

    /*向下过滤*/

child = parent*2;

    if((child != H->Size) && (H->Data[child]->Weight > H->Data[child+1]->Weight)){/*有右儿子，并且左儿子权值大于右儿子*/

    child++; //child指向左右儿子中较小者

    }

    if(temp->Weight > H->Data[child]->Weight){

    H->Data[parent] = H->Data[child];  //向上过滤结点-temp存放位置下移到child位置

    }else{

    break;  //找到了合适的位置

    }

    }/*结束内部for循环对以H->data[i]为根的子树的调整*/

 

H->Data[parent] = temp;  //temp存放到此处  

}

return H;

}