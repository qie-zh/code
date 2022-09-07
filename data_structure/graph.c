#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 20
#define WeightType int
#define DataType int
#define Vertex int


//邻接图定义
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;                                       //顶点数
    int Ne;                                        //边数
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];                                //存放顶点的数据
};
typedef PtrToGNode MGraph; //用指针来传递图



//边定义
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1,V2;//有向边
    WeightType Weight;
};
typedef PtrToENode Edge;



MGraph CreatGraph(int VertexNum){

    Vertex V,W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    for(V = 0; V < Graph->Nv; V++){
        for (W = 0; W < Graph->Nv; W++){
            Graph->G[V][W] = 0;
        }
        
    }
    return Graph;

}

void InsertEdge( MGraph Graph, Edge E){

    Graph->G[E->V1][E->V2] = E->Weight;//有向图
    Graph->G[E->V2][E->V1] = E->Weight;//无向图

}

MGraph BUildGraph(){
    MGraph Graph;
    int Nv, i;
    Edge E;
    Vertex V;



    scanf("%d",&Nv);
    Graph = CreatGraph(Nv);
    scanf("%d",Graph->Ne);
    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(int i = 0; i < Graph->Ne; i++){
            scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
            InsertEdge(Graph,E)
        }
    }
    return Graph;
}

//邻接表的边
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

//邻接表类型
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
    DataType Data;    //顶点数据
} AdjList[MaxVertexNum];


//邻接表表示图
typedef struct GNodeList *PtrToGNodeList;
struct GNodeList
{
    int Nv;//顶点
    int Ne;//边
    AdjList G;//邻接表
};
typedef PtrToGNodeList LGraph;

LGraph CreatGraph(int VertexNum){
    Vertex V,W;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNodeList));
    Graph->Ne = 0;
    Graph->Nv = Vertex;

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
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;

    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

