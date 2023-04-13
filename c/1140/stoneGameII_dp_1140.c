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

int MAX(int a, int b)
{
    return a > b ? a : b;
}
int MIN(int a, int b)
{
    return a < b ? a : b;
}

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


#define MAX_N 101
#define STATEP 2
// 表示从i->j 这些位置，0先选，最大值，1后选的最大值
int g_dp[MAX_N][MAX_N];
int g_sum[MAX_N];

int Dp(int* piles, int pilesSize)
{
    int n = pilesSize;
    memset(g_dp, 0x0, sizeof(g_dp));
    memset(g_sum, 0x0, sizeof(g_sum));
    for (int i = 0; i < n; i++) {
        g_sum[i + 1] = g_sum[i] + piles[i];
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int tmpSum = g_sum[n] - g_sum[n - i];
            for (int k = 1; k <= MIN(i, 2 * j); k++) {
                int t = MAX(k, j);
                g_dp[i][j] = MAX(g_dp[i][j], tmpSum - g_dp[i - k][t]);
            }
        }
    }

    return g_dp[n][1];
}

int stoneGameII(int* piles, int pilesSize)
{
    int ans;

    ans = Dp(piles, pilesSize);

    // ans = Dfs(piles, pilesSize);
    return ans;
}

// int main()
// {
//     int ans;
//     int a[] = {2,7,9,4,4};
//     ans = stoneGameII(a, sizeof(a) / sizeof(int));
//     printf("ans=%d\n", ans);
//     return 0;
// }