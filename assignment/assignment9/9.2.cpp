#include <stdio.h>
// 孩子结点
struct CNode
{
    int index;
    struct CNode *Next;
};
//
struct CLinkArr
{
    char data;
    struct CNode *firstChild;
};
// 孩子链树
struct CTree
{
    int NodeNum;
    int root;
    struct CLinkArr node[20];
};

void initChildTree(CTree &tree)
{
    tree.NodeNum = 0;
    tree.root = -1;
    for (int i = 0; i < 20; i++)
    {
        tree.node[i].data = NULL;
        tree.node[i].firstChild = nullptr;
    }
    
}
//创建二叉树
void createChildTree(CTree &tree)
{
    tree.root = 0;
    tree.node[tree.root].data = 'R';
    tree.node[tree.root + 1].data = 'A';
    tree.node[tree.root + 2].data = 'B';
    tree.node[tree.root + 3].data = 'C';
    tree.node[tree.root + 4].data = 'D';
    tree.node[tree.root + 5].data = 'E';
    tree.node[tree.root + 6].data = 'F';
    tree.node[tree.root + 7].data = 'G';
    tree.node[tree.root + 8].data = 'H';
    tree.node[tree.root + 9].data = 'K';

    tree.node[tree.root].firstChild = new CNode;
    tree.node[tree.root].firstChild->index = 1;
    tree.node[tree.root].firstChild->Next = new CNode;
    tree.node[tree.root].firstChild->Next->index = 2;
    tree.node[tree.root].firstChild->Next->Next = new CNode;
    tree.node[tree.root].firstChild->Next->Next->index = 3;
    tree.node[tree.root].firstChild->Next->Next->Next = nullptr;

    tree.node[tree.root + 1].firstChild = new CNode;
    tree.node[tree.root + 1].firstChild->index = 4;
    tree.node[tree.root + 1].firstChild->Next = new CNode;
    tree.node[tree.root + 1].firstChild->Next->index = 5;
    tree.node[tree.root + 1].firstChild->Next->Next = nullptr;

    tree.node[tree.root + 2].firstChild = nullptr;

    tree.node[tree.root + 3].firstChild = new CNode;
    tree.node[tree.root + 3].firstChild->index = 6;
    tree.node[tree.root + 3].firstChild->Next = nullptr;

    tree.node[tree.root + 6].firstChild = new CNode;
    tree.node[tree.root + 6].firstChild->index = 7;
    tree.node[tree.root + 6].firstChild->Next = new CNode;
    tree.node[tree.root + 6].firstChild->Next->index = 8;
    tree.node[tree.root + 6].firstChild->Next->Next = new CNode;
    tree.node[tree.root + 6].firstChild->Next->Next->index = 9;
    tree.node[tree.root + 6].firstChild->Next->Next->Next = nullptr;

    tree.NodeNum = 10;
}

int LeafNodeNumber(CTree &tree){
    int cnt = 0;
    for (int i = 0; i < tree.NodeNum; i++)
    {
        if (tree.node[i].data != NULL && tree.node[i].firstChild == nullptr)
        {
            cnt++;
        }        
    }
    return cnt;
}

int LeafDegreeIsK(CTree &tree, int k){
    int cnt = 0;
    for ( int i = 0; i < tree.NodeNum; i++)
    {
        int childNodeNum = 0;
        CNode *tmp = tree.node[i].firstChild;
        while (tmp != nullptr)
        {
            tmp = tmp->Next;
            childNodeNum ++;
        }
        if (childNodeNum == k)
        {
            cnt++;
        }
    }
    return cnt;
}

int main()
{
    CTree tree;
    initChildTree(tree);
    createChildTree(tree);
    int leafNodeCnt = LeafNodeNumber(tree);
    printf("树中叶子结点的个数为%d\n", leafNodeCnt);
    printf("请输入k的值");
    int k;
    scanf("%d", &k);
    int NodeDegreeisK = LeafDegreeIsK(tree, k);
    printf("树中度为%d的结点个数为%d", k, NodeDegreeisK);
    return 0;
}
