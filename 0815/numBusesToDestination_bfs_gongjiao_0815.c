/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

// #include "securec.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

typedef struct _queue{
    int head;
    int tail;
    int size;
    int *queue
}Queue;

#define INIT    (-1)
#define VOS_OK  0
#define VOS_NOK (-1)
Queue *QueueCreate(int k)
{
    Queue *p = (Queue *)malloc(sizeof(Queue));
    p->size = k;
    p->head = INIT;
    p->tail = INIT;
    p->queue = (int *)malloc(sizeof(int) * (k + 1));
    return p;
}
int QueueIsEmpty(Queue *obj)
{
    if (obj->head == INIT) {
        return VOS_OK;
    }
    return VOS_NOK;
}
int QueueIsFull(Queue *obj)
{
    if ((obj->tail + 1) % obj->size == obj->head) {
        return VOS_OK;
    }
    return VOS_NOK;
}
int QueueSize(Queue *obj)
{
    if (VOS_OK == QueueIsEmpty(obj)) {
        return 0;
    }
    if (VOS_OK == QueueIsFull(obj)) {
        return obj->size;
    }
    if (obj->head > obj->tail) {
        return obj->head - obj->tail - 1;
    } else {
        return obj->tail - obj->head + 1;
    }
}
int QueueEn(Queue *obj, int value)
{
    if (VOS_OK == QueueIsFull(obj)) {
        return VOS_NOK;
    }
    if (VOS_OK == QueueIsEmpty(obj)) {
        obj->head = 0;
    }
    obj->tail = (obj->tail + 1) % obj->size;
    obj->queue[obj->tail] = value;
    return VOS_OK;
}
int QueueDe(Queue *obj)
{
    if (VOS_OK == QueueIsEmpty(obj)) {
        return VOS_NOK;
    }
    if (obj->head == obj->tail) {
        obj->head = INIT;
        obj->tail = INIT;
        return VOS_OK;
    }
    obj->head = (obj->head + 1) % obj->size;
    return VOS_OK;
}
int QueueFront(Queue *obj)
{
    if (VOS_OK == QueueIsEmpty(obj)) {
        return -1;
    }
    return obj->queue[obj->head];
}
void QueueFree(Queue *obj)
{
    if (obj == NULL) {
        return;
    }
    if (obj->queue != NULL) {
        free(obj->queue);
        obj->queue = NULL;
    }
    free(obj);
    obj = NULL;
}

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

#define MAX_N 500
#define MAX_QUEUE_SIZE 10000

/* 使用BFS
 * 因为可以回走，使用带状态的, 总共12个结点，可以考虑使用bit位表示，每次push两个点值，一个表示v, 一个在v结点的状态情况
 * g_visist[v][0x1<<N];
 * 求最短路径考虑bfs
 */

int g_start[MAX_N];
int g_startidx;
int g_shash[MAX_N];
int g_end[MAX_N];
int g_endidx;
int g_ehash[MAX_N];
int g_gmap[MAX_N][MAX_N];
int g_ghash[MAX_N][MAX_N];
int g_grouplen[MAX_N];
int g_visit[MAX_N];

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

int SetValue(int *a, int len1, int sgid, int *b, int len2, int tgid)
{
    int ans = 0;
    int i = 0, j = 0;
    while (i < len1 && j < len2) {
        printf("i=%d a[i]=%d, j=%d, a[j]=%d\n", i, a[i], j, b[j]);
        if (a[i] == b[j]) {
            if (g_ghash[sgid][tgid] == 0 && g_ghash[tgid][sgid] == 0) {
                g_gmap[sgid][g_grouplen[sgid]] = tgid;
                g_grouplen[sgid]++;
                g_gmap[tgid][g_grouplen[tgid]] = sgid;
                g_grouplen[tgid]++;
                g_ghash[sgid][tgid] = 1;
                g_ghash[tgid][sgid] = 1;
                return ans;
            } else {
                i++;
                j++;
            }
        } else if (a[i] > b[j]) {
            j++;
        } else {
            i++;
        }
    }
    return ans;
}

int Cmp(void *a, void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta - tb;
}

void InitMap(int** routes, int routesSize, int* routesColSize, int s, int t)
{
    g_startidx = 0;
    g_endidx = 0;

    memset(g_shash, 0x0, sizeof(g_shash));
    memset(g_ehash, 0x0, sizeof(g_ehash));
    memset(g_ghash, 0x0, sizeof(g_ghash));
    memset(g_start, 0x0, sizeof(g_start));
    memset(g_end, 0x0, sizeof(g_end));
    memset(g_gmap, 0x0, sizeof(g_gmap));
    memset(g_grouplen, 0x0, sizeof(g_grouplen));
    memset(g_visit, 0x0, sizeof(g_visit));
    for (int i = 0; i < routesSize; i++) {
        for (int f = 0; f < routesColSize[i]; f++) {
            if (routes[i][f] == s && g_shash[i] == 0) {
                g_start[g_startidx++] = i;
                g_shash[i] = 1;
                break;
            }
        }
        for (int f = 0; f < routesColSize[i]; f++) {
            if (routes[i][f] == t && g_ehash[i] == 0) {
                g_end[g_endidx++] = i;
                g_ehash[i] = 1;
                break;
            }
        }
        qsort(routes[i], routesColSize[i], sizeof(int), Cmp);
        PrintArray(routes[i], routesColSize[i]);
    }

    for (int i = 0; i < routesSize; i++) {
        for (int j = i + 1; j < routesSize; j++) {
            SetValue(routes[i], routesColSize[i], i, routes[j], routesColSize[j], j);
        }
    }
    // PrintArray(g_start, g_startidx);
    // PrintArray(g_end, g_endidx);
}

bool FindTarget(int s)
{
    bool ans = false;
    for (int i = 0; i < g_endidx; i++) {
        if (g_end[i] == s) {
            return true;
        }
    }
    return ans;
}

int Bfs(int** routes, int routesSize, int* routesColSize, int s, int t)
{
    int n = routesSize;
    for (int i = 0; i < g_startidx; i++) {
        for (int j = 0; j < routesColSize[g_start[i]]; j++)
        if (t == routes[g_start[i]][j]) {
            return 1;
        }
    }
    Queue *q = QueueCreate(MAX_QUEUE_SIZE);
    for (int i = 0; i < g_startidx; i++) {
        QueueEn(q, g_start[i]);
        g_visit[g_start[i]] = 1;
    }
    int step = 1;
    while (QueueIsEmpty(q) != VOS_OK) {
        int laySize = QueueSize(q);
        for (int i = 0; i < laySize; i++) {
            int gid = QueueFront(q);
            QueueDe(q);
            if (FindTarget(gid)) {
                QueueFree(q);
                return step;
            }
            for (int j = 0; j < g_grouplen[gid]; j++) {
                int newgid = g_gmap[gid][j];
                if (g_visit[newgid] != 0) {
                    continue;
                }
                g_visit[newgid] = 1;
                QueueEn(q, newgid);
            }
        }
        step++;
    }
    QueueFree(q);
    return -1;
}

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int S, int T)
{
    int ans;
    if (S == T) return 0;
    InitMap(routes,  routesSize, routesColSize, S, T);
    ans = Bfs(routes,  routesSize, routesColSize, S, T);
    return ans;
}


#define MAP_ROW 5
#define MAP_COL 3
int g_map[MAP_ROW][MAP_COL] = {{12, 7}, {4,5,15}, {6}, {15, 19}, {12, 13, 9}};
int g_col[MAP_ROW] = {2, 3, 1, 2, 3};
// [[7,12],[],[6],[15,19],[9,12,13]]
int main()
{
    int gridSize = MAP_ROW;
    int **grid = NULL;
    int *gridColSize = NULL;

    /* 申请测试用例输入参数中需要的内存并根据用例输入初始化 */
    grid = malloc(gridSize * sizeof(int *));
    if (grid == NULL) {
        return -1;
    }
    gridColSize = malloc(gridSize * sizeof(int));
    if (gridColSize == NULL) {
        return -1;
    }
    for (int i = 0; i < gridSize; i++) {
        gridColSize[i] = g_col[i];
        grid[i] = malloc(gridColSize[i] * sizeof(int));
        if (grid[i] == NULL) {
            return -1;
        }
    }
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            grid[i][j] = g_map[i][j];
        }
    }
    int s = 15;
    int t = 12;
    int result = numBusesToDestination(grid, gridSize, gridColSize, s, t);

    /* 释放测试用例输入参数中申请的内存 */
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(gridColSize);
    free(grid);
}