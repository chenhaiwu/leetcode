#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define ROWS 4
#define COLS 3
#define MAXSTEPS 5001
#define MAX_MOD 1000000007
int g_matrix[ROWS][COLS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {-1, 0, -1}};
int g_init[ROWS][COLS] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {0, 1, 0}};
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
int g_memo[MAXSTEPS][ROWS][COLS];

bool IsIllegalNum(int i, int j)
{
    bool ans = false;
    if ((i == 3 && j == 0) || (i == 3 && j == 2)) return false;
    if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
        ans = true;
    }
    return ans;
}

int Step(int r, int c, int n)
{
    int ans = 0;
    if (n == 1) {
        return 1;
    }
    if (g_memo[n][r][c] != -1) return g_memo[n][r][c];

    for (int i = 0; i < 8; i++) {
        int newi = r + g_dir[i][0];
        int newj = c + g_dir[i][1];
        if (IsIllegalNum(newi, newj)) {
            ans += Step(newi, newj, n - 1);
            ans %= MAX_MOD;
        }
    }
    g_memo[n][r][c] = ans;
    return ans;
}

int Dfs(int n)
{
    int ans = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            memset(g_memo, -1, sizeof(g_memo));
            if (IsIllegalNum(i, j)) {
                ans += Step(i, j, n);
                ans %= MAX_MOD;
            }
        }
    }
    return ans;
}

int g_dp[MAXSTEPS][ROWS][COLS];
int Dp(int n)
{
    /* init state*/
    memset(g_dp, 0x0, sizeof(g_dp));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            g_dp[1][i][j] = g_init[i][j];
        }
    }
    for (int s = 2; s <= n; s++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                for (int t = 0; t < 8; t++) {
                    int newi = i + g_dir[t][0];
                    int newj = j + g_dir[t][1];
                    if (!IsIllegalNum(newi, newj)) continue;
                    g_dp[s][newi][newj] += g_dp[s - 1][i][j];
                    g_dp[s][newi][newj] %= MAX_MOD;
                }
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (IsIllegalNum(i, j)) {
                ans += g_dp[n][i][j];
                ans %= MAX_MOD;
            }
        }
    }
    return ans;
}

int knightDialer(int n)
{
    int ans = 0;
    if (n == 0) {
        return 0;
    }
    
    // ans = Dfs(n);

    ans = Dp(n);

    return ans;
}

void main()
{
    int ans;
    int n = 1;
    ans = knightDialer(1);
    printf("ans=%d\n", ans);
    ans = knightDialer(2);
    printf("ans=%d\n", ans);
    ans = knightDialer(3);
    printf("ans=%d\n", ans);
    ans = knightDialer(4);
    printf("ans=%d\n", ans);
    ans = knightDialer(5);
    printf("ans=%d\n", ans);
    return;
}