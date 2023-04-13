#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define NODE_MAX 200001
int g_pre[NODE_MAX];

int Find(int i)
{
    if (i != g_pre[i]) {
        g_pre[i] = Find(g_pre[i]);
    }
    return g_pre[i];
}

void Join(int i, int j)
{
    int pi = Find(i);
    int pj = Find(j);
    if (pi == pj) {
        return;
    } else if (pi < pj) {
        g_pre[pj] = pi;
    } else {
        g_pre[pi] = pj;
    }
}

void HanldeAllParnet(int len)
{
    for (int i = 0; i < len; i++) {
        Find(i);
    }
}

void PrintUnion(int len)
{
    for (int i = 0; i < len; i++) {
        printf("%d ", g_pre[i]);
    }
    printf("\n");
}

void InitUnion(int *A, int ASize)
{
    for (int i = 0; i < ASize; i++) {
        if (A[i] % 2 == 0) {
            g_pre[i] = 0;
        } else {
            g_pre[i] = i;
        }
    }
}

bool HasTheSameMulti(int a, int b)
{
    if (a > b) {
        return HasTheSameMulti(b, a);
    }
    if (a == 1) {
        return false;
    }
    if (a == 0 || b % a == 0) {
        return true;
    }
    for (int i = 3; i <= a / 2 + 1; i += 2) {
        if (a % i == 0 && b % i == 0) {
            return true;
        }
    }
    return false;
}

void HanldeUnion(int *A, int ASize)
{
    for (int i = 1; i < ASize; i++) {
        // if (A[i] % 2 == 0) {
        //     continue;
        // }
        for (int j = i + 1; j < ASize; j++) {
            if (HasTheSameMulti(A[i], A[j])) {
                Join(i, j);
            }
        }
    }
}

int g_hash[NODE_MAX];
int CaluUnion(int ASize)
{
    memset(g_hash, 0x0, sizeof(int) * ASize);
    for (int i = 0; i < ASize; i++) {
        g_hash[g_pre[i]]++;
    }
    g_hash[0]--;
    int max = INT_MIN;
    for (int i = 0; i < ASize; i++) {
        if (g_hash[i] > max) {
            max = g_hash[i];
        }
    }
    return max;
}

int largestComponentSize(int* A, int ASize)
{
    int *newA = (int *)malloc(sizeof(int) * (ASize + 1));
    newA[0] = 0;
    for (int i = 0; i < ASize; i++) {
        newA[i + 1] = A[i];
    }
    ASize = ASize + 1;
    InitUnion(newA, ASize);
    PrintUnion(ASize);
    HanldeUnion(newA, ASize);
    PrintUnion(ASize);
    HanldeAllParnet(ASize);
    PrintUnion(ASize);
    int ret = CaluUnion(ASize);
    PrintUnion(ASize);
    return ret;
}

void main()
{
    int nums[] = {1,2,3,4,5,6,7,8,9};
    int ret = largestComponentSize(nums, sizeof(nums) / sizeof(int));
    printf("ret = %d\n", ret);
}