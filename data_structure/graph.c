#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 20
#define WeightType int
#define DataType int
#define Vertex int

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;                                       //顶点数
    int Ne;                                        //边数
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];                                //存放顶点的数据
};

typedef PtrToGNode MGraph; //用指针来传递图



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

void InsertEdge()

