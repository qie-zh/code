//最小树生成问题，贪心算法
//向生成树中任意加一条边都构成回路，V个顶点则有V-1条边
//用邻接矩阵实现

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define  MaxVertexNum 10
#define INFINTY 100
#define error -1000

typedef int WeightType;
typedef int DataType;
typedef int Vertex;

bool collected[MaxVertexNum];
WeightType dist[MaxVertexNum];
WeightType path[MaxVertexNum];
WeightType MST[MaxVertexNum];

//定义邻接矩阵图
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;//顶点个数
    int Ne;//边
    WeightType G[MaxVertexNum][MaxVertexNum];//边的值
    DataType Data[MaxVertexNum];//顶点的值
};
typedef PtrToGNode MGraph;

//定义边
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1,V2;//边所连接的顶点
    WeightType Weight;
};
typedef PtrToENode Edge;

//初始化图
MGraph CreatGraph(int Num){

    Vertex V,W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = Num;
    Graph->Ne = 0;

    for( V = 0; V < Graph->Nv; V++){
        for(W = 0; W < Graph->Nv; W++){
            Graph->G[V][W] = INFINTY;
        }
    }

    return Graph;
}

//建造图
MGraph BuildGraph(){

    MGraph Graph;
    int Nv, i;
    Edge E;
    Vertex V,W;

    printf("输入顶点个数:");
    scanf("%d",&Nv);
    Graph = CreatGraph(Nv);

    printf("输入边个数:");
    scanf("%d",&(Graph->Ne));

    //初始化邻接矩阵，所有边都为-1
    for(V = 0; V < Graph->Nv; V++){
        for(W = 0; W < Graph->Nv; W++){
            Graph->G[V][W] = -1;
        }
    }

    if(Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for(V = 0; V <Graph->Ne; V++){
            printf("输入第%d条边:",V);
            scanf("%d%d%d",&E->V1,&E->V2,&E->Weight);
            Graph->G[E->V1][E->V2] = E->Weight;//把边插入图
            Graph->G[E->V2][E->V1] = E->Weight;//无向图
        }
    }
    
}

//寻找访问集合之外的权值最小点
Vertex FindMinDist(MGraph G){
    
    Vertex MinV,V;
    int MinDist = INFINTY;

    for(V = 0; V < G->Nv; V++){
        if(collected[V] == false && dist[V] < MinDist){
            MinDist = dist[V];
            MinV = V;
        }
    }

    if( MinDist < INFINTY){
        return MinV;
    }
    else return error;
}

void Prim(MGraph Graph, Vertex S){

    Vertex V,W;

    //把原点收入数组
    dist[S] = 0;
    collected[S] = true;
    path[S] = -1;

    //初始化dist数组
    for(V = 0; V < Graph->Nv; V++){
        if(Graph->G[S][V] != -1){
            dist[V] = Graph->G[S][V];//和原点相邻的点直接加入dist
        }
        else dist[V] = INFINTY;//否则为正无穷
    }

    while(1){
        V = FindMinDist(Graph);

        if(V == error) break;

        collected[V] = true;
        dist[V] = 0;

        for(W = 0; W < Graph->Nv; W++){
            if(collected[W] == false && Graph->G[V][W] != -1){
                if(Graph->G[V][W] < dist[W]){
                    dist[W] = Graph->G[V][W];
                    path[W] = V;
                }
            }
        }
    }

}


void main(){

    MGraph Graph;

    Graph = BuildGraph();




}