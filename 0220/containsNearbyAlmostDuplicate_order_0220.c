#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)


typedef struct _mynode {
    int v;
    int idx;
} MyNode;
/* 
 * 
 */
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
        printf("(%d,%d)", nums[i].v, nums[i].idx);
    }
    printf("\n");
#endif
}

int Cmp(const void *a, const void *b)
{
    MyNode *ta = (MyNode *)a;
    MyNode *tb = (MyNode *)b;
    if (ta->v == tb->v) {
        return ta->idx - tb->idx;
    }
    return ta->v > tb->v ? 1 : -1;
}

void PreHandle(MyNode *array, int* nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++) {
        array[i].v = nums[i];
        array[i].idx = i;
    }
}

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t)
{
    bool ret = false;
    MyNode *array = (int *)malloc(sizeof(MyNode) * numsSize);
    PreHandle(array, nums, numsSize);
    qsort(array, numsSize, sizeof(MyNode), Cmp);
    PrintArray2(array, numsSize);
    int right;
    for (int i = 0; i < numsSize; i++) {
        right = i + 1;
        long t2 = (long)array[i].v;
        while (right < numsSize) {
            long t1 = (long)array[right].v;
            if (t1 - t2 > t) {
                break;
            }
            if (abs(array[right].idx - array[i].idx) <= k) {
                return true;
            }
            right++;
        }
    }
    free(array);
    return ret;
}

bool containsNearbyAlmostDuplicate_1(int* nums, int numsSize, int k, int t)
{
    bool ret = false;
    for (int i = 0; i < numsSize; i++) {
        for (int j = MAX(i - k, 0); j < i; j++) {
            long t1 = (long)nums[i];
            long t2 = (long)nums[j];
            if (labs(t1 - t2) <= (long)t) {
                return true;
            }
        }
    }
    return ret;
}

int main()
{
    int a[] = {1,5,9,1,5,9};
    int k = 2;
    int t = 3;
    bool ret = containsNearbyAlmostDuplicate(a, sizeof(a)/sizeof(int), k, t);
    printf("ret=%d\n", ret);
    return 0;
}