#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MOD_MAX 1000000007

/* 动态规划，进行分类讨论：第一行时，选择ABA、ABC型
 * 如果选 ABA，则有3 * 2种可能，A：选3种，B选: 2种  ,  定义为m。
 * 如果选 ABC，则有 A: 3: B: 2: c: 1，也有6种可能。   ， 定义为n。
 * 第二行时，如果上一行选ABA：则有: BAB, BAC, BCB, CAC, CAB， 再进行归类，分成：(3 * m + 2 * n)
 * 如果上一行选 ABC: 则有 BAB, BCA, BCB, CAB，进行归类为：(2m + 2n)
 * 则是第二行为上一行的值为：(3m + 2n) + (2m + 2n)，注意是要分开计算的。类型一开始就是分开的。
 * 设计写法时，可以定义两个类型的变量
 */
int Dp(int layer)
{
    long long m = 6;
    long long n = 6;
    for (int i = 1; i < layer; i++) {
        long long newm = 3 * m + 2 * n;
        long long newn = 2 * m + 2 * n;
        newm %= MOD_MAX;
        newn %= MOD_MAX;
        m = newm;
        n = newn;
    }
    m = (m + n) % MOD_MAX;
    int ans = (int)m;
    return ans;
}

// 使用三个位置的值，+ 层数来表示memo，进行dfs
#define MAX_N 5001
int g_memo[4][4][4][MAX_N];
int g_n;

int Step(int prei, int prej, int prek, int step)
{
    if (step == g_n) {
        return 1;
    }
    if (g_memo[prei][prej][prek][step] != 0) {
        return g_memo[prei][prej][prek][step];
    }
    int ans = 0;
    for (int i = 0; i < 3; i++) {
        if (i == prei) continue;
        for (int j = 0; j < 3; j++) {
            if (j == prej || j == i) continue;
            for (int k = 0; k < 3; k++) {
                if (k == prek || k == j) continue;
                ans = (ans + Step(i, j, k, step + 1)) % MOD_MAX;
            }
        }
    }
    g_memo[prei][prej][prek][step] = ans;
    return ans;
}

int Dfs(int layer)
{
    g_n = layer;
    memset(g_memo, 0x0, sizeof(g_memo));
    // g_memo[0][0][0][0] = 1;
    int ans = Step(3, 3, 3, 0);
    return ans;
}

int numOfWays(int layer)
{
    int ans;
    // ans = Dp(layer);
    ans = Dfs(layer);
    return ans;
}

void main()
{
    int ans = numOfWays(1);
    ans = numOfWays(2);
    ans = numOfWays(3);
    ans = numOfWays(4);
    return;
}