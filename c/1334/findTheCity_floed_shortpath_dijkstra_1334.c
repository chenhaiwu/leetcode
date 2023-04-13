#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define NODE_MAX 101
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

int g_dis[NODE_MAX][NODE_MAX];
#define MAX_LOADS 10001

void PreHandle(int n, int** edges, int edgesSize)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g_dis[i][j] = MAX_LOADS;
        }
    }
    for (int i = 0; i < edgesSize; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        g_dis[from][to] = g_dis[to][from] = edges[i][2];
    }
}

int findTheCity(int n, int** edges, int edgesSize, int* edgesColSize, int distanceThreshold)
{
    PreHandle(n, edges, edgesSize);
    // floeydºâªk
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g_dis[i][j] == MAX_LOADS) continue;
            for (int k = j + 1; k < n; k++) {
                g_dis[k][j] = g_dis[j][k] = MIN(g_dis[j][k], g_dis[j][i] + g_dis[i][k]);
            }
        }
    }
    // ‰s??ªG
    int ans = n;
    int ret = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (g_dis[i][j] <= distanceThreshold) {
                cnt++;
            }
        }
        if (cnt <= ans) {
            ans = cnt;
            ret = i;
        }
    }
    return ret;
}