/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
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

#define MAX_M 11
#define MAX_N 11
int g_dir[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
// int g_visist[MAX_M][MAX_N][MAX_N + MAX_M];
#define MAX_LEN 1000

// grid[i][j] = 0: space, ¤£¯à‰V?¥h¡C1¡GOK¡A2¡G»G?ªº¡A3¡G¤w‰r¤J??ªº
int Bfs(int** grid, int gridSize, int* gridColSize)
{
    int n = gridSize;
    int m = gridColSize[0];
    int s = 0;
    int lan = 0;
    Queue *q = QueueCreate(MAX_LEN);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != 0) s++;
            if (grid[i][j] == 2) {
                lan++;
                QueueEn(q, i);
                QueueEn(q, j);
                grid[i][j] = 3;
            }
        }
    }
    if (lan == s) {
        if (lan == 0) return 0;
        else return 0;
    } else {
        if (lan == 0) return -1;
    }

    int step = -1;
    while (QueueIsEmpty(q) != VOS_OK) {
        int size = QueueSize(q) / 2;
        for (int i = 0; i < size; i++) {
            int orii = QueueFront(q);
            QueueDe(q);
            int orij = QueueFront(q);
            QueueDe(q);
            for (int j = 0; j < 4; j++) {
                int newi = orii + g_dir[j][0];
                int newj = orij + g_dir[j][1];
                if (newi < 0 || newi == n || newj < 0 || newj == m) continue;
                if (grid[newi][newj] == 3) continue;
                if (grid[newi][newj] == 0) continue;
                QueueEn(q, newi);
                QueueEn(q, newj);
                grid[newi][newj] = 3;
            }
        }
        step++;
    }
    QueueFree(q);
    
    int newlan = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 3) {
                newlan++;
            }
        }
    }
    return newlan == s ? step : -1;
}

// int GetOneValue(int** grid, int n, int r, int c)
// {
//     int ans = INT_MAX;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             if (grid[i][j] == 1) {
//                 int tmp = abs(i - r) + abs(j - c);
//                 ans = MIN(ans, tmp);
//             }
//         }
//     }
//     return ans;
// }

// int Baoli(int** grid, int gridSize, int* gridColSize)
// {
//     int ans = -1;
//     int n = gridSize;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             if (grid[i][j] == 0) {
//                 int tmp = GetOneValue(grid, n, i, j);
//                 ans = MAX(ans, tmp);
//             }
//         }
//     }
//     return ans == INT_MAX ? -1 : ans;
// }

int orangesRotting(int** grid, int gridSize, int* gridColSize)
{
    if (gridSize == 0) return -1;
    int ans;
    // ans = Baoli(grid, gridSize, gridColSize);

    ans = Bfs(grid, gridSize, gridColSize);

    // ans = Dfs(grid, gridSize, gridColSize, k);
    return ans;
}

// #define MAP_ROW 3
// #define MAP_COL 3
// int g_map[MAP_ROW][MAP_COL] = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
// int g_col[MAP_ROW] = {3, 3, 3};

// int main()
// {
//     int gridSize = MAP_ROW;
//     int **grid = NULL;
//     int *gridColSize = NULL;

//     /* ¥Ó???¥Î¨Ò™]¤J‰ë?¤¤»Ý­nªº?¦s¦}®ÚÕu¥Î¨Ò™]¤Jªì©l¤Æ */
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
//     int result = orangesRotting(grid, gridSize, gridColSize);

//     /* ?©ñ??¥Î¨Ò™]¤J‰ë?¤¤¥Ó?ªº?¦s */
//     for (int i = 0; i < gridSize; i++) {
//         free(grid[i]);
//     }
//     free(gridColSize);
//     free(grid);
// }