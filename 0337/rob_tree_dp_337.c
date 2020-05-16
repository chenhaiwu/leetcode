/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/* �T�ĺ�k�A�Q�μɤO�A�ɤO+??�ơ]�`�N?��??�ƥi�H�ɧU���ޥ��A��?�Ȧs�ۤ�?�^�A
 * �V??�E�]?�O��?���A�������Q��?�ŚV�W���Z�q�A��????����^�ȡ^ */

int Max(int a, int b)
{
    if (a < b) {
        return b;
    }
    return a;
}

int rob_baoli(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    int money = root->val;
    if (root->left) {
        money += rob(root->left->left) + rob(root->left->right);
    }
    if (root->right) {
        money += rob(root->right->left) + rob(root->right->right);
    }
    int money2 = rob(root->left) + rob(root->right);
    return Max(money2, money);
}

/* ??�ƺ�k�A�����a�Q��?�򪺭ȡA�p�G??�A��ܤw�r��?�F�A���A�D */
int rob(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    if (root && root->val < 0) {
        return -root->val;
    }
    int money = root->val;
    if (root->left) {
        money += rob(root->left->left) + rob(root->left->right);
    }
    if (root->right) {
        money += rob(root->right->left) + rob(root->right->right);
    }
    int money2 = rob(root->left) + rob(root->right);
    int ans = Max(money2, money);
    root->val = -ans;
    return ans;
}

/*
��??�@��?�k?�w�妹??
�C��?��i??���Ύͤ�������??�A���u?�طN��A��??�򤣯�@����

?�e?��??��?�A���\�ΟīĤl?��N����??���F
?�e?��??����?�A�ΟīĤl?��u�ݭn���̦h��?�X?�N��(�ΟīĤl?�򰽤���??�t)
��?�ϥΤ@�Ĥj�p?2��???��� int[] res = new int[2] 0�N�����A1�N��
����@��?��ఽ�쪺�̤j?��??�i�H�w��?

?�e?��??����: ?�e?��ఽ�쪺�̤j?? = ���Ĥl�ఽ�쪺? + �k�Ĥl�ఽ�쪺?
?�e?��??��: ?�e?��ఽ�쪺�̤j?? = ���Ĥl??�ۤv����?��o�쪺? + �k�Ĥl??����?��o�쪺? + ?�e?��??
���?�����p�U

root[0] = Math.max(rob(root.left)[0], rob(root.left)[1]) + Math.max(rob(root.right)[0], rob(root.right)[1])
root[1] = rob(root.left)[0] + rob(root.right)[0] + root.val;
*/

typedef struct _steel {
    int unsteal;
    int steal;
} Steal;

void robInternel(struct TreeNode* root, Steal *s)
{
    Steal sleft = {0, 0};
    if (root->left) {
        robInternel(root->left, &sleft);
    }
    Steal sright = {0, 0};
    if (root->right) {
        robInternel(root->right, &sright);
    }
    s->unsteal = Max(sleft.unsteal, sleft.steal) + Max(sright.unsteal, sright.steal);
    s->steal = root->val + sleft.unsteal + sright.unsteal;
    return;
}

int rob_3_dp(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }

    Steal s = {0, 0};
    robInternel(root, &s);
    return Max(s.unsteal, s.steal);
}