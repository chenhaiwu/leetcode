#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define NUM_MAX 30001
#define VALUE_MAX 200002
int g_hash[VALUE_MAX];
int g_hash2[VALUE_MAX];

void PrintValue(int* A, int ASize)
{
    for (int i = 0; i < ASize; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

bool HandleGroup(int* A, int ASize, int *hash)
{
    int tmp;
    for (int i = 0; i < ASize; i++) {
        tmp = A[i];
        if (hash[tmp] <= 0) {
            continue;
        }
        if (hash[tmp * 2] <= 0) {
            return false;
        }
        hash[tmp]--;
        hash[2 * tmp]--;
    }
    return true;
}

void ReverseGroup(int* A, int ASize)
{
    int tmp;
    for (int i = 0; i < ASize / 2; i++) {
        tmp = A[i];
        A[i] = A[ASize - 1 - i];
        A[ASize - 1 - i] = tmp;
    }
}

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

bool canReorderDoubled(int* A, int ASize)
{
    bool bRet = false;
    if (ASize % 2 != 0) {
        return bRet;
    }
    qsort(A, ASize, sizeof(int), Cmp);
    //PrintValue(A, ASize);
    int a1[NUM_MAX], a2[NUM_MAX];
    int a1Size = 0, a2Size = 0, zeroSize = 0;
    memset(g_hash, 0x0, sizeof(g_hash));
    memset(g_hash2, 0x0, sizeof(g_hash2));
    int tmp;
    for (int i = 0; i < ASize; i++) {
        tmp = A[i];
        if (tmp < 0) {
            a1[i] = -A[i];
            g_hash[-tmp]++;
            a1Size++;
        } else if (tmp == 0) {
            zeroSize++;
        } else {
            a2[i - a1Size - zeroSize] = A[i];
            g_hash2[tmp]++;
            a2Size++;
        }
    }
    if (a1Size % 2 != 0 || a2Size % 2 != 0 || zeroSize % 2 != 0) {
        return bRet;
    }
    ReverseGroup(a1, a1Size);
    //PrintValue(a1, a1Size);
    //PrintValue(a2, a2Size);
    bRet = HandleGroup(a1, a1Size, g_hash);
    if (!bRet) {
        return bRet;
    }
    bRet = HandleGroup(a2, a2Size, g_hash2);
    return bRet;
}

void main()
{
    int nums[] = {4, 3, 2, 3, 5, 2, 1};
    bool ret = canReorderDoubled(nums, sizeof(nums) / sizeof(int));
    printf("ret = %d\n", ret);
}