#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define NODE_MAX 100001
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)
int g_pre[NODE_MAX];
int g_reginCnt[NODE_MAX];
bool g_bDelFlag[NODE_MAX];
int g_groupCnts;

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

void HanldeAllParnet(int len)
{
    for (int i = 0; i < len; i++) {
        Find(i);
    }
}

int GetNewGroupCnts(int n, int** connections, int connectionsSize, int exp)
{
    for (int i = 0; i < n; i++) {
        g_pre[i] = i;
        g_reginCnt[i] = 0;
        g_bDelFlag[i] = false;
    }
    for (int i = 0; i < connectionsSize; i++) {
        if (g_bDelFlag[i] || i == exp) {
            continue;
        }
        int from = connections[i][0];
        int to = connections[i][1];
        Join(from, to);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int t = Find(i);
        if (g_reginCnt[t] == 0) {
            ans++;
        }
        g_reginCnt[t]++;
    }
    return ans;
}

/*
写一个函数，统计如何求连通分量，返回值，连通分量数目
1：求初始状态的连通分量数。cnt
if (cnt==1) 直接返回0
if cnt > 1, 则检查边的数目，如果conSize < cnt - 1, 则返回-1
2: 剩下情况求：可以省出来的线数目。
   for (针对每条边，做循环，表示，当前这条表，跳出来，不用，可以有多少个连通分量)
   {
       只有这种情况：new_cnt == cnt; reduceCnt++;
   }
   if (reduceCnt >= cnt - 1)，说明有解，最少解为cnt - 1
   否则无解，-1
    34/36超时
*/
int makeConnected_1(int n, int** connections, int connectionsSize, int* connectionsColSize)
{
    g_groupCnts = GetNewGroupCnts(n, connections, connectionsSize, -1);
    if (g_groupCnts == 1) {
        return 0;
    }
    int curGroupCnts = g_groupCnts;
    if (connectionsSize < n - 1) return -1;
    int ret = 0;
    int reduceCnt = 0;
    for (int i = 0; i < connectionsSize; i++) {
        int newCnts = GetNewGroupCnts(n, connections, connectionsSize, i);
        if (newCnts == curGroupCnts) {
            g_bDelFlag[i] = true;
            reduceCnt++;
            if (reduceCnt >= curGroupCnts - 1) {
                return reduceCnt;
            }
        }
    }
    return -1;
}

/*
   同样是上面的逻辑，并查集。
   但是不必要把每条边去掉，然后再去查找还有几个连通分量。
   我们只要证明，如果边够多的话，一个连通分量一定有多余的边，然后每动一条边，就可以连起2个连通分量
   那么，最少的移动是，连通分量 - 1
*/
int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize)
{
    g_groupCnts = GetNewGroupCnts(n, connections, connectionsSize, -1);
    if (g_groupCnts == 1) {
        return 0;
    }
    int curGroupCnts = g_groupCnts;
    if (connectionsSize < n - 1) return -1;
    return curGroupCnts - 1;
}