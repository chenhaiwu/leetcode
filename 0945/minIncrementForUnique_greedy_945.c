#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX_N 40004
int g_hash[MAX_N];
int g_dup[MAX_N];
int g_dupNum;

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

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

void GetDupNums(int* A, int ASize)
{
    g_dupNum = 0;
    for (int i = 0; i < ASize; i++) {
        if (g_hash[A[i]] != 0) {
            g_dup[g_dupNum] = A[i];
            g_dupNum++;
        }
        g_hash[A[i]]++;
    }
    qsort(g_dup, g_dupNum, sizeof(int), Cmp);
    // PrintArray(g_dup, g_dupNum);
}

int Baoli(int* A, int ASize)
{
    printf("asize=%d\n", ASize);
    int ans = 0;
    memset(g_hash, 0x0, sizeof(g_hash));
    memset(g_dup, 0x0, sizeof(int) * ASize);
    GetDupNums(A, ASize);
    if (g_dupNum == 0) {
        return ans;
    }
    for (int i = 0; i < g_dupNum; i++) {
        int dupv = g_dup[i];
        while (dupv < MAX_N && g_hash[dupv] != 0) {
            dupv++;
            if (dupv == MAX_N) {
                dupv = 0;
            }
        }
        
        ans += (dupv - g_dup[i]);
        // if (dupv >= MAX_N) {
        //     printf("duupv=%d, v=%d\n", dupv, g_dup[i]);
        //     PrintArray(&g_hash[g_dup[i]], MAX_N - g_dup[i] - 1);
        // }
        g_hash[dupv] = 1;
    }
    return ans;
}

int minIncrementForUnique(int* A, int ASize)
{
    int ans;
    ans = Baoli(A, ASize);
    return ans;
}

void main()
{
    int ans;
    int A[] = {1, 2, 2};
    ans = minIncrementForUnique(A, sizeof(A) / sizeof(int));
    printf("ans=%d\n", ans);
    int B[] = {3, 2, 1, 2, 1, 7};
    ans = minIncrementForUnique(B, sizeof(B) / sizeof(int));
    printf("ans=%d\n", ans);
    return;
}