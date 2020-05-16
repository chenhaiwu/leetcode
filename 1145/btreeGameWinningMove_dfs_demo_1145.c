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

void FindNode(struct TreeNode* root, int x, struct TreeNode* sel)
{
    if (root->val == x) {
        sel = root;
        return;
    }
    if (!root->left) {
        FindNode(root->left, x, sel);
        return;
    }
    if (!root->right) {
        FindNode(root->right, x, sel);
        return;
    }
    return;
}

int Step(struct TreeNode* root)
{
    if (!root) {
        return 0;
    }
    return 1 + Step(root->left) + Step(root->right);
}

/* 因为每次选择只能在上一次选择的左右父结点中选择一个，
 * 所以当A先选后，B的选择，只要从这个点的左右孩子，父亲点中选择一个，他们的结点的连通数量大于一半就胜利 */
int Dfs(struct TreeNode* root, int n, int x)
{
    struct TreeNode sel;
    FindNode(root, x, &sel);
    int lefts = Step(sel.left);
    int rights = Step(sel.right);
    int parents = n - lefts - rights - 1;
    int half = n / 2;
    if (lefts > half || rights > half || parents > half) {
        return true;
    } else {
        return false;
    }
}

bool btreeGameWinningMove(struct TreeNode* root, int n, int x)
{
    bool ans = false;
    ans = Dfs(root, n, x);
    return ans;
}

void main()
{
    int ans;
    ans = findPaths(2, 2, 2, 0, 0);
    printf("ans=%d\n", ans);
    ans = findPaths(1, 3, 3, 0, 1);
    printf("ans=%d\n", ans);
    ans = findPaths(2, 2, 2, 0, 1);
    printf("ans=%d\n", ans);
    return;
}