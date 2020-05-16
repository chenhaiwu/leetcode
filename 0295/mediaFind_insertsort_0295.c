#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

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

/* 
 * ´¡¤J±Æ§Ç
 */

void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


#define MAX_NUM 10000
typedef struct {
    int vals[MAX_NUM];
    int len;
} MedianFinder;

/** initialize your data structure here. */

MedianFinder* medianFinderCreate() {
    MedianFinder *obj = (MedianFinder *)malloc(sizeof(MedianFinder));
    memset(obj, 0x0, sizeof(MedianFinder));
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    int i;
    int right = obj->len - 1;
    for (i = right; i >= 0 && obj->vals[i] > num; i--) {
        obj->vals[i + 1] = obj->vals[i];
    }
    obj->vals[i + 1] = num;
}

double medianFinderFindMedian(MedianFinder* obj) {
    int mid = obj->len / 2;
    if (mid & 1) {
        return double(obj->vals[mid]);
    } else {
        return ((double)obj->vals[mid - 1] + (double)obj->vals[mid]) / 2;
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj);
}

int main()
{
    int a[] = {1,2,3,4,2,3,1,4,2};
    int aSize = sizeof(a) / sizeof(int);
    int k = 3;
    int retSize;
    double *ret = medianSlidingWindow(a, aSize, k, &retSize);
    for (int i = 0; i < retSize; i++) {
        printf("%lf ", ret[i]);
    }
    printf("\n");
    free(ret);
    return 0;
}