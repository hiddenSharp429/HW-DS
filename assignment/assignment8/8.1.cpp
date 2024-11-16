#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 统计具有度为1的节点数目的函数
int count(TreeNode *root)
{
    if (!root)
    {
        return 0;
    }
    // 创建一个队列用于存储待访问的节点
    TreeNode **queue = (TreeNode **)malloc(sizeof(TreeNode *) * 100);
    int front = 0, rear = 0; // 队列的前后指针
    int count = 0;           // 度为1的节点数目
    queue[rear++] = root;    // 将根节点入队
    while (front < rear)
    {
        TreeNode *node = queue[front++]; // 取出队头节点
        int degree = 0;
        // 检查当前节点的左右子节点，如果存在则加入队列
        if (node->left)
        {
            degree++;
            queue[rear++] = node->left;
        }
        if (node->right)
        {
            degree++;
            queue[rear++] = node->right;
        }
        // 如果当前节点的度为1，则将计数器加1
        if (degree == 1)
        {
            count++;
        }
    }

    free(queue); // 释放队列内存

    return count;
}
void inputTree(TreeNode *root)
{
    root->val = 1;
    root->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->left->val = 2;
    root->left->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->left->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->left->left->val = 4;
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->left->right->val = 5;
    root->left->right->left = NULL;
    root->left->right->right = NULL;

    root->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->val = 3;
    root->right->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->left->val = 6;
    root->right->left->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->left->left->val = 8;
    root->right->left->left->left = NULL;
    root->right->left->left->right = NULL;
    root->right->left->right = NULL;
    root->right->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->right->val = 7;
    root->right->right->left = NULL;
    root->right->right->right = NULL;
}

int main()
{
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    //输入二叉树
    inputTree(root);
    // 统计具有度为1的节点数目并输出结果
    int res = count(root);
    printf("%d\n", res);
    return 0;
}
