// 完成用十字链表存储的稀疏矩阵的加法运算。
typedef struct OLNode
{
    int i;
    int j;
    int e;
    struct OLNode *right;
    struct OLNode *down;
} OLNode, *OLink;

typedef struct
{
    OLink *rhead;
    OLink *chead;
    int mu; // 行数
    int nu; // 列数
    int tu;
} CrossList;

void addArray(CrossList &a, CrossList b)
{
    int cnt = a.tu + b.tu; // 统计一共有多少个非零数
    int i = 1;
    // int j1, j2;
    while (cnt > 0) // 当还有数没加时继续循环
    {
        OLink p = a.rhead[i];
        OLink q = b.rhead[i];

        if (!p && q) // p当前行无元素，q有元素，则将q赋给p
            p = q;
        if (!p && !q) // p、q当前行均无元素，则跳转下一行
            continue;
        if (p && !q) // p有元素，q无元素，则跳转下一行
            continue;
        if (p && q) // p、q均有元素，则进行加法
        {
            do
            {
                if (p->j < q->j)
                {
                    cnt--;        // cnt减一
                    if (p->right) // p的右元素不为空
                    {
                        p = p->right; // 工作指针p向右移
                    }
                    else
                    {
                        p->right = q; // q当前行的所有元素接到p的后面
                    }
                }
                else if (p->j == q->j)
                {
                    p->e = p->e + q->e;
                    p = p->right;
                    q = q->right;  // p、q同时向右移动
                    cnt = cnt - 2; // cnt减二
                }
                else
                {
                    OLink tmp1 = p;
                    p = q;                 // a.rhead[i]指向q的节点
                    OLink tmp2 = q->right; // 将q的右节点的指针保存
                    q->right = tmp1;       // q的右指针指向p
                    cnt--;
                    if (tmp2) // 若q的右节点不为空
                    {
                        q = tmp2; // 工作指针q向右移
                    }
                }
            } while (!p->right); // 当工作指针为当前行的最后一个元素时退出循环
        }

        i++; // 转移到下一行
    }
}