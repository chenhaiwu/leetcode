#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)


typedef struct _mynode {
    int bV;
    int bIdx;
    int aV;
} MyNode;

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

void PrintArray2(MyNode* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("(%d,%d)", nums[i].bV, nums[i].bIdx);
    }
    printf("\n");
#endif
}

#define MAX_NUM 10001
MyNode g_mynode[MAX_NUM];
int g_flagA[MAX_NUM];

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

int Cmp2(const void *a, const void *b)
{
    MyNode *ta = (MyNode *)a;
    MyNode *tb = (MyNode *)b;
    if (ta->bV == tb->bV) {
        return ta->bIdx - tb->bIdx;
    }
    return ta->bV - tb->bV;
}

int Cmp3(const void *a, const void *b)
{
    MyNode *ta = (MyNode *)a;
    MyNode *tb = (MyNode *)b;
    return ta->bIdx - tb->bIdx;
}

void PreHandle(int* A, int ASize, int* B, int BSize)
{
    for (int i = 0; i < BSize; i++) {
        g_mynode[i].bIdx = i;
        g_mynode[i].bV = B[i];
    }
    qsort(A, ASize, sizeof(int), Cmp);
    PrintArray(A, ASize);
    qsort(g_mynode, BSize, sizeof(MyNode), Cmp2);
    PrintArray2(g_mynode, BSize);
    memset(g_flagA, 0x0, sizeof(int) * ASize);
}

int FindBestValFromA(int* A, int ASize, int startA, int v)
{
    int ans = -1;
    for (int i = startA; i < ASize; i++) {
        if (A[i] > v) {
            ans = i;
            break;
        }
    }
    return ans;
}

int CurrentUnselV(int* A, int ASize, int start)
{
    int ans = start;
    for (int i = start; i < ASize; i++) {
        if (g_flagA[i] == 0) {
            ans = i;
            g_flagA[i] = 1;
            break;
        }
    }
    return ans;
}

void SetAllSmallVal(int* A, int ASize, int idx)
{
    int startA = 0;
    for (int i = idx; i < ASize; i++) {
        startA = CurrentUnselV(A, ASize, startA);
        g_mynode[i].aV = A[startA];
    }
}

#define MAX_PNUM 50001
int g_flagSel[MAX_PNUM];
int findMaximizedCapital(int k, int w, int *pro, int proSize, int *cap, int capSize)
{
    int ans = w;
    int left = w;
    int max = INT_MIN;
    int maxIdx;
    PrintArray(pro, proSize);
    PrintArray(cap, capSize);
    qsort(cap, capSize, sizeof(int), Cmp);
    memset(g_flagSel, 0x0, sizeof(int) * capSize);
    for (int i = 0; i < k; i++) {
        max = INT_MIN;
        maxIdx = -1;
        int j;
        for (j = 0; j < capSize; j++) {
            if (!g_flagSel[j] && cap[j] <= left) {
                if (pro[j] > max) {
                    max = pro[j];
                    maxIdx = j;
                }
            }
        }
        if (maxIdx == -1) {
            break;
        }
        left += max;
        g_flagSel[maxIdx] = 1;
        ans += pro[maxIdx];
    }
    return ans;
}

int main()
{
    int a[] = {1,2,3};
    int b[] = {0,1,1};
    int k = 2;
    int w = 0;
    int ret = findMaximizedCapital(k, w, a, sizeof(a)/sizeof(int), b, sizeof(b)/sizeof(int));
    printf("ret=%d\n", ret);
    return 0;
}