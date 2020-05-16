#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

// #define DEGUG_CHW 1
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

int hIndex(int* a, int aSize)
{
    qsort(a, aSize, sizeof(int), Cmp);
    int i;
    int ans = 0;
    while (i < aSize && a[aSize - i - 1] > i) {
        i++;
    }
    return i;
}

int main()
{
    int a[] = {3,0,6,1,5};
    int aSize = sizeof(a) / sizeof(int);
    int k = 3;
    int ret = hIndex(a, aSize);
    return 0;
}
