#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/**
 * Definition for a binary tree node.
 * /
 */ 
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#define MAX_N 10000
int g_midorder[MAX_N];
int g_len;

#define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

void PreHandle()
{
    memset(g_midorder, 0, sizeof(g_midorder));
    g_len = 0;
}

void MidOrder(struct TreeNode* root)
{
    if (!root) {
        return;
    }

    MidOrder(root->left);
    g_midorder[g_len++] = root->val;
    MidOrder(root->right);
}

bool AfterHandler()
{
    // PrintArray(g_midorder, g_len);
    bool ans = true;
    for (int i = 1; i < g_len; i++) {
        if (g_midorder[i] <= g_midorder[i - 1]) {
            ans = false;
            break;
        }
    }
    return ans;
}

bool Step3(struct TreeNode* root, long long low, long long high)
{
    if (!root) return true;
    long long val = root->val;
    if (val <= low || val >= high) return false;
    return Step3(root->left, low, root->val) && Step3(root->right, root->val, high);
}

/* 是否有效的二叉搜索?，要求左孩子小于根，右孩子大不天根 */
bool Dfs(struct TreeNode* root)
{
    /* 并不是??的左右孩子比大小就好了，?要照?左孩子中下面?子?�礞]比???�礞p */
    bool ret;
    // ret = Step(root);

    // PreHandle();
    // MidOrder(root);
    // ret = AfterHandler();

    ret = Step3(root, LLONG_MIN, LLONG_MAX);

    return ret;
}

bool isValidBST(struct TreeNode* root)
{
    bool ans = false;
    ans = Dfs(root);
    return ans;
}