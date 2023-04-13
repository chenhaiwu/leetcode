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

int GetFix1(int *a, int len)
{
    int ans = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] == 1) {
            ans++;
        }
    }
    return ans;
}

void HandleFirstKto1(int *a, int *b, int len, int k)
{
    int md = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] == 3) {
            if (md < k) {
                a[i] = 1;
                b[i] = 0;
                md++;
            } else {
                a[i] = 0;
                b[i] = 1;
            }
        }
    }
    PrintArray(a, len);
    PrintArray(b, len);
}

int** reconstructMatrix(int upper, int lower, int* colsum, int colsumSize, int* returnSize, int** returnColumnSizes)
{
    printf("colsumSize=%d\n", colsumSize);
    int sum = 0;
    for (int i = 0; i < colsumSize; i++) {
        sum += colsum[i];
    }
    int fixupper1 = 0;
    int fixlower1 = 0;
    if (sum != upper + lower) {
        *returnSize = 0;
        returnColumnSizes = NULL;
        return NULL;
    }
    int **ret = (int **)malloc(sizeof(int *) * 2);
    int *retCol = (int *)malloc(sizeof(int) * 2);
    for (int i = 0; i < 2; i++) {
        ret[i] = (int *)malloc(sizeof(int) * colsumSize);
        retCol[i] = colsumSize;
    }
    for (int i = 0; i < colsumSize; i++) {
        if (colsum[i] == 0) {
            ret[0][i] = ret[1][i] = 0;
        } else if (colsum[i] == 2) {
            ret[0][i] = ret[1][i] = 1;
        } else {
            ret[0][i] = ret[1][i] = 3;
        }
    }
    fixupper1 = GetFix1(ret[0], colsumSize);
    fixlower1 = GetFix1(ret[1], colsumSize);
    printf("colsumSize=%d, sum=%d, fix1=%d, fix2=%d\n", colsumSize, sum, fixupper1, fixlower1);
    if (fixupper1 > upper || fixlower1 > lower) {
        *returnSize = 0;
        returnColumnSizes = NULL;
        return NULL;
    }
    HandleFirstKto1(ret[0], ret[1], colsumSize, upper - fixupper1);
    *returnSize = 2;
    *returnColumnSizes = retCol;
    return ret;
}

int main()
{
    return 0;
}