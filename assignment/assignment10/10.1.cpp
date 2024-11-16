#include <stdio.h>
#include <iostream>

using namespace std;

#define MaxSize 20 // 最大顶点的个数
struct Node
{
    int weight;
    int index;
    struct Node *next;
};
struct HNode
{
    char nodeData;
    struct Node *next;
};
struct Graph
{
    int vertexNum;
    int arcNum;
    bool isDireted;
    HNode verList[MaxSize];
};

int Locate(char c, Graph G)
{
    int index = -1;
    for (int i = 0; i < G.vertexNum; i++)
    {
        if (G.verList[i].nodeData == c)
        {
            index = i;
        }
    }
    return index;
}

void InsertVex(Graph &G, char v)
{
    G.verList[G.vertexNum].nodeData = v;
    G.verList[G.vertexNum].next = nullptr;
    G.vertexNum++;
}

void InsertArc(Graph &G, char tail, char head)
{
    int TailIndex, HeadIndex;
    TailIndex = Locate(tail, G);
    HeadIndex = Locate(head, G);
    if (HeadIndex == -1 || TailIndex == -1) // 输入的弧头或者弧尾不存在
    {
        return;
    }
    // 无论G为有向图还是无向图
    Node *newNode = new Node;
    newNode->next = G.verList[TailIndex].next; // 头插法插入到邻接表中
    newNode->index = HeadIndex;
    G.verList[TailIndex].next = newNode;
    if (!G.isDireted) // G为无向图
    {
        Node *newNode = new Node;
        newNode->next = G.verList[HeadIndex].next; // 头插法插入到邻接表中
        newNode->index = TailIndex;
        G.verList[HeadIndex].next = newNode;
    }
}

void DeleteVex(Graph &G, char v)
{
    int index = Locate(v, G); // 该顶点的下标
    // 释放与该顶点有关的所有边
    Node *p = G.verList[index].next; // 临时指针p指向该顶点邻接表的第一个结点
    while (p != nullptr)
    {
        if (!G.isDireted) // G为无向图
        {
            Node *q = G.verList[p->index].next; // 临时指针q指向待删除结点所在邻接表中的第一个结点
            while (q->next->index != index)     // 一直找，直到找到q的next结点的index值为删除顶点的index
            {
                q = q->next;
            }
            Node *needDel = q->next; // 创建一个临时指针，指向待删除的结点
            q->next = needDel->next; // 保证邻接表不断
            free(needDel);           // 释放空间
        }
        G.verList[index].next = p->next;
        G.arcNum--;
        free(p);
    }
    // 释放顶点
    G.verList[index].nodeData = NULL;
    G.verList[index].next = nullptr;
    G.vertexNum--;
    return;
}

void DeleteArc(Graph &G, char tail, char head)
{
    int TailIndex = Locate(tail, G);
    int HeadIndex = Locate(head, G);
    Node *p = G.verList[TailIndex].next; // 临时指针p指向弧尾顶点邻接表的第一个结点
    while (p->next->index != HeadIndex)
    {
        p = p->next;
    }
    Node *needDel = p->next;
    p->next = needDel->next;
    free(needDel);
    G.arcNum--;
    if (!G.isDireted) // G为无向图
    {
        Node *q = G.verList[HeadIndex].next;
        while (q->next->index != TailIndex)
        {
            q = q->next;
        }
        needDel = q->next;
        q->next = needDel->next;
        free(needDel);
    }
}
void CreateGraph(Graph &G)
{
    cin >> G.vertexNum >> G.arcNum; // 输入顶点数和边数
    cin >> G.isDireted;             // 输入是否为有向图
    if (G.vertexNum > MaxSize)
    {
        return;
    }
    // 初始化顶点列表
    for (int i = 0; i < G.vertexNum; i++)
    {
        cin >> G.verList[i].nodeData;
        G.verList[i].next = nullptr;
    }
    // 依次输入各边的信息
    for (int j = 0; j < G.arcNum; j++)
    {
        char ArcHead, ArcTail;
        cin >> ArcTail >> ArcHead;
        InsertArc(G, ArcTail, ArcHead);
    }
}

void HNodeIndegree(Graph G)
{
    int IndegreeCnt[G.vertexNum] = {0};
    for (int i = 0; i < G.vertexNum; i++)
    {
        Node *tmp = G.verList[i].next;
        while (tmp != nullptr)
        {
            IndegreeCnt[tmp->index]++;
            tmp = tmp->next;
        }
    }
    cout << "all node's indegree" << endl;
    for (int j = 0; j < G.vertexNum; j++)
    {
        cout << G.verList[j].nodeData << ':' << IndegreeCnt[j] << endl;
    }
}

void HNodeOutdegree(Graph G)
{
    int OutdegreeCnt[G.vertexNum] = {0};
    for (int i = 0; i < G.vertexNum; i++)
    {
        Node *tmp = G.verList[i].next;
        while (tmp != nullptr)
        {
            OutdegreeCnt[i]++;
            tmp = tmp->next;
        }
    }
    cout << "all node's outdegree" << endl;
    for (int j = 0; j < G.vertexNum; j++)
    {
        cout << G.verList[j].nodeData << ':' << OutdegreeCnt[j] << endl;
    }
}

void MaxOutDegreeNode(Graph G)
{
    int index = -1; // 出度最大的数组下标
    int res = 0;    // 出度
    // 与HNodeOutdegree同
    // same code
    int OutdegreeCnt[G.vertexNum] = {0};
    for (int i = 0; i < G.vertexNum; i++)
    {
        Node *tmp = G.verList[i].next;
        while (tmp != nullptr)
        {
            OutdegreeCnt[i]++;
            tmp = tmp->next;
        }
    }
    // same code

    for (int j = 0; j < G.vertexNum; j++)
    {
        if (OutdegreeCnt[j] > res)
        {
            res = OutdegreeCnt[j];
            index = j;
        }
    }
    cout << "the max out degree is" << ':' << G.verList[index].nodeData << endl;
}

void ZeroOutdegree(Graph G)
{
    int cnt = 0;
    // same code
    int OutdegreeCnt[G.vertexNum] = {0};
    for (int i = 0; i < G.vertexNum; i++)
    {
        Node *tmp = G.verList[i].next;
        while (tmp != nullptr)
        {
            OutdegreeCnt[i]++;
            tmp = tmp->next;
        }
    }
    // same code
    for (int j = 0; j < G.vertexNum; j++)
    {
        if (OutdegreeCnt[j] == 0)
        {
            cnt++;
        }
    }
    cout << "the number of zero outdegree is" << ' ' << cnt;
}

bool IsArcExist(char a, char b, Graph G)
{
    int AIndex, BIndex; // 找到弧头和弧尾的数组下标
    for (int i = 0; i < G.vertexNum; i++)
    {
        if (G.verList[i].nodeData == a)
        {
            AIndex = i;
            continue;
        }
        if (G.verList[i].nodeData == b)
        {
            BIndex = i;
            continue;
        }
    }
    Node *tmp = G.verList[AIndex].next;
    while (tmp != nullptr)
    {
        if (tmp->index == BIndex)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

int main()
{
    Graph G;
    CreateGraph(G);
    // HNodeIndegree(G);
    // HNodeOutdegree(G);
    // MaxOutDegreeNode(G);
    // ZeroOutdegree(G);
    // char head, tail;
    // cin >> head >> tail;
    // bool isit = IsArcExist(head, tail, G);
    // cout << isit << endl;
    return 0;
}
