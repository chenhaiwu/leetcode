/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/* ¤TŸÄºâªk¡A§Q¥Î¼É¤O¡A¼É¤O+??¤Æ¡]ª`·N?ªº??¤Æ¥i¥H­É§Uªº§Þ¥©¡A­ì?­È¦s¬Û¤Ï?¡^¡A
 * ‰V??¦E¡]?ÉO¤£?ªº¡A¥©§®ªº§Q¥Î?ªÅšV¤Wªº‰Z¶q¡A¥Î????ªºªð¦^­È¡^ */

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

/* ??¤Æºâªk¡A¥©§®¦a§Q¥Î?˜òªº­È¡A¦pªG??¡Aªí¥Ü¤w‰rºâ?¤F¡A¤£¦A¨D */
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
§Ú??¤@Ïú?ªk?©wúå¦¹??
¨CŸÄ?˜ò¥i??°½©ÎŽÍ¤£°½‰ÎÏú??¡A®ÚÕu?¥Ø·N«ä¡A¬Û??˜ò¤£¯à¤@þ°½

?«e?˜ò??°½?¡A¨º¤\‰ÎŸÄ«Ä¤l?˜ò´N¤£¯à??°½¤F
?«e?˜ò??¤£°½?¡A‰ÎŸÄ«Ä¤l?˜ò¥u»Ý­n®³³Ì¦hªº?¥X?´N¦æ(‰ÎŸÄ«Ä¤l?˜ò°½¤£°½??¨t)
§Ú?¨Ï¥Î¤@ŸÄ¤j¤p?2ªº???ªí¥Ü int[] res = new int[2] 0¥Nªí¤£°½¡A1¥Nªí°½
¥ô¦ó¤@ŸÄ?˜ò¯à°½¨ìªº³Ì¤j?ªº??¥i¥H©wúå?

?«e?˜ò??¤£°½: ?«e?˜ò¯à°½¨ìªº³Ì¤j?? = ¥ª«Ä¤l¯à°½¨ìªº? + ¥k«Ä¤l¯à°½¨ìªº?
?«e?˜ò??°½: ?«e?˜ò¯à°½¨ìªº³Ì¤j?? = ¥ª«Ä¤l??¦Û¤v¤£°½?¯à±o¨ìªº? + ¥k«Ä¤l??¤£°½?¯à±o¨ìªº? + ?«e?˜òªº??
ªí¥Ü?¤½¦¡¦p¤U

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