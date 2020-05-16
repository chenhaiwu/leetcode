#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

int FuncMin(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

#define MAX_LEN 5001

int g_memo[MAX_LEN];

int Step(int amount, int* coins, int coinsSize)
{
    if (amount == 0) return 1;
    if (amount < 0) return 0;
    if (g_memo[amount] != -1) return g_memo[amount];
    for (int i = 0; i < coins; i++) {
        int k = amount / coins[i];
        int ans;
        for (int j = 0; j <= k + 1; j++) {
            ans = Step(amount - j * coins[i], coins, coins);
            if (ans != -1) g_memo[amount] = ans + 1;
        }
    }
    return g_memo[amount];
}

int change_memo(int amount, int* coins, int coinsSize)
{
    if (amount == 0) return 0;
    for (int i = 0; i < amount; i++) g_memo[i] = -1;
    int ans = Step(amount, coins, coinsSize);
    return ans;
}

int g_dp[MAX_LEN];
int change(int amount, int* coins, int coinsSize)
{
    if (amount < 0) return 0;
    for (int i = 0; i <= amount; i++) {
        g_dp[i] = 0;
    }
    g_dp[0] = 1;
    for (int i = 0; i < coinsSize; i++) {
        for (int j = 1; j <= amount; j++) {
            if (j >= coins[i]) {
                g_dp[j] += g_dp[j - coins[i]];
            }
        }
    }
    return g_dp[amount];
}

int main()
{
    int a[] = {1,2,5};
    int ret = change(5, a, sizeof(a) / sizeof(int));
    // PrintArray(ret, retSize);
    // free(ret);
    printf("ret=%d\n", ret);
    return 0;
}
