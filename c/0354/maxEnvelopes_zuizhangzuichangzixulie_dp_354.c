#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int Max(int a, int b)
{
    if (a < b) {
        return b;
    }
    return a;
}

int Min(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

/* 套娃问题是，因为要满足两个条件， w,h都递增，所以考虑先快排一下，两个元素都考虑。
 * 这样w满足条件（注意还有一个不能相等），然后变成了求h的数组的最长子序列问题
 * 求最长子序列问题：可以使用动态规划标定当前位置i，然后从j-> [0,i)，开始找每个符合条件的最大值
 */
typedef struct _node {
    int w;
    int h;
} MyNode;
// MyNode g_node[MAX_NODE_N];

#define MAX_N 50001
int g_dp[MAX_N];

int Cmp(const void *a, const void *b)
{
    int* ta = *(int **)a;
    int* tb = *(int **)b;
    if (ta[0] == tb[0]) {
        return ta[1] - tb[1];
    }
    return ta[0] - tb[0];
}

int Dp(int** e, int n)
{
    memset(g_dp, 0x0, sizeof(g_dp));
    qsort(e, n, sizeof(e[0]), Cmp);
    g_dp[0] = 1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int curMax = 0;
        for (int j = 0; j < i; j++) {
            if (e[i][0] > e[j][0] && e[i][1] > e[j][1]) {
                curMax = Max(curMax, g_dp[j]);
            }
        }
        g_dp[i] = curMax + 1;
        ans = Max(ans, g_dp[i]);
    }
    return ans;
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize)
{
    int ans;
    if (envelopesSize == 0) return 0;
    ans = Dp(envelopes, envelopesSize);
    return ans;
}