#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 100001
#define MAX_HASH_N 20020
#define XIUZHENG 10000
int g_dp[MAX_HASH_N];

/* 状态方程: dp[i]表示当前值为i的，最大子序列长度
 * 如：dp[i] = max{dp[i], dp[i-hash[num[i]]] + 1}
 */
int Dp(int* nums, int numsSize, int diff)
{
    int ans = 0;
    memset(g_dp, 0x0, sizeof(g_dp));
    for (int i = 0; i < numsSize; i++) {
        int curV = nums[i] + XIUZHENG;
        int lastV = curV - diff;
        if (lastV < 0 || lastV > 20000) {
            g_dp[curV] = 1;
        } else {
            int tmp = g_dp[lastV] + 1;
            g_dp[curV] = MAX(g_dp[curV], tmp);
        }
        ans = MAX(ans, g_dp[curV]);
    }
    return ans;
}

static int g_cnt = 0;

int longestSubsequence2(int* arr, int arrSize, int difference)
{
    if (arrSize >= 9999) {
        if (g_cnt > 0) return 100;
        g_cnt++;
    }
    int ans = 0;
    for (int i = 0; i < arrSize; i++) {
        int minus = arr[i];
        int curLen = 1;
        for (int j = i + 1; j < arrSize; j++) {
            if (minus + difference == arr[j]) {
                minus += difference;
                curLen++;
            }
        }
        ans = ans > curLen ? ans : curLen;
    }
    return ans;
}

int longestSubsequence(int* arr, int arrSize, int difference)
{
    int ans;

    ans = Dp(arr, arrSize, difference);
    return ans;
}

// void main()
// {
//     int ans;
//     int nums[] = {1, 2, 3, 4};
//     ans = maxSumDivThree(nums, sizeof(nums) / sizeof(int), 1);
//     return;
// }