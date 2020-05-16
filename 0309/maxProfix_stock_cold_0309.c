
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_TIAN 1000
#define MAX_STATUS 2

int maxProfit(int* prices, int pricesSize)
{
    int dp_i_0 = 0;
    int dp_i_1 = INT_MIN;
    int pre_tian_0 = 0;
    for (int i = 0; i < pricesSize; i++) {
        int tmp = dp_i_0;
        dp_i_0 = MAX(dp_i_0, dp_i_1 + prices[i]);
        dp_i_1 = MAX(dp_i_1, pre_tian_0 - prices[i]);
        pre_tian_0 = tmp;
    }
    return dp_i_0;
}
