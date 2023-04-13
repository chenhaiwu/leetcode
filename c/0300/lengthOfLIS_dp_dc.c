#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/* 超时 其实就是遇到一个元素，如果可选的话，求出选，和不选的大小，取更大者
int lengthOfLoop(int *nums, int numsSize, int prev, int curPos)
{
    if (curPos == numsSize) {
        return 0;
    }
    int taken = 0;
    if (nums[curPos] > prev) {
        taken = 1 + lengthOfLoop(nums, numsSize, nums[curPos], curPos + 1);
    }
    int notaken = lengthOfLoop(nums, numsSize, prev, curPos + 1);
    return taken > notaken ? taken : notaken;
}

int lengthOfLIS(int* nums, int numsSize)
{
    //memset(g_memo, -1, sizeof(g_memo));
    // if (numsSize > 20) return 0;
    int max = lengthOfLoop(nums, numsSize, INT_MIN, 0);
    return max;
}
*/

/* 其实就是遇到一个元素，如果可选的话，求出选，和不选的大小，取更大者，加上记忆化，主要特点是从-1开始记，这样到0，就刚好记上 */
/*
#define MAXNUM 2501 //调试出来的最小值
int g_memo[MAXNUM][MAXNUM];

int lengthOfLoop(int *nums, int numsSize, int prev, int curPos)
{
    if (curPos == numsSize) {
        return 0;
    }
    if (g_memo[prev + 1][curPos] > 0) {
        return g_memo[prev + 1][curPos];
    }
    int taken = 0;
    if (prev < 0 || nums[curPos] > nums[prev]) {
        taken = 1 + lengthOfLoop(nums, numsSize, curPos, curPos + 1);
    }
    int notaken = lengthOfLoop(nums, numsSize, prev, curPos + 1);
    g_memo[prev + 1][curPos] = taken > notaken ? taken : notaken;
    return g_memo[prev + 1][curPos];
}

int lengthOfLIS(int* nums, int numsSize)
{
    memset(g_memo, -1, sizeof(g_memo));

    int max = lengthOfLoop(nums, numsSize, -1, 0);
    return max;
}
*/

/* dp 算法，主要是思路是：dp[i] 表示第i个位置的，是最大值为多少，则一定等前面所有比num[i]小的元素，其中的最大值+1 */
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MAXNUM 2501 //调试出来的最小值
int g_dp[MAXNUM];
int lengthOfLIS(int* nums, int numsSize)
{
    int max = 0;
    memset(g_dp, 0x0, sizeof(int) * numsSize);
    g_dp[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        int maxTmp = 0;
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                maxTmp = MAX(maxTmp, g_dp[j]);
            }
        }
        g_dp[i] = maxTmp + 1;
        max = MAX(max, g_dp[i]);
    }
    return max;
}


int main()
{
    int nums[] = {10,9,2,5,3,7,101,18};
    int ret = lengthOfLIS(nums, sizeof(nums) / sizeof(int));
    printf("ret=%d\n", ret);
    return ret;
}