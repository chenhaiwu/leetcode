/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: 缺省代??供参考，可自行决定使用、修改或删除
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

#define MAX_N 12
#define MAX_QUEUE_SIZE 100000
int g_visit[MAX_N][1 << 12];

/* 使用BFS
 * 因?可以回走，使用???的, 总共12个?点，可以考?使用bit位表示，每次push两个点值，一个表示v, 一个在v?点的??情况
 * g_visist[v][0x1<<N];
 * 求最短路?考?bfs
 */
int shortestPathLength(int** graph, int graphSize, int* graphColSize)
{
    if (graphSize == 0) return 0;
    int n = graphSize;
    int target = (1 << n) - 1;
    Queue *q = QueueCreate(MAX_QUEUE_SIZE);
    // init value
    memset(g_visit, 0x0, sizeof(g_visit));
    for (int i = 0; i < n; i++) {
        QueueEn(q, i);
        QueueEn(q, 1 << i);
    }

    int step = 0;
    while (QueueIsEmpty(q) != VOS_OK) {
        int laySize = QueueSize(q) / 2;
        for (int i = 0; i < laySize; i++) {
            int v = QueueFront(q);
            QueueDe(q);
            int s = QueueFront(q);
            QueueDe(q);
            if (s == target) return step;
            for (int j = 0; j < graphColSize[v]; j++) {
                int newv = graph[v][j];
                int news = BitSet(s, newv);
                if (g_visit[newv][news] != 0) {
                    continue;
                }
                g_visit[newv][news] = 1;
                QueueEn(q, newv);
                QueueEn(q, news);
            }
        }
        step++;
    }
    return step;
}


#define MAP_ROW 4
#define MAP_COL 4
int g_map[MAP_ROW][MAP_COL] = {{1, 2, 3}, {0}, {0}, {0}};
int g_col[MAP_ROW] = {3, 1, 1, 1};

int main()
{
    int gridSize = MAP_ROW;
    int **grid = NULL;
    int *gridColSize = NULL;

    /* 申???用例输入参?中需要的?存并根据用例输入初始化 */
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

    int result = shortestPathLength(grid, gridSize, gridColSize);

    /* ?放??用例输入参?中申?的?存 */
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(gridColSize);
    free(grid);
}