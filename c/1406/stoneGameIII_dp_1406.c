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


#define MAX_N 50001
#define STATEP 2
/*
定义dp[i]的意义为从stoneValue[i]到stoneValue[N-1]这堆石头里，从i开始取石头的人所能够拿到的最多石头数。
因为从i开始取石头的人可以取1、2或3堆石头，然后下一个人取到的最多石头数就分别是dp[i+1]、dp[i+2]和dp[i+3]，
为了使从i开始取得的石头最多，等价于使下一个人取得的石头数最少即min(dp[i+1], dp[i+2], dp[i+3])，
此时从i开始取得的最多石头数为\sum_{j=i}^{N-1}stoneValue[j]-min(dp[i+1], dp[i+2], dp[i+3])∑ 
j=i
N−1 stoneValue[j]−min(dp[i+1],dp[i+2],dp[i+3])。
*/


int g_dp[MAX_N];
int g_sum;

int Dp(int* piles, int pilesSize)
{
    int n = pilesSize;

    g_dp[n] = 0;
    g_dp[n - 1] = piles[n - 1];
    g_sum = piles[n - 1];
    if (n - 2 >= 0) {
        g_sum += piles[n - 2];
        g_dp[n - 2] = g_sum - MIN(g_dp[n], g_dp[n - 1]);
    }
    for (int i = n - 3; i >= 0; i--) {
        g_sum += piles[i];
        int t1 = MIN(g_dp[i + 2], g_dp[i + 1]);
        int t2 = MIN(t1, g_dp[i + 3]);
        g_dp[i] = g_sum - t2;
    }

    return g_dp[0];
}

char * stoneGameIII(int* piles, int pilesSize)
{
    int ans;
    int n = pilesSize;

    memset(g_dp, INT_MIN, sizeof(int) * (n + 1));
    // for (int i = 0 ; i <= n; i++) g_dp[i] = INT_MIN;
    g_sum = 0;

    ans = Dp(piles, pilesSize);

    int ans2 = g_sum - ans;
    if (ans == ans2) {
        return "Tie";
    } else if (ans > ans2) {
        return "Alice";
    } else {
        return "Bob";
    }
}

// int main()
// {
//     char *ans;
//     int a[] = {1,2,3,-9};
//     ans = stoneGameIII(a, sizeof(a) / sizeof(int));
//     printf("ans=%s\n", ans);
//     return 0;
// }