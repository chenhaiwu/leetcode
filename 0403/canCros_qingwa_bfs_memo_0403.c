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

#define MAX_N 1100
#define MAX_QUEUE_SIZE 100000
#define MAX_K 1000 // 1000个k的值
typedef struct _node {
    int len;
    int list[MAX_K];
} MyNode;
MyNode g_visit[MAX_N];

/* 使用BFS
 * 每次把当前的位置及 k 入队保存(pos, k), pos == n - 1时, true;
 * 算法可以了，不过超时，决定使用二维数据缓存一下。
 */
int FindValueIdx(int* s, int len, int start, int newv)
{
    int pos = -1;
    for (int i = start; i < len && s[i] <= newv; i++) {
        if (s[i] == newv) {
            pos = i;
            break;
        }
    }
    return pos;
}

bool Bfs(int* s, int stonesSize)
{
    if (stonesSize < 2) return false;
    printf("%d %d\n", s[0], s[1]);
    if (s[0] != 0 || s[1] != 1) {
        return false;
    }
    int n = stonesSize;
    int target = s[n - 1];
    memset(g_visit, 0x0, sizeof(g_visit));
    Queue *q = QueueCreate(MAX_QUEUE_SIZE);
    QueueEn(q, 1);
    QueueEn(q, 1);
    g_visit[1].list[g_visit[1].len] = 1;
    g_visit[1].len++;
    bool ans = false;
    while (QueueIsEmpty(q) != VOS_OK) {
        int laySize = QueueSize(q) / 2;
        for (int i = 0; i < laySize; i++) {
            int pos = QueueFront(q);
            QueueDe(q);
            int k = QueueFront(q);
            QueueDe(q);
            int v = s[pos];
            if (v == target) {
                ans = true;
                break;
            }
            for (int j = 0; j < 3; j++) {
                int newk = k - 1 + j;
                int newv = v + newk;
                if (newv <= v) continue;
                int newPos = FindValueIdx(s, n, pos + 1, newv);
                if (newPos == -1) continue;
                bool bFlag = true;
                for (int t = 0; t < g_visit[newPos].len; t++) {
                    if (g_visit[newPos].list[t] == newk) {
                        bFlag = false;
                        break;
                    }
                }
                if (!bFlag) continue;
                QueueEn(q, newPos);
                QueueEn(q, newk);
                g_visit[newPos].list[g_visit[newPos].len] = newk;
                g_visit[newPos].len++;
            }
        }
    }
    QueueFree(q);
    return ans;
}

/* DFS 注意每次能跑的步数，只是jumpsize，也就是k 其实是在 1100之内的 */
int g_memo[MAX_N][MAX_N];

bool Step(int *s, int len, int start, int k)
{
    if (start == len - 1) return true;
    if (g_memo[start][k] != -1) {
        return g_memo[start][k];
    }
    for (int i = start + 1; i < len; i++) {
        int gap = s[i] - s[start];
        if (gap <= k + 1 && gap >= k - 1) {
            if (Step(s, len, i, gap)) {
                g_memo[start][k] = 1;
                return 1;
            }
        }

    }
    g_memo[start][k] = (start == len - 1) ? 1 : 0;
    return g_memo[start][k];
}

bool Dfs(int* s, int len)
{    
    if (len < 2) return false;
    if (s[0] != 0 || s[1] != 1) {
        return false;
    }
    memset(g_memo, -1, sizeof(g_memo));
    bool ans = Step(s, len, 0, 0);
    return ans;
}

bool canCross(int* s, int stonesSize)
{
    bool ans;
    // ans = Bfs(s, stonesSize);
    ans = Dfs(s, stonesSize);
    return ans;
}

int main()
{
    bool ans;
    int c[] = {0,2};
    ans = canCross(c, sizeof(c) / sizeof(int));
    int a[] = {0,1,3,5,6,8,12,17};
    ans = canCross(a, sizeof(a) / sizeof(int));
    int b[] = {0,1,2,3,4,8,9,11};
    ans = canCross(b, sizeof(b) / sizeof(int));
    return (int)ans;
}