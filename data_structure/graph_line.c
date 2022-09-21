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
bool collected[MaxVertexNum];    //记录已被访问过的顶点
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


//有顶点但是没有边的图
LGraph CreatGraph(int VertexNum){ 
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

//插入边
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


    int Vnums[5] =  {0,0,1,2,3};
    int Wnums[5] =  {1,2,3,3,0};
    int Weight[5] = {1,2,1,3,2};

    //printf("输入顶点个数：");
    //scanf("%d",&Nv);
    Nv = 4;
    Graph = CreatGraph(Nv);

    //printf("输入边个数：");
    //scanf("%d",&(Graph->Ne));
    Graph->Ne = 5;

    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for( i = 0; i < Graph->Ne; i++){
            //printf("输入第%d条边：",i+1);
            //scanf("%d %d %d",&(E->V1),&(E->V2),&(E->Weight));

            E->V1 = Vnums[i];
            E->V2 = Wnums[i];
            E->Weight = Weight[i];
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

//顶点没存数据，打印数组中的位置
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
        if( collected[V] == false && dist[V] < MinDist){ //未被访问且权值较小者
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

    //把顶点放入数组
    dist[S] = 0;
    collected[S] = true;

    //初始化数组
    for(W = G->G[S].FirstEdge; W; W = W->Next){
        dist[W->AdjV] = W->Weight;
        if( dist[W->AdjV] < INFINITY ){
            path[W->AdjV] = S;
        }
        else{
            path[W->AdjV] = S;
        }
    }

    

    return false;

}



int main(){

    //初始化数组
    for(int i = 0; i < MaxVertexNum; i++){
        Visited[i] = 0;
        dist[i] = INFINITY;
        collected[i] = false;
    }

    LGraph G;

    G = BuildGraph();

    DFS(G,0);

    //获取原点并将最近的顶点权值放入数组
    int S;
    PtrToAdjVNode W;
    printf("输入原点：");
    scanf("%d",&S);
    
    //Dijksra(G,S);


    printf("%d\n", FindMinDist(G));

    /*for(int i = 0; i < MaxVertexNum; i++){
        printf("%d ",dist[i]);
    }*/
    




    return 0;
}