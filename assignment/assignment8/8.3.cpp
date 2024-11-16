#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

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

void LeafToRoot(TreeNode *node, int length, int *Path)
{
    // 结点不存在
    if (node == NULL)
        return;
    // 结点存在
    else
    {
        Path[length] = node->val;
        length = length + 1;
        // 该结点为叶子结点
        if (node->left == NULL && node->right == NULL)
        {
            // 输出路径上每个结点的值
            for (int i = 0; i < length; i++)
            {
                printf("%d ", Path[i]);
            }
            printf("\n");
        }
        else
        {
            LeafToRoot(node->left, length, Path);
            LeafToRoot(node->right, length, Path);
        }
    }
}
int main()
{
    int Path[20];
    int length = 0;
    TreeNode *root = new TreeNode;
    inputTree(root);
    LeafToRoot(root, length, Path);
    return 0;
}