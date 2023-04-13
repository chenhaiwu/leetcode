#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)


int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;

    return ta > tb;
}

int* numMovesStonesII(int* stones, int stonesSize, int* returnSize)
{
    qsort(stones, stonesSize, sizeof(int), Cmp);
    int max, min;
    int minMinus1 = stones[1] - stones[0] - 1;
    int minMinus2 = stones[stonesSize - 1] - stones[stonesSize - 2] - 1;
    minMinus1 = MIN(minMinus1, minMinus2);
    max = stones[stonesSize - 1] - stones[0] + 1 - stonesSize;
    max -= minMinus1;
    min = max;
    int i = 0;
    int j = 0;
    for (; i < stonesSize; i++) {
        while (j + 1 < stonesSize && stones[j + 1] - stones[i] + 1 <= stonesSize) {
            j++;
        }
        int cost = stonesSize - (j - i + 1);
        if (j - i + 1 == stonesSize - 1 && stones[j] - stones[i] + 1 == stonesSize - 1) {
            cost = 2;
        }
        min = MIN(cost, min);
    }
    int *ret = (int *)malloc(sizeof(int) * 2);
    ret[0] = min;
    ret[1] = max;
    *returnSize = 2;
    return ret;
}

int main()
{
    //int retsize = removeSubfolders(s, words, 4);
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
