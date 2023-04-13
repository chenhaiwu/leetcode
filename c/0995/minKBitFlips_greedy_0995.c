#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>


int minKBitFlips_1(int* A, int ASize, int K)
{
    int ans = 0;
    for (int i = 0; i < ASize; i++) {
        if (A[i] == 0) {
            if (i + K > ASize) {
                return -1;
            } else {
                for (int j = i; j < i + K; j++) {
                    A[j] ^= 1;
                }
                ans++;
            }
        }
    }
    return ans;
}

typedef struct _queue{
    int head;
    int tail;
    int size;
    int *queue
} Queue;

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

int minKBitFlips(int* A, int ASize, int K)
{
    int ans = 0;
    Queue *obj = QueueCreate(ASize + 1);
    for (int i = 0; i < ASize; i++) {
        if (QueueFront(obj) == i) {
            QueueDe(obj);
        }
        if ((A[i] && (QueueSize(obj) % 2 == 0)) || (!A[i] && (QueueSize(obj) % 2 == 1))) {
            continue;
        } else if (i + K <= ASize) {
            QueueEn(obj, i + K);
            ans++;
        } else {
            return -1;
        }
    }
    QueueFree(obj);
    return ans;
}

int main()
{
    int a[] = {0,0,0,1,0,1,1,0};
    int k = 3;
    int ret = minKBitFlips(a, sizeof(a) / sizeof(int), k);
    return ret;
}