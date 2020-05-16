#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

// #include "securec.h"

/**
 * Definition for a binary tree node.
 * /
 */ 
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int g_ans;

int Max(int i, int j)
{
    return i > j ? i : j;
}

int Dfs(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    int left = Dfs(root->left);
    left = Max(left, 0);
    int right = Dfs(root->right);
    right = Max(right, 0);
    g_ans = Max(g_ans, root->val + left + right);
    return root->val + Max(left, right);
}

int maxPathSum(struct TreeNode* root)
{
    g_ans = INT_MIN;
    Dfs(root);
    return g_ans;
}