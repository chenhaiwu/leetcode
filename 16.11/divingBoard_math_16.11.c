#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int* divingBoard(int shorter, int longer, int k, int* returnSize)
{
    int retSize = 0;
    int *ret = (int *)malloc((k + 1) * sizeof(int));
    if (k == 0) {
        *returnSize = 0;
        return NULL;
    }
    if (shorter == longer) {
        *returnSize = 1;
        ret[0] = k * shorter;
        return ret;
    }

    for (int i = k; i >= 0; i--) {
        ret[retSize] = shorter * i + longer * (k - i);
        retSize++;
    }
    *returnSize = retSize;
    return ret;
}

void main()
{
    int retSize;
    int shorter = 1;
    int longer = 2;
    int k = 3;
    int * a = divingBoard(shorter, longer, k, &retSize);
    PrintArray(a, retSize);
    free(a);
    return;
}