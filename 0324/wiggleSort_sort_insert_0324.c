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

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

/* 
 * 先qsort，然后再分成前后两半，然后分别从前后两个区间，一次选一个，则一定是满足摆排序
 */
void wiggleSort_1(int* nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), Cmp);
    /* 多申请一个空间，然后取一半时，向上取整，这样在奇数个是，right会多拷一个。所以多申请一个
        赋值时，不需要多拷一个
     */
    int *tmp = (int *)malloc(sizeof(int) * (numsSize + 1));
    int mid = (numsSize + 1) / 2;
    int k = 0;
    PrintArray(nums, numsSize);
    for (int i = 0; i < mid; i++) {
        tmp[k++] = nums[mid - 1 - i];
        /* 有可能会多拷一下mid中间值给最后 */
        tmp[k++] = nums[numsSize - 1 - i];
    }
    for (int i = 0; i < numsSize; i++) {
        nums[i] = tmp[i];
    }
    PrintArray(nums, numsSize);
    free(tmp);
}

/* 
 * 这题，我们知道，前后两个区间的数，其实不一定要有序，right区间都比left区间要大就行了。
 * 所以，我们没必要进行qsort，只要找到中位数，能区分原来的数在哪个区间即可。然后对原来的数，
 * 小于大于中位数的，分别用前项指针定位即可。但是不能使用二分法，因为有可能有些值相等，要采用三分法，
 * 保证相等的值，都放到中间来。三分法就不写了，也不会更快。
 */

void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(int *nums, int low, int high)
{
    int midIdx = low;
    int pivot = nums[low];
    for (int i = low + 1; i <= high; i++) {
        if (nums[i] < pivot) {
            Swap(&nums[i], &nums[midIdx + 1]);
            midIdx++;
        }
    }
    Swap(&nums[low], &nums[midIdx]);
    return midIdx;
}

int GetMidVal(int *nums, int low, int high)
{
    int midIdx = (low + high) / 2;
    while (1) {
        int pos = Partition(nums, low, high);
        if (pos == midIdx) {
            break;
        } else if (pos < midIdx) {
            low = pos + 1;
        } else {
            high = midIdx - 1;
        }
    }
    return nums[midIdx];
}

int g_num[8] = {3,4,6,2,7,8,1,9};
void wiggleSort(int* nums, int numsSize)
{
    int mid = GetMidVal(g_num, 0, 7);
}

int main()
{
    int a[] = {1,1,2,1,2,2,1};
    int aSize = sizeof(a) / sizeof(int);
    int k = 3;
    wiggleSort(a, aSize);
    return 0;
}