
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define DEGUG_CHW 0
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_TIAN 1000
#define MAX_OPT_K 2
#define MAX_STATUS 2
int g_dp[MAX_TIAN][MAX_OPT_K][MAX_STATUS];

int maxProfit_infi(int* prices, int pricesSize)
{
    int dp_i_0 = 0;
    int dp_i_1 = INT_MIN;
    for (int i = 0; i < pricesSize; i++) {
        dp_i_0 = MAX(dp_i_0, dp_i_1 + prices[i]);
        dp_i_1 = MAX(dp_i_1, dp_i_0 - prices[i]);
    }
    return dp_i_0;
}
int g_dp_k1[MAX_TIAN][2];

int maxProfit_one(int* prices, int pricesSize)
{
    if (pricesSize == 0) return 0;
    g_dp_k1[0][0] = 0; //sell
    g_dp_k1[0][1] = -prices[0]; //buy
    for (int i = 1; i < pricesSize; i++) {
        g_dp_k1[i][0] = MAX(g_dp_k1[i - 1][0], g_dp_k1[i - 1][1] + prices[i]);
        g_dp_k1[i][1] = MAX(g_dp_k1[i - 1][1], -prices[i]);
    }
    return g_dp_k1[pricesSize - 1][0];
}

int maxProfit_one_youhua(int* prices, int pricesSize)
{
    int dp_i_0 = 0;
    int dp_i_1 = -prices[0];
    for (int i = 0; i < pricesSize; i++) {
        dp_i_0 = MAX(dp_i_0, dp_i_1 + prices[i]);
        dp_i_1 = MAX(dp_i_1, - prices[i]);
    }
    return dp_i_0;
}

int maxProfit_infi(int* prices, int pricesSize)
{
    int dp_i_0 = 0;
    int dp_i_1 = INT_MIN;
    for (int i = 0; i < pricesSize; i++) {
        dp_i_0 = MAX(dp_i_0, dp_i_1 + prices[i]);
        dp_i_1 = MAX(dp_i_1, dp_i_0 - prices[i]);
    }
    return dp_i_0;
}

int maxProfit(int* prices, int pricesSize)
{
    memset(g_dp, 0x0, sizeof(g_dp));
    if (MAX_OPT_K > pricesSize / 2) {
        return maxProfit_infi(prices, pricesSize);
    }
    if (MAX_OPT_K == 1) {
        return maxProfit_one(prices, pricesSize);
    }
    for (int i = 0; i < pricesSize; i++) {
        for (int k = MAX_OPT_K - 1; k >= 1; k--) {
            if (i == 0) {
                g_dp[i][k][0] = 0;
                g_dp[i][k][1] = -prices[0];
                continue;
            }
            g_dp[i][k][0] = MAX(g_dp[i - 1][k][0], g_dp[i - 1][k][1] + prices[i]);
            g_dp[i][k][1] = MAX(g_dp[i - 1][k][1], g_dp[i - 1][k - 1][0] - prices[i]);
        }
    }
    return g_dp[pricesSize - 1][MAX_OPT_K - 1][0];
}

int main()
{
    int nums[] = {2,3,1,2,4,3};
    int retsize = minSubArrayLen(7, nums, sizeof(nums) / sizeof(int));
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
