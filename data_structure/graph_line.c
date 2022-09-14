//邻接表的建立，并使用DFS遍历整棵树

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 20
typedef int WeightType;
typedef int DataType;
typedef int Vertex;

int Visited[MaxVertexNum];

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
    
    for(V = 0; V <Graph->Nv; V++){
        printf("输入第%d顶点",V+1);
        scanf("%d",&(Graph->G[V].Data));
    }/**/

    return Graph;
}

void Visit(Vertex V){
    printf("%d ",V);
}

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

int main(){

    for(int i = 0; i < MaxVertexNum; i++){
        Visited[i] = 0;
    }

    LGraph G;

    G = BuildGraph();

    DFS(G,0);


    return 0;
}