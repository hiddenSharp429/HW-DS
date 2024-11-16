#include <stdio.h>
#include <iostream>

using namespace std;

#define Max 20
// 顶点信息
struct VertexItem
{
    char Vertex; // 顶点信息
    int index;   // 顶点在邻接矩阵中的下标
};
// 图的邻接矩阵存储
struct Graph
{
    int vertexNum;
    int arcNum;
    bool isDireted;
    int Matrix[Max][Max];
    VertexItem vertexList[Max]; // 顶点信息表
};
// 初始化图
void InitGraph(Graph &G)
{
    G.arcNum = 0;
    G.vertexNum = 0;
    for (int i = 0; i < Max; i++)
    {
        for (int j = 0; j < Max; j++)
        {
            G.Matrix[i][j] = -1;
        }
    }
}
// 获取顶点下标
int Locate(Graph G, char c)
{
    int res = -1;
    for (int i = 0; i < G.vertexNum; i++)
    {
        if (G.vertexList[i].Vertex == c)
        {
            res = G.vertexList[i].index;
        }
    }
    return res;
}
// 创造图
void CreateGraph(Graph &G)
{
    if (G.vertexNum > Max) // 输入的顶点数量超过最大值
    {
        return;
    }
    //
    for (int i = 0; i < G.vertexNum; i++)
    {
        for (int j = 0; j < G.vertexNum; j++)
        {
            G.Matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < G.vertexNum; i++)
    {
        char vertex;
        cin >> vertex;
        G.vertexList[i].Vertex = vertex;
        G.vertexList[i].index = i;
    }
    char tail, head; // 弧尾和弧头
    for (int i = 0; i < G.arcNum; i++)
    {
        cin >> tail >> head;
        int tailIndex, headIndex;
        tailIndex = Locate(G, tail);
        headIndex = Locate(G, head);
        // G为有向图
        if (G.isDireted)
        {
            G.Matrix[tailIndex][headIndex] = 1;
        }
        // G为无向图
        else
        {
            G.Matrix[tailIndex][headIndex] = 1;
            G.Matrix[headIndex][tailIndex] = 1;
        }
    }
}
// 添加顶点
void InsertVex(Graph &G, char c)
{
    G.vertexList[G.vertexNum].Vertex = c;          // 顶点信息存入顶点表中
    G.vertexList[G.vertexNum].index = G.vertexNum; // 顶点的在邻接矩阵的索引存入顶点表中                            // 顶点数量加一
    // 对新插入的顶点对应的矩阵初始化
    for (int i = 0; i <= G.vertexNum; i++)
    {
        G.Matrix[G.vertexNum][i] = 0;
        G.Matrix[i][G.vertexNum] = 0;
    }
    G.vertexNum++;
}
// 删除顶点以及相关的边
void DeletVex(Graph &G, char c)
{
    int vexIndex = Locate(G, c);
    G.vertexNum--;
    for (int i = 0; i < G.vertexNum; i++)
    {
        if (G.Matrix[vexIndex][i] == 1) // 有边
        {
            G.Matrix[vexIndex][i] = 0;
            G.arcNum--;
        }
        if (G.Matrix[i][vexIndex] == 1)
        {
            G.Matrix[i][vexIndex] = 0;
        }
    }
    G.vertexList[vexIndex].index = -1;
}
// 添加弧
void InsertArc(Graph &G, char tail, char head)
{
    int tailIndex = Locate(G, tail);
    int headIndex = Locate(G, head);
    if (headIndex == -1 || tailIndex == -1) // 输入的弧头或者弧尾不存在
    {
        return;
    }
    G.Matrix[tailIndex][headIndex] = 1;
    G.arcNum++;
    if (!G.isDireted)
    {
        G.Matrix[headIndex][tailIndex] = 1; // 若不是有向图则再添加一条对称边
    }
}
// 删除弧
void DeleteArc(Graph &G, char tail, char head)
{
    int tailIndex = Locate(G, tail);
    int headIndex = Locate(G, head);
    if (headIndex == -1 || tailIndex == -1)
    {
        return;
    }
    G.Matrix[tailIndex][headIndex] = 0;
    G.arcNum--;
    if (!G.isDireted)
    {
        G.Matrix[headIndex][tailIndex] = 0; // 若不是有向图则再删除一条对称边
        G.arcNum--;
    }
}

int main()
{
    Graph G;
    InitGraph(G);
    cin >> G.vertexNum >> G.arcNum;
    cin >> G.isDireted;
    CreateGraph(G);
    InsertVex(G, '6');      // 插入新顶点6
    InsertVex(G, '7');      // 插入新顶点7
    InsertArc(G, '1', '6'); // 添加一条边，从1 -> 6
    InsertArc(G, '3', '6'); // 添加一条边，从3 -> 6
    InsertArc(G, '1', '7'); // 添加一条边，从1 -> 7
    InsertArc(G, '3', '7'); // 添加一条边，从3 -> 7
    DeletVex(G, '6');       // 删除顶点6以及其关联的所有边
    DeleteArc(G, '1', '6'); // 删除1->6的边
    return 0;
}