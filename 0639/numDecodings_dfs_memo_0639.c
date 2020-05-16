#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 100001
#define MOD_MAX 1000000007

int g_memo[MAX_N];

long long Step(int idx, char *s, int len)
{
    if (idx == len - 1) {
        if (s[idx] > '0' && s[idx] <= '9') return 1;
        else if (s[idx] == '0' ) return 0;
        else return 9;
    }
    if (idx >= len) {
        return 1;
    }
    if (s[idx] == '0') return 0;
    if (g_memo[idx] != 0) {
        return g_memo[idx];
    }

    char c = s[idx];
    int ans = 0;
    long long curMax = 0;
    if (c >= '3' && c <= '9') {
        curMax = Step(idx + 1, s, len);
        curMax %= MOD_MAX;
    } else if (c == '*') {
        long long one = 9 * Step(idx + 1, s, len);
        long long two = 0;
        if (idx < len - 1) {
            if (s[idx + 1] <= '9' && s[idx + 1] >= '7') {
                two = 1 * Step(idx + 2, s, len);
            } else if (s[idx + 1] <= '6' && s[idx + 1] >= '0') {
                two = 2 * Step(idx + 2, s, len);
            } else {
                two = 15 * Step(idx + 2, s, len);
            }
        }
        curMax = one + two;
        curMax %= MOD_MAX;
    } else if (c == '1') {
        long long one = Step(idx + 1, s, len);
        long long two = 0;
        if (idx < len - 1) {
            // 第二个字符存在，那要么是数字0-9，要么就是*号
            if (s[idx + 1] <= '9' && s[idx + 1] >= '0') {
                two = Step(idx + 2, s, len);
            } else {
            // 第二个字符如果是*号，则
                two = 9 * Step(idx + 2, s, len);
            }
        }
        curMax = one + two;
        curMax %= MOD_MAX;
    } else if (c == '2') {
        long long one = Step(idx + 1, s, len);
        long long two = 0;
        if (idx < len - 1) {
            // 第二个字符存在，那要么是数字0-9，要么就是*号
            if (s[idx + 1] == '*') {
                two = 6 * Step(idx + 2, s, len);
            } else if (s[idx + 1] <= '6' && s[idx + 1] >= '0') {
                two = Step(idx + 2, s, len);
            }
        }
        curMax = one + two;
        curMax %= MOD_MAX;
    }

    ans = curMax;
    g_memo[idx] = ans;
    return (long long)ans;
}

int Dfs(char * s)
{
    int ans;
    memset(g_memo, 0x0, sizeof(g_memo));
    int len = strlen(s);
    ans = Step(0, s, len);
    return ans;
}

int numDecodings(char * s)
{
    int ans = 0;
    ans = Dfs(s);

    return ans;
}

// void main()
// {
//     int ans;
//     ans = numDecodings("1**");
//     printf("ans=%d\n", ans);
//     ans = numDecodings("123");
//     printf("ans=%d\n", ans);
//     ans = numDecodings("1*");
//     printf("ans=%d\n", ans);
//     ans = numDecodings("1**");
//     printf("ans=%d\n", ans);
//     return;
// }