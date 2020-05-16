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

int FuncMin(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

#define MAX_LEN 10010

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}


int g_memo[MAX_LEN];
int GetSteps(int* coins, int coinsSize, int amount)
{
    if (amount == 0) return 0;
    if (g_memo[amount] != -2) {
        return g_memo[amount];
    }
    int res = INT_MAX;
    for (int i = 0; i < coinsSize; i++) {
        if (amount >= coins[i]) {
            int sub = GetSteps(coins, coinsSize, amount - coins[i]);
            if (sub == -1) {
                continue;
            }
            res = FuncMin(res, sub + 1);
        }
    }
    g_memo[amount] = (res == INT_MAX) ? -1 : res;
    return g_memo[amount];
}

/* memoªº??¤èªk¡A???¬OÃz¤F¡A±o¥X¶W?ªººâªk
 * É¬¤Æªº?ªk¡Gª`·N¤@?©l¬O¦³¸Ñªº?­Ô¡Amemo‰N??¡AÆÓ¸Ñ?¡A¤]¥i¥H??¤U?¡A?ı©¤£¥Î¨C¦¸m¬d§ä«Ü¦hÆÓ®Ä¸Ñ¡C
 */
int coinChange_1(int* coins, int coinsSize, int amount)
{
    int ans = 0;
    if (amount < 0) return -1;
    if (amount == 0) return 0;
    for (int i = 0; i <= amount; i++) g_memo[i] = -2;
    // memset(g_memo, -2U, sizeof(int) * (amount + 1));
    ans = GetSteps(coins, coinsSize, amount);
    return ans;
}

int g_dp[MAX_LEN];
int coinChange(int* coins, int coinsSize, int amount)
{
    int ans = 0;
    if (amount < 0) return -1;
    if (amount == 0) return 0;
    for (int i = 1; i <= amount; i++) g_dp[i] = amount + 1;
    g_dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coinsSize; j++) {
            if (i < coins[j]) {
                continue;
            }
            g_dp[i] = FuncMin(g_dp[i], g_dp[i - coins[j]] + 1);
        }
    }
    return g_dp[amount] > amount ? -1 : g_dp[amount];
}

int main()
{
    int a[] = {1,2,5};
    int ret = coinChange(a, sizeof(a) / sizeof(int), 11);
    // PrintArray(ret, retSize);
    // free(ret);
    printf("ret=%d\n", ret);
    return 0;
}
