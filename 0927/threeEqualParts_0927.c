#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define DEGUG_CHW
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

void PrintMatrix(int** grid, int gridSize, int* gridColSize)
{
#ifdef DEGUG_CHW
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridColSize[row]; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
#endif
}

/* 
 */
int GetTotal1(int* A, int ASize)
{
    int ans = 0;
    for (int i = 0; i < ASize; i++) {
        if (A[i] == 1) {
            ans++;
        }
    }
    return ans;
}

int* threeEqualParts(int* A, int ASize, int* returnSize)
{
    int *ret = (int *)malloc(2 * sizeof(int));
    ret[0] = -1;
    ret[1] = -1;
    *returnSize = 2;
    int sum1 = GetTotal1(A, ASize);
    if (sum1 % 3 != 0) {
        return ret;
    }
    /* 如果全是0，没有1的情况特定处理下 */
    if (sum1 == 0) {
        ret[0] = 0;
        ret[1] = ASize - 1;
        return ret;
    }
    int zero0 = 0, zero1 = 0, zero2 = 0, zero3 = 0;
    int start0 = 0, end0 = 0, start1 = 0, end1 = 0, start2 = 0, end2 = 0;
    int ave1 = sum1 / 3;
    int cnt = 0;
    for (int i = 0; i < ASize; i++) {
        if (A[i] == 0) {
            continue;
        }
        cnt++;
        if (cnt == 1) {
            start0 = i;
        }
        if (cnt == ave1) {
            end0 = i;
        }
        if (cnt == ave1 + 1) {
            start1 = i;
        }
        if (cnt == ave1 * 2) {
            end1 = i;
        }
        if (cnt == ave1 * 2 + 1) {
            start2 = i;
        }
        if (cnt == ave1 * 3) {
            end2 = i;
        }
    }
    zero3 = ASize - end2 - 1;
    zero2 = start2 - end1 - 1;
    zero1 = start1 - end0 - 1;
    zero0 = start0;
    if (end0 - start0 == end1 - start1 && end1 - start1 == end2 - start2) {
        int len1 = end0 - start0 + 1;
        for (int i = 0; i < len1; i++) {
            if (A[start0 + i] != A[start1 + i] || A[start0 + i] != A[start2 + i] ||
                A[start1 + i] != A[start2 + i]) {
                return ret;
            }
        }
        /* 再保证后缀0足够 */
        //if (zero3 != 0) {
        int numLen = ASize;
        if (zero1 >= zero3 && zero2 >= zero3) {
            ret[0] = end0 + zero3;
            ret[1] = end1 + zero3 + 1;
        }
        return ret;
        //}
    } else {
        return ret;
    }
}

int main()
{
    int a[] = {1,1,0,1,1};
    int retSize;
    int *ret = threeEqualParts(a, sizeof(a) / sizeof(int), &retSize);
    PrintArray(ret, retSize);
    return 0;
}