#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 40001
int g_dp[MAX_N][3];

/* 状态方程: 有三个状态，0、1、2
 * 每个状态分别转移，在遇到新i元素时，每个状态都检查一下，看是否选择
 * 看0状态，如：dp[i][0] = max{dp[i-1][0], dp[i-1][0] + nums[i] (nums[i]%3==0)}
 * 或者 dp[i][0] = max{dp[i-1][0], dp[i-1][1] + nums[i](i %3 ==2)}
 * 或者 dp[i][0] = max{dp[i-1][0], dp[i-1][2] + nums[i](i%3==1)}
 * 说明0状态，的最大值，有三行，第一个元素，都表示不选。
 * 如果选的话，要受两个条件影响，当前nums[i]元素与前一个的另外状态相加，刚好为3的位数
 * 同样，求dp[n][0] 还受前面1、2的状态影响，所以都要求。
 */
int Dp(int* nums, int numsSize)
{
    int ans = 0;
    memset(g_dp, 0x0, sizeof(int) * (numsSize + 1));
    g_dp[0][1] = INT_MIN;
    g_dp[0][2] = INT_MIN;
    for (int i = 1; i <= numsSize; i++) {
        if (nums[i - 1] % 3 == 0) {
            g_dp[i][0] = MAX(g_dp[i - 1][0], g_dp[i - 1][0] + nums[i - 1]);
            g_dp[i][1] = MAX(g_dp[i - 1][1], g_dp[i - 1][1] + nums[i - 1]);
            g_dp[i][2] = MAX(g_dp[i - 1][2], g_dp[i - 1][2] + nums[i - 1]);
        } else if (nums[i - 1] % 3 == 1) {
            g_dp[i][0] = MAX(g_dp[i - 1][0], g_dp[i - 1][2] + nums[i - 1]);
            g_dp[i][1] = MAX(g_dp[i - 1][1], g_dp[i - 1][0] + nums[i - 1]);
            g_dp[i][2] = MAX(g_dp[i - 1][2], g_dp[i - 1][1] + nums[i - 1]);
        } else {
            g_dp[i][0] = MAX(g_dp[i - 1][0], g_dp[i - 1][1] + nums[i - 1]);
            g_dp[i][1] = MAX(g_dp[i - 1][1], g_dp[i - 1][2] + nums[i - 1]);
            g_dp[i][2] = MAX(g_dp[i - 1][2], g_dp[i - 1][0] + nums[i - 1]);
        }
    }
    return g_dp[numsSize][0];
}

int maxSumDivThree(int* nums, int numsSize)
{
    int ans;

    ans = Dp(nums, numsSize);
    return ans;
}

void main()
{
    int ans;
    int nums[] = {3, 6, 5, 1, 8};
    ans = maxSumDivThree(nums, sizeof(nums) / sizeof(int));
    return;
}