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

#define MAX_M 101
#define MAX_N 101
int g_dir[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
// int g_visist[MAX_M][MAX_N][MAX_N + MAX_M];
#define MAX_LEN 10000

// grid[i][j] = 1: ludi, 0: sea; 2: 已访问过
int Bfs(int** grid, int gridSize, int* gridColSize)
{
    int n = gridSize;
    Queue *q = QueueCreate(MAX_LEN);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                QueueEn(q, i);
                QueueEn(q, j);
                grid[i][j] = 2;
            }
        }
    }
    if (QueueIsEmpty(q) == VOS_OK || QueueSize(q) == n * n * 2) return -1;

    int step = -1;
    while (QueueIsEmpty(q) != VOS_OK) {
        int size = QueueSize(q) / 2;
        step++;
        for (int i = 0; i < size; i++) {
            int orii = QueueFront(q);
            QueueDe(q);
            int orij = QueueFront(q);
            QueueDe(q);
            for (int j = 0; j < 4; j++) {
                int newi = orii + g_dir[j][0];
                int newj = orij + g_dir[j][1];
                if (newi < 0 || newi == n || newj < 0 || newj == n) continue;
                if (grid[newi][newj] == 2) continue;
                QueueEn(q, newi);
                QueueEn(q, newj);
                grid[newi][newj] = 2;
            }
        }        
    }
    QueueFree(q);
    return step;
}

int g_visit[MAX_M][MAX_N][MAX_M + MAX_N];
int g_ans;
void Step(int** grid, int steps, int i, int j, int m, int n, int k)
{
    if (k < 0) return;
    if (steps >= g_ans) return;
    if (i == m - 1 && j == n - 1) {
        g_ans = steps;
    }
    if (g_visit[i][j][k] == 1) return;

    g_visit[i][j][k] = 1;
    for (int t = 0; t < 4; t++) {
        int newi = i + g_dir[t][0];
        int newj = j + g_dir[t][1];
        if (newi < 0 || newi == m || newj < 0 || newj == n) continue;
        if (g_visit[newi][newj][k] == 1) continue;
        Step(grid, steps + 1, newi, newj, m, n, k - grid[newi][newj]);
    }
    return;
}
int Dfs(int** grid, int gridSize, int* gridColSize, int k)
{
    int m = gridSize;
    int n = gridColSize[0];
    memset(g_visit, 0x0, sizeof(g_visit));
    k = k > (m + n) ? (m + n) : k;
    g_ans = INT_MAX;
    Step(grid, 0, 0, 0, m, n, k);
    g_ans = (g_ans == INT_MAX) ? -1 : g_ans;
    return g_ans;
}

int BaoGetOneValueli(int** grid, int n, int r, int c)
{
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                int tmp = abs(i - r) + abs(j - c);
                ans = MIN(ans, tmp);
            }
        }
    }
    return ans;
}

#define MAX_N 201
int g_sum[MAX_N][MAX_N];

int* Dp_substring(int** grid, int gridSize, int* gridColSize)
{
    int sum = INT_MIN;
    int r1, c1, r2, c2;
    int w = gridColSize[0];
    int h = gridSize;
    int *dp = (int *)malloc(sizeof(int) * w);

    // i -> (0, h)表示 从起点行开始
    for (int i = 0; i < h; i++) {
        // 把当前起点行到最后一行，累加起来，一行一行来
        memset(dp, 0x0, sizeof(int) * w);
        // printf("w=%d,h=%d\n", w, h);
        for (int j = i; j < h; j++) {
            int localsum = 0;
            int start = 0;
            for (int k = 0; k < w; k++) {
                if (localsum < 0) {
                    start = k;
                    localsum = 0;
                }
                dp[k] += grid[j][k];
                localsum += dp[k];
                if (sum < localsum) {
                    r1 = i;
                    c1 = start;
                    r2 = j;
                    c2 = k;
                    sum = localsum;
                    // printf("update i = %d, j=%d, r2=%d, c2=%d\n", r1, c1, r2, c2);
                }
            }
        }
    }
    int *ret = (int *)malloc(4 * sizeof(int));
    ret[0] = r1;
    ret[1] = c1;
    ret[2] = r2;
    ret[3] = c2;
    return ret;
}

void InitMatrixSum(int** grid, int n, int *m)
{
    memset(g_sum, 0x0, sizeof(g_sum));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m[i]; j++) {
            g_sum[i][j + 1] = g_sum[i][j] + grid[i][j];
        }
    }
}

int GetSubMatrixSum(int** grid, int starti, int startj, int n, int m, int *endi, int *endj)
{
    int sum = INT_MIN;
    int rowsum;
    for (int col = startj; col < m; col++) {
        rowsum = 0;
        for (int row = starti; row < n; row++) {
            rowsum += (g_sum[row][col + 1] - g_sum[row][startj]);
            if (rowsum > sum) {
                *endi = row;
                *endj = col;
                sum = rowsum;
            }
        }
    }
    return sum;
}

int* Baoli(int** grid, int gridSize, int* gridColSize)
{
    InitMatrixSum(grid, gridSize, gridColSize);
    int sum = INT_MIN;
    int r1, c1, r2, c2;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            int tmpr2, tmpc2;
            int tmp = GetSubMatrixSum(grid, i, j, gridSize, gridColSize[i], &tmpr2, &tmpc2);
            if (tmp > sum) {
                sum = tmp;
                r1 = i;
                c1 = j;
                r2 = tmpr2;
                c2 = tmpc2;
            }
        }
    }
    int *ret = (int *)malloc(4 * sizeof(int));
    ret[0] = r1;
    ret[1] = c1;
    ret[2] = r2;
    ret[3] = c2;
    return ret;
}

int* getMaxMatrix(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    int *ans;
    // ans = Baoli(matrix, matrixSize, matrixColSize);
    *returnSize = 4;

    // ans = Bfs(grid, gridSize, gridColSize);

    // ans = Dfs(grid, gridSize, gridColSize, k);
    ans = Dp_substring(matrix, matrixSize, matrixColSize);
    return ans;
}

// [[9,-8,1,3,-2],[-3,7,6,-2,4],[6,-4,-4,8,-7]]
// #define MAP_ROW 3
// #define MAP_COL 5
// int g_map[MAP_ROW][MAP_COL] = {{9,-8,1,3,-2}, {-3,7,6,-2,4}, {6,-4,-4,8,-7}};
// int g_col[MAP_ROW] = {5, 5, 5, 5, 5};

// int main()
// {
//     int gridSize = MAP_ROW;
//     int **grid = NULL;
//     int *gridColSize = NULL;

//     /* 申请测试用例输入参数中需要的内存并根据用例输入初始化 */
//     grid = malloc(gridSize * sizeof(int *));
//     if (grid == NULL) {
//         return -1;
//     }
//     gridColSize = malloc(gridSize * sizeof(int));
//     if (gridColSize == NULL) {
//         return -1;
//     }
//     for (int i = 0; i < gridSize; i++) {
//         gridColSize[i] = g_col[i];
//         grid[i] = malloc(gridColSize[i] * sizeof(int));
//         if (grid[i] == NULL) {
//             return -1;
//         }
//     }
//     for (int i = 0; i < gridSize; i++) {
//         for (int j = 0; j < gridColSize[i]; j++) {
//             grid[i][j] = g_map[i][j];
//         }
//     }
//     int k = 1;
//     int * result = getMaxMatrix(grid, gridSize, gridColSize, &k);

//     /* 释放测试用例输入参数中申请的内存 */
//     for (int i = 0; i < gridSize; i++) {
//         free(grid[i]);
//     }
//     free(gridColSize);
//     free(grid);
// }