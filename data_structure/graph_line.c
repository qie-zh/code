//邻接表的建立，并使用DFS遍历整棵树,有权图的最短路径Dijkstra

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 20
#define INFINITY 100
#define error -100

typedef int WeightType;
typedef int DataType;
typedef int Vertex;

int Visited[MaxVertexNum];
bool collected[MaxVertexNum];    //储存被访问过顶点的集合
WeightType dist[MaxVertexNum];  //最短距离
WeightType path[MaxVertexNum]; //经过的顶点


//边的定义
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

//邻接点定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;         //邻接点下标
    WeightType Weight;
    PtrToAdjVNode Next;
};

//邻接表表头数组定义
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
    DataType Data;    //顶点数据
} AdjList[MaxVertexNum];


//邻接表表示图
typedef struct GNodeList *PtrToGNodeList;
struct GNodeList{

    int Nv;//顶点
    int Ne;//边
    AdjList G;//邻接表
};
typedef PtrToGNodeList LGraph;



LGraph CreatGraph(int VertexNum){ //有顶点但是没有边的图
    Vertex V,W;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNodeList));
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    for(V = 0; V < Graph->Nv; V++){
        Graph->G[V].FirstEdge = NULL;
    }
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E){
    PtrToAdjVNode NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;

    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    //无向图
    /*NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;

    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;*/
}

LGraph BuildGraph(){
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv,i;

    printf("输入顶点个数：");
    scanf("%d",&Nv);
    Graph = CreatGraph(Nv);

    printf("输入边个数：");
    scanf("%d",&(Graph->Ne));

    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for( i = 0; i < Graph->Ne; i++){
            printf("输入第%d条边：",i+1);
            scanf("%d %d %d",&(E->V1),&(E->V2),&(E->Weight));
            InsertEdge(Graph,E);
        }
    }

    //如果有顶点数据
    
   /*for(V = 0; V <Graph->Nv; V++){
        printf("输入第%d顶点",V+1);
        scanf("%d",&(Graph->G[V].Data));
    }*/

    return Graph;
}

void Visit(Vertex V){
    printf("%d ",V);
}



//深度优先搜索
void DFS(LGraph Graph,Vertex V){

    PtrToAdjVNode W;

    Visit(V);
    Visited[V] = 1;

    for(W = Graph->G[V].FirstEdge; W; W = W->Next){
        if( !Visited[W->AdjV]){
            DFS(Graph,W->AdjV);

        }
    }

}

/*-------------------------有权图的最短路径------------------------*/

//寻找访问集合之外的最小顶点
Vertex FindMinDist(LGraph G){

    Vertex MinV,V;
    int MinDist = INFINITY;

    for(V = 0; V < G->Nv; V++){
        if( collected[V] = false && dist[V] < MinDist){ //未被访问且
            MinDist = dist[V];
            MinV = V;
        }
    }

    if( MinDist < INFINITY){
        return MinV;
    }
    else{
        return error;
    }

}

//最短路径算法
bool Dijksra(LGraph G,Vertex S){

    Vertex V,M;
    PtrToAdjVNode W;

    for(W = G->G[V]; V < G->Nv; V++){
        dist[V] = 
    }
}


int main(){

    //初始化数组
    for(int i = 0; i < MaxVertexNum; i++){
        Visited[i] = 0;
        dist[i] = INFINITY;
        path[i] = -1;
        collected[i] = false;
    }

    LGraph G;

    G = BuildGraph();

    DFS(G,0);


    return 0;
}