#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX_STEPS 101
#define MAX_N 25
/* 表示剩余频数为steps时，在位置r,c位置可能的概率。*/
double g_memo[MAX_STEPS][MAX_N][MAX_N];
int g_dir[8][2] = {
    {-2, -1},
    {-2, 1},
    {-1, -2},
    {-1, 2},
    {2, 1},
    {2, -1},
    {1, 2},
    {1, -2}
};

bool IsInChese(int n, int i, int j)
{
    bool ans = false;
    if (i >= 0 && i < n && j >= 0 && j < n) {
        ans = true;
    }
    return ans;
}

/* DFS退出条件的差别，首先能进STEP一定是在棋盘上，
 * 而且如果当前的剩余频数为1，表明只要算出最后一步，可以8步走法中的，有几步在棋盘中即可 
 */
double Step(int n, int k, int r, int c)
{
    if (k == 1) {
        double ret1 = 0.0;
        int cnt = 0;
        for (int i = 0; i < 8; i++) {
            int newi = r + g_dir[i][0];
            int newj = c + g_dir[i][1];
            if (IsInChese(n, newi, newj)) cnt++;
        }
        return (double)cnt / 8.0;
    }
    if (g_memo[k][r][c] - 0.0 > 0.0000001) return g_memo[k][r][c];

    double pi = 1.0 / 8.0;
    double ans = 0.0;
    for (int i = 0; i < 8; i++) {
        int newi = r + g_dir[i][0];
        int newj = c + g_dir[i][1];
        if (!IsInChese(n, newi, newj)) continue;
        ans += Step(n, k - 1, newi, newj);
    }
    g_memo[k][r][c] = ans / 8.0;
    return g_memo[k][r][c];
}

/* DFS退出条件的差别，首先能进STEP一定是在棋盘上，而且如果当前的剩余频数为0，表明这就是1.0事件 */
double Step2(int n, int k, int r, int c)
{
    if (k <= 0) return 1.0;
    if (g_memo[k][r][c] - 0.0 > 0.0000001) return g_memo[k][r][c];

    double pi = 1.0 / 8.0;
    double ans = 0.0;
    for (int i = 0; i < 8; i++) {
        int newi = r + g_dir[i][0];
        int newj = c + g_dir[i][1];
        if (!IsInChese(n, newi, newj)) continue;
        ans += Step(n, k - 1, newi, newj);
    }
    g_memo[k][r][c] = ans / 8.0;
    return g_memo[k][r][c];
} 

/* DFS+memo的做法，表示深度上走完steps全部步数，宽度上，每次遍历8个点 */
double Dfs(int N, int K, int r, int c)
{
    double ans;
    memset(g_memo, 0.0, sizeof(g_memo));

    ans = Step(N, K, r, c);
    return ans;
}

/* 状态转移方程，dp[steps][i][j] 在棋盘上ij位置走steps出界的次数 = 在它的四面走steps-1 的概率和/8
 * 初始状态：向四周散射型，如果有值，则开始8方射
 */
double g_dp[MAX_STEPS][MAX_N][MAX_N];
double Dp(int N, int K, int r, int c)
{
    double ans;
    memset(g_dp, 0.0, sizeof(g_memo));
    g_dp[0][r][c] = 1.0;
    for (int s = 1; s <= K; s++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (g_dp[s - 1][i][j] - 0.0 < 0.000001) continue;
                for (int t = 0; t < 8; t++) {
                    int newi = i + g_dir[t][0];
                    int newj = j + g_dir[t][1];
                    if (!IsInChese(N, newi, newj)) continue;
                    g_dp[s][newi][newj] += g_dp[s - 1][i][j] * 0.125;
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ans += g_dp[K][i][j];
        }
    }
    return ans;
}

/* 这题有两个难点，第1个是要明白，概率如何计算，如果先求所有可能的步数，然后除以8的步数次方，则一定越界
 * 所以可以先求每一步的概率，然后做加。
 * 第2个点：double是如何表示的，memo数组初始化值是多少，0.0，这是真0.  有值的，
 * 那比较的时候，如果非0，则使用减法.
 * 第三点：可以使用dfs，每走一步的概率就是当前这一步，走几种可能在棋盘上，然后 除8
 * 算法： dp方法
 */
double knightProbability(int N, int K, int r, int c)
{
    double ans;
    if (K == 0) {
        return 1.0;
    }

    // ans = Dfs(N, K, r, c);

    ans = Dp(N, K, r, c);

    return ans;
}

void main()
{
    double ans;
    ans = knightProbability(3, 2, 0, 0);
    printf("ans=%f\n", ans);
    // ans = findPaths(1, 3, 3, 0, 1);
    // printf("ans=%d\n", ans);
    // ans = findPaths(2, 2, 2, 0, 1);
    // printf("ans=%d\n", ans);
    return;
}