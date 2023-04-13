
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_TIAN 50001
#define MAX_OPT_K 2
#define MAX_STATUS 2
int g_dp[MAX_TIAN][MAX_OPT_K][MAX_STATUS];

int maxProfit_infi(int* prices, int pricesSize, int fee)
{
    int dp_i_0 = 0;
    int dp_i_1 = INT_MIN;
    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] >= fee) {
            dp_i_0 = MAX(dp_i_0, dp_i_1 + prices[i] - fee);
        }
        dp_i_1 = MAX(dp_i_1, dp_i_0 - prices[i]);
    }
    return dp_i_0;
}

int maxProfit(int* prices, int pricesSize, int fee)
{
    memset(g_dp, 0x0, sizeof(int) * (pricesSize + 1));
    //if (MAX_OPT_K > pricesSize / 2) {
    return maxProfit_infi(prices, pricesSize, fee);
    //}
    /*
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
    */
}

int main()
{
    int nums[] = {2,3,1,2,4,3};
    int retsize = minSubArrayLen(7, nums, sizeof(nums) / sizeof(int));
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
