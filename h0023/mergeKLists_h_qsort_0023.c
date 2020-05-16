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

struct ListNode {
    int val;
    struct ListNode *next;
};

#define MAX_N 50001
int g_v[MAX_N];
int g_n;

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
int Cmp(void *a, void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta - tb;
}

struct ListNode* mergeKLists2(struct ListNode** lists, int listsSize)
{
    if (listsSize == 0) return NULL;
    memset(g_v, 0x0, sizeof(g_v));
    g_n = 0;
    struct ListNode* p = NULL;
    int i = 0;
    p = lists[0];
    while (!p) {
        i++;
        p = lists[i];
    }
    struct ListNode* prev = p;

    struct ListNode* pHead = lists[0];
    while (1) {
        while (p) {
            g_v[g_n++] = p->val;
            prev = p;
            p = p->next;
        }
        i++;
        if (i == listsSize) {
            break;
        } else {
            if (!lists[i]) continue;
            prev->next = lists[i];
            p = prev->next;
        }
    }
    qsort(g_v, g_n, sizeof(int), Cmp);
    p = pHead;
    for (int i = 0; i < g_n; i++) {
        p->val = g_v[i];
        p = p->next;        
    }
    return pHead;
}


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if (listsSize == 0) return NULL;
    memset(g_v, 0x0, sizeof(g_v));
    g_n = 0;
    struct ListNode* p = NULL;
    for (int i = 0; i < listsSize; i++) {
        p = lists[i];
        while (p) {
            g_v[g_n++] = p->val;
            free(p);
            p = p->next;
        }
    }
    if (g_n == 0) return NULL;
    PrintArray(g_v, g_n);
    qsort(g_v, g_n, sizeof(int), Cmp);
    PrintArray(g_v, g_n);

    struct ListNode* pHead = (struct ListNode *)malloc(sizeof(struct ListNode));
    p = pHead;
    for (int i = 0; i < g_n; i++) {
        struct ListNode* pnew = (struct ListNode *)malloc(sizeof(struct ListNode));
        memset(pnew, 0x0, sizeof(struct ListNode));
        p->val = g_v[i];
        p->next = pnew;
        p = pnew;      
    }
    return pHead;
}

int main()
{
    return 0;
}