#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 1001
int g_p[MAX_N];

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

void InitHandle(int m)
{
    for (int i = 0; i < m; i++) {
        g_p[i] = i + 1;
    }
}

int FindInP(int *p, int n, int v)
{
    int ans = -1;
    for (int i = 0; i < n; i++) {
        if (v == p[i]) {
            ans = i;
            break;
        }
    }
    return ans;
}

void AdjustP(int *p, int n, int idx)
{
    if (idx == 0) return;
    int pri = p[idx];
    for (int i = idx; i >= 1; i--) {
        p[i] = p[i - 1];
    }
    p[0] = pri;
}

int* processQueries(int* q, int queriesSize, int m, int* returnSize)
{
    InitHandle(m);
    int n = queriesSize;
    int *ret = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        int v = q[i];
        int newIdx = FindInP(g_p, m, v);
        AdjustP(g_p, m, newIdx);
        PrintArray(g_p, m);
        ret[i] = newIdx;
    }
    *returnSize = n;
    return ret;
}

void main()
{
    int a[] = {7,5,5,8,3};
    int m = 8;
    int retsize;
    int *ans = processQueries(a, sizeof(a) / sizeof(int), m, &retsize);
    PrintArray(ans, retsize);
    free(ans);
    return;
}