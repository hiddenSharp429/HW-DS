#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 输入二叉树
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

void FindLongesetPath(TreeNode *node, int length, int *MaxLength, int *currentPath, int *longestPath)
{
    // 该节点不存在
    if (node == NULL)
        return;
    // 该结点存在
    else
    {
        // 先记录当前结点的值，随后长度加一
        currentPath[length] = node->val;
        length = length + 1;
        // 已经到达叶子节点
        if (node->left == NULL && node->right == NULL)
        {
            if (*MaxLength < length)
            {
                *MaxLength = length;
                for (int i = 0; i < *MaxLength; i++) // 更新最长路径
                {
                    longestPath[i] = currentPath[i];
                }
            }
            return;
        }
        // 还有子结点
        else
        {
            FindLongesetPath(node->left, length, MaxLength, currentPath, longestPath);
            FindLongesetPath(node->right, length, MaxLength, currentPath, longestPath);
        }
    }
}

int main()
{
    int maxLength = 0;
    int Length = 0;
    int currentPath[20]; // 当前路径
    int longestPath[20]; // 最长路径
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    // 输入二叉树
    inputTree(root);
    FindLongesetPath(root, Length, &maxLength, currentPath, longestPath); // 查找第一个最长的路径
    printf("第一个最长路径上的结点为：");
    for (int i = 0; i < maxLength; i++)
    {
        printf("%d ", longestPath[i]);
    }
    return 0;
}