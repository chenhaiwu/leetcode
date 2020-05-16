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

/* ¬O§_¦³®Äªº¤G¤e·j¯Á?¡A­n¨D¥ª«Ä¤l¤p¤_®Ú¡A¥k«Ä¤l¤j¤£¤Ñ®Ú */
bool Dfs(struct TreeNode* root)
{
    /* ¦}¤£¬O??ªº¥ª¥k«Ä¤l¤ñ¤j¤p´N¦n¤F¡A?­n·Ó?¥ª«Ä¤l¤¤¤U­±?¤l?˜ò¤]¤ñ???˜ò¤p */
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