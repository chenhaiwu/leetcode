#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 2002
#define MAX_UNLIKE 10002
int g_unlikemap[MAX_N][MAX_N];
int g_cnt[MAX_N];
int g_color[MAX_N];
int g_n;
int g_unlikelen;
int **g_dislikes;

//union find
int g_pre[MAX_N * 2 + 6];

#define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

void PreHandle(int N, int** dislikes, int dislikesSize)
{
    g_n = N;
    g_unlikelen = dislikesSize;
    g_dislikes = dislikes;
    memset(g_color, -1, sizeof(int) * (N + 1));
    memset(g_cnt, 0x0, sizeof(g_cnt));
    memset(g_unlikemap, -1, sizeof(g_unlikemap));
    for (int i = 0; i < dislikesSize; i++) {
        int a = dislikes[i][0];
        int b = dislikes[i][1];
        int idx = g_cnt[a];
        g_unlikemap[a][idx] = b;
        g_cnt[a]++;
        idx = g_cnt[b];
        g_unlikemap[b][idx] = a;
        g_cnt[b]++;
    }
    PrintArray(g_cnt, N + 1);
    for (int i = 0; i < dislikesSize; i++) {
        printf("i=%d", i);
        PrintArray(g_unlikemap[i], N + 1);
    }
}

bool Docolor(int idx, int color)
{
    if (g_color[idx] != -1 && g_color[idx] != color) {
        return false;
    }
    if (g_color[idx] == color) {
        return true;
    }
    g_color[idx] = color;
    int cnt = g_cnt[idx];
    for (int i = 0; i < cnt; i++) {
        int b = g_unlikemap[idx][i];
        bool ans = Docolor(b, color ^ 1);
        if (!ans) {
            return false;
        }
    }
    return true;
}

bool Dfs(int N, int** dislikes, int dislikesSize)
{
    PreHandle(N, dislikes, dislikesSize);

    for (int i = 0; i < g_unlikelen; i++) {
        int a = g_dislikes[i][0];
        int b = g_dislikes[i][1];
        if (g_color[a] == -1) {
            bool ans = Docolor(a, 0);
            if (!ans) {
                return false;
            }
        }
    }
    return true;
}


int Find(int i)
{
    if (i != g_pre[i]) {
        g_pre[i] = Find(g_pre[i]);
    }
    return g_pre[i];
}

void Join(int i, int j)
{
    int pi = Find(i);
    int pj = Find(j);
    if (pi == pj) {
        return;
    } else if (pi < pj) {
        g_pre[pj] = pi;
    } else {
        g_pre[pi] = pj;
    }
}

bool UnionFind(int N, int** dislikes, int dislikesSize)
{
    for (int i = 0; i < 2 * N + 6; i++) {
        g_pre[i] = i;
    }
    int len = N + 1;
    for (int i = 0; i < dislikesSize; i++) {
        int a = dislikes[i][0];
        int b = dislikes[i][1];
        int x = Find(a);
        int y = Find(b);
        int m = Find(a + len);
        int n = Find(b + len);
        if (x == y) {
            return false;
        } else {
            Join(y, m);
            Join(x, n);
        }
    }
    return true;
}

bool possibleBipartition(int N, int** dislikes, int dislikesSize, int* dislikesColSize)
{
    bool ans;
    
    ans = Dfs(N, dislikes, dislikesSize);

    ans = UnionFind(N, dislikes, dislikesSize);
    return ans;
}

void main()
{
    return;
}