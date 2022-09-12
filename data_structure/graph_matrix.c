//图矩阵的建立，遍历

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 20
typedef int WeightType
typedef int DataType
typedef int Vertex


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
    
    //有向图
    Graph->G[E->V1][E->V2] = E->Weight;
    //无向图，反向再插一次
    //Graph->G[E->V2][E->V1] = E->Weight;

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

    //如果顶点有数据
    /*for(V = 0; V < Graph->Nv; V++){
        scanf("%d",&Graph->Data[V];)
    }*/


    return Graph;
}






