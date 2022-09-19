//图矩阵、队列的建立，利用BFS遍历树，无权图的最短路径算法（类似bsf）。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MaxVertexNum 20
#define MaxQueueNum 10
#define INFINTY 100
typedef int WeightType;
typedef int DataType;
typedef int Vertex;

bool Visited[MaxVertexNum];//保存顶点的访问状态
WeightType dist[MaxVertexNum];  //最短距离
WeightType path[MaxVertexNum]; //经过的顶点


//邻接图节点定义
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;                                       //顶点数
    int Ne;                                       //边数
    WeightType G[MaxVertexNum][MaxVertexNum];     //邻接矩阵，包含边的权重
    DataType Data[MaxVertexNum];                  //存放顶点的数据
};
typedef PtrToGNode MGraph; //用指针来传递图


//边定义
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1,V2;              //有向边
    WeightType Weight;         //边的权重
};
typedef PtrToENode Edge;


//初始化图，顶点数据置0
MGraph CreatGraph(int VertexNum){

    Vertex V,W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    for(V = 0; V < Graph->Nv; V++){
        for (W = 0; W < Graph->Nv; W++){
            Graph->G[V][W] = INFINTY;
        }
    }
    return Graph;

}

//把边插入图中
void InsertEdge( MGraph Graph, Edge E){
    
    //有向图
    Graph->G[E->V1][E->V2] = E->Weight;
    //无向图，反向再插一次
    //Graph->G[E->V2][E->V1] = E->Weight;

}

//建造图
MGraph BUildGraph(){
    MGraph Graph;
    int Nv, i;
    Edge E;
    Vertex V;

    printf("输入顶点个数：\n");
    scanf("%d",&Nv);                //获取顶点数
    Graph = CreatGraph(Nv);         //创建n个顶点的图

    printf("输入边的个数：\n");
    scanf("%d",&Graph->Ne);          //获取边的个数

    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(int i = 0; i < Graph->Ne; i++){

            printf("输入第%d条边：\n",i+1);
            scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
            InsertEdge(Graph,E);
            
        }
        
    }

    //如果顶点有数据
    /*for(V = 0; V < Graph->Nv; V++){
        scanf("%d",&Graph->Data[V];)
    }*/


    return Graph;
}

//队列的定义
typedef struct QueueNode *queue;
struct QueueNode
{
    int Data[MaxQueueNum];
    int rear;     //最后一个元素
    int front;    //第一个元素
};

//初始化队列
queue CreatQueue(){

    queue Q;

    Q = (queue)malloc(sizeof(struct QueueNode));
    Q->front = Q->rear = -1;
    return Q;

}

//进队
void AddQueue(queue Q, int x){
    if((Q->rear + 1) % MaxQueueNum == Q->front % MaxQueueNum){
        printf("full\n");
        return;
    }

    Q->rear = ++Q->rear % MaxQueueNum;
    Q->Data[Q->rear] = x;
    
}

//出队
int DeleQueue(queue Q){
    int x = -1;
    if(Q->rear % MaxQueueNum == Q->front % MaxQueueNum){
        printf("empty");
    }
    else{
        Q->front = ++Q->front % MaxQueueNum;
        x = Q->Data[Q->front];
        
    }
    return x;
}

/*-------------------操作相关-----------------*/
//判断是否存在边
bool IsEdge(MGraph G, Vertex V, Vertex M){
    return G->G[V][M] < INFINTY ? true : false;
}

//访问点
void visit(Vertex V){
    printf("%d ",V);
    Visited[V] = true;
}

//BFS的实现
void BFS(MGraph G, Vertex S){
    queue Q;
    Vertex V,W;

    Q = CreatQueue();
    visit(S);
    AddQueue(Q,S);

    while( !(Q->rear % MaxQueueNum == Q->front % MaxQueueNum) ){
        V = DeleQueue(Q);
        for( W = 0; W < G->Nv; W++){
            if( !Visited[W] && IsEdge(G,V,W)){
                visit(W);
                AddQueue(Q,W);
            }
        }
    }
    
}


/*------------------无权图的最短路径-----------------*/
void Unweighted( Vertex S, MGraph G){
    queue Q;
    Vertex V,W;

    Q = CreatQueue();
    AddQueue(Q,S);
    while( !(Q->rear%MaxQueueNum == Q->front%MaxQueueNum) ){
        V = DeleQueue(Q);
        for(W = 0; W < G->Nv; W++){
            if(dist[W] == -1 && IsEdge(G,V,W)){
                dist[W] = dist[V] + 1;
                path[W] = V;
                AddQueue(Q,W);
            }
        }
    }
}

void print_path_dist(MGraph G){

    for (int i = 0; i < G->Nv; i++){

        printf("%d %d \n",dist[i], path[i]);

    }
    
}

void print_route(MGraph G, Vertex x,Vertex V){

    if(V != x){
        printf("%d->",V);
        print_route(G,x,path[V]);
    }
    else{
        printf("%d",x);
    }
    
}

/*---------------有权图的最短路径------------------*/





int main(){

    //初始化visited数组
    for( int i = 0; i < MaxVertexNum; i++){

        Visited[i] = false;
        path[i] = -1;
        dist[i] = -1;

    }

    MGraph G;

    G = BUildGraph();

    BFS(G,0);
    printf("\n");

    int x;                  //原点
    printf("输入原点：\n");
    scanf("%d",&x);
    dist[x] = 0;

    //print_path_dist(G);

    Unweighted(x,G);

    print_path_dist(G);

    int V;               //查找点
    printf("输入要查找的节点：\n");
    scanf("%d",&V);

    print_route(G,x,V);


    return 0;
}




