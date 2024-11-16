/*
 * @Author: hiddenSharp429 z404878860@163.com
 * @Date: 2023-05-30 19:39:55
 * @LastEditors: hiddenSharp429 z404878860@163.com
 * @LastEditTime: 2023-06-03 12:23:20
 * @FilePath: \appe:\C OR C++\code\HW14.2.cpp
 * @Description: "数据结构作业14-2"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AvlNode
{
    int bf;   // 平衡因子
    int data; // 结点数据
    AvlNode *right;
    AvlNode *left;
} AvlNode, *AvlTree;
// 初始化平衡二叉树
void init(AvlTree &root)
{
    root->bf = 0; // 负一表示没有值
    root->right = nullptr;
    root->left = nullptr;
    root->data = NULL;
}
// 旋转树
void rotate(AvlNode **node, const char *type)
{
    // 使用strcmp判断字符串相等
    if (strcmp(type, "LL") == 0)
    {
        AvlNode *tmp = (*node)->left;
        (*node)->left = tmp->right;
        tmp->right = (*node);
        (*node) = tmp;
    }
}
// 检查插入的结点的父节点的双亲结点是否不平衡了
void checkBF(AvlNode *root, AvlNode *insertNode)
{
    AvlNode *parent = nullptr;      // 父节点
    AvlNode *grandparent = nullptr; // 祖父节点

    AvlNode *current = root;
    while (current != insertNode)
    {
        grandparent = parent;
        parent = current;

        if (insertNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    // 根据父节点和祖父节点的平衡因子判断需要进行的旋转类型
    if (grandparent != nullptr)
    {
        if (grandparent->bf == 2 && parent == grandparent->left && current == parent->left)
            rotate(&grandparent, "LL");
        else if (grandparent->bf == 2 && parent == grandparent->right && current == parent->right)
            rotate(&grandparent, "LR");
        else if (grandparent->bf == -2 && parent == grandparent->right && current == parent->right)
            rotate(&grandparent, "RR");
        else if (grandparent->bf == -2 && parent == grandparent->left && current == parent->left)
            rotate(&grandparent, "RL");
    }
}
// 计算树的深度
int treeDepth(AvlTree root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftDepth = treeDepth(root->left);
    int rightDepth = treeDepth(root->right);
    return (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
}
// 计算BF
int calculateBalanceFactor(AvlTree node)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftDepth = treeDepth(node->left);
    int rightDepth = treeDepth(node->right);
    return leftDepth - rightDepth;
}
// 更新BF
void updataBF(AvlTree &root)
{
    if (root == NULL)
    {
        return;
    }
    updataBF(root->left);
    updataBF(root->right);
    root->bf = calculateBalanceFactor(root);
}
// 插入结点
void insetAvlNode(AvlTree &root, int data)
{
    // PTmp是父节点临时指针、CTmp是孩子结点临时指针，它们初始都是root
    AvlNode *PTmp, *CTmp;
    PTmp = CTmp = root;

    // 创建一个新的结点并且初始化它
    AvlNode *newNode = new AvlNode;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->bf = 0;

    // 根节点还没有数据
    if (root->data == 0)
    {
        root->data = data;
        return;
    }
    // 根节点已经有数据了
    else
    {
        while (CTmp != nullptr) // 只要CTmp不为空就一直循环
        {
            if (data < CTmp->data)
            {
                PTmp = CTmp;
                CTmp = CTmp->left;
            }
            else
            {
                PTmp = CTmp;
                CTmp = CTmp->right;
            }
        } // 结束while循环后CTmp为空，PTmp为将要插入结点的父节点
        if (data < PTmp->data)
        {
            PTmp->left = newNode;
            updataBF(root);
        }
        if (data > PTmp->data)
        {
            PTmp->right = newNode;
            updataBF(root);
        }
        checkBF(root, newNode);
    }
}
// 创建一个平衡二叉树
void buildAvlTree(AvlTree &root)
{
    int data; // 接收的数据
    printf("请依次输入个结点的值用回车分割用0结束\n");
    while (scanf("%d", &data) && data != 0)
    {
        insetAvlNode(root, data);
    }
    return;
}
// 求平衡二叉树的高度
int AvlTreeHeight(AvlTree root)
{
    int height = 0;
    if (root->left == nullptr && root->right == nullptr) // 或root->bf == 0也行
    {
        return 1; // 若只有根节点则返回高度为1
    }

    while (root != nullptr) // 一直为空才停止
    {
        if (root->bf == 1 && root->bf == 0)
        {
            root = root->left;
            height++;
        }
        else
        {
            root = root->right;
            height++;
        }
    }
    return height;
}

int main()
{
    AvlTree root = new AvlNode;
    init(root);
    buildAvlTree(root);
    free(root);
    return 0;
}