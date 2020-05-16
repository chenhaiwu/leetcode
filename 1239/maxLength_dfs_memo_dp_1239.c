#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 17
#define CHAR_N 26

int g_canSel[CHAR_N];
int g_wordBit[MAX_N];
int g_memo[MAX_N];
int g_wordsFlag[MAX_N][MAX_N];

int BitSet(int mask, int bit)
{
    return mask | (1 << bit);
}

int BitClr(int mask, int bit)
{
    return mask & (~(1 << bit));
}

bool BitTest(int mask, int bit)
{
    if ((mask & (1 << bit)) >> bit == 1) {
        return true;
    } else {
        return false;
    }
}

void InitWordSelf(char **arr, int n)
{
    for (int i = 0; i < n; i++) {
        g_canSel[i] = 1;
        g_wordBit[i] = 0;
        g_memo[i] = -1;
        int len = strlen(arr[i]);
        for (int j = 0; j < len; j++) {
            // 转换大小写
            if (arr[i][j] >= 'A' && arr[i][j] <= 'Z') {
                arr[i][j] += ('a' - 'A');
            }
            int idx = arr[i][j] - 'a';
            if (BitTest(g_wordBit[i], idx)) {
                g_canSel[i] = 0;
                break;
            }
            g_wordBit[i] = BitSet(g_wordBit[i], idx);
        }
    }
}

int GetFlageInWords(char *s1, char *s2)
{
    int ans = 1;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int hashFlag[CHAR_N] = {0};
    for (int j = 0; j < len1; j++) {
        int idx = s1[j] - 'a';
        hashFlag[idx]++;
    }
    for (int j = 0; j < len2; j++) {
        int idx = s2[j] - 'a';
        hashFlag[idx]++;
    }
    for (int j = 0; j < CHAR_N; j++) {
        if (hashFlag[j] > 1) {
            ans = 0;
            break;
        }
    }
    return ans;
}

void InitTotalWords(char **arr, int n)
{
    for (int i = 0; i < n; i++) {
        g_wordsFlag[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            if (!g_canSel[i] || !g_canSel[j]) {
                g_wordsFlag[i][j] = g_wordsFlag[j][i] = 0;
                continue;
            }
            g_wordsFlag[i][j] = g_wordsFlag[j][i] = GetFlageInWords(arr[i], arr[j]);
        }
    }
}

int g_dp[MAX_N][MAX_N];

void PreHandle(int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g_dp[i][j] = 0;
        }
    }
}

int Dp(char ** arr, int n)
{
    PreHandle(n);
    InitWordSelf(arr, n);
    InitTotalWords(arr, n);
    // f[i][j] 表示到i位置时，如果j和i合法时，能选到的最长字符串长度
    //  f[i][j] = max(f[i-1][j] , f[i-1][j] + len(arr[i]))
    // g_dp[0][0] = strlen()
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < i; j++) {
    //     }
    // }
    return 0;
}

int Step(int idx, char ** arr, int n, int bits, int len)
{
    int ans;
    if (idx == n) {
        return len;
    }
    if (g_memo[idx] != -1) {
        return g_memo[idx];
    }
    // 检查当前位置是否可选，如果可选，可以分为选与不选
    int sel = 0, nosel = 0;
    if ((bits & g_wordBit[idx]) == 0 && g_canSel[idx] == 1) {
        sel = Step(idx + 1, arr, n, bits | g_wordBit[idx], len + strlen(arr[idx]));
        int unsel = Step(idx + 1, arr, n, bits, len);
        sel = MAX(sel, unsel);
    } else {
        nosel = Step(idx + 1, arr, n, bits, len);
    }

    ans = MAX(sel, nosel);
    g_memo[idx] = ans;
    return ans;
}

int Step_2(int idx, char ** arr, int n, int bits)
{
    int ans;
    if (idx == n) {
        return 0;
    }
    // if (g_memo[idx] != -1) {
    //     return g_memo[idx];
    // }
    // 检查当前位置是否可选，如果可选，可以分为选与不选
    int sel = 0, nosel = 0;
    if ((bits & g_wordBit[idx]) == 0 && g_canSel[idx] == 1) {
        sel = Step_2(idx + 1, arr, n, bits | g_wordBit[idx]) + strlen(arr[idx]);
        int unsel = Step_2(idx + 1, arr, n, bits);
        sel = MAX(sel, unsel);
        return sel;
    } else {
        nosel = Step_2(idx + 1, arr, n, bits);
        return nosel;
    }

    // ans = MAX(sel, nosel);
    // // g_memo[idx] = ans;
    // return ans;
}

int Dfs(char ** arr, int n)
{
    int ans;
    int bits = 0;
    // ans = Step(0, arr, n, bits, 0);
    ans = Step_2(0, arr, n, bits);
    return ans;
}

int maxLength(char ** arr, int arrSize)
{
    int ans = 0;

    if (arrSize == 0) {
        return 0;
    }
    if (arr == NULL || arr[0] == NULL) {
        return 0;
    }

    InitWordSelf(arr, arrSize);

    // dp
    // ans = Dp(arr, arrSize);

    // dp
    ans = Dfs(arr, arrSize);

    return ans;
}

char *arr2[3] = {"un", "abcddefgu", "ue"};
void main()
{
    int gridSize = 3;
    char **arr = malloc(gridSize * sizeof(char *));
    for (int i = 0; i < gridSize; i++) {
        int len = strlen(arr2[i]);
        arr[i] = (char *)malloc(len + 1);
        memset(arr[i], 0x0, len + 1);
        memcpy(arr[i], arr2[i], len);
        // arr[len] = '\0';
        printf("%s\n", arr[i]);
        printf("%s\n", arr2[i]);
    }

    int ans = maxLength(arr2, 3);
    printf("ans=%d\n", ans);
    return;
}