/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

// #include "securec.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

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


#define MAX_N 501
#define STATEP 2
// 表示从i->j 这些位置，0先选，最大值，1后选的最大值
int g_dp[MAX_N][MAX_N][STATEP];

int Step(int l, int r, int s, int* piles)
{
    // printf("s=%d\n", s);
    if (l > r) return 0;
    if (l == r) {
        g_dp[l][r][s] = piles[l];
        return g_dp[l][r][s];
    }
    if (g_dp[l][r][s] != 0) return g_dp[l][r][s];
    int ans1 = piles[l] - Step(l + 1, r, s ^ 1, piles);
    int ans2 = piles[r] - Step(l, r - 1, s ^ 1, piles);
    int ans = MAX(ans1, ans2);
    g_dp[l][r][s] += ans;
    return g_dp[l][r][s];
}

bool Dfs(int* piles, int pilesSize)
{
    int n = pilesSize;
    memset(g_dp, 0x0, sizeof(g_dp));

    int ans = Step(0, n - 1, 0, piles);
    return ans > 0;
}

bool Dp(int* piles, int pilesSize)
{
    int n = pilesSize;
    memset(g_dp, 0x0, sizeof(g_dp));

    // 初始状态，如果i==j，表示只有一个点，先选的人值相等，后选的人为0
    for (int i = 0; i < n; i++) {
        g_dp[i][i][0] = piles[i];
        g_dp[i][i][1] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = len + i - 1;
            int left = piles[i] + g_dp[i + 1][j][1];
            int right = piles[j] + g_dp[i][j - 1][1];
            if (left > right) {
                g_dp[i][j][0] = left;
                g_dp[i][j][1] = g_dp[i + 1][j][0];
            } else {
                g_dp[i][j][0] = right;
                g_dp[i][j][1] = g_dp[i][j - 1][0];
            }
        }
    }
    return g_dp[0][n - 1][0] - g_dp[0][n - 1][1];
}

bool stoneGame(int* piles, int pilesSize)
{
    bool ans;

    // ans = Dp(piles, pilesSize);

    ans = Dfs(piles, pilesSize);
    return ans;
}

// int main()
// {
//     int ans;
//     int a[] = {5,3,4,5};
//     ans = stoneGame(a, sizeof(a) / sizeof(int));
//     printf("ans=%d\n", ans);
//     return 0;
// }