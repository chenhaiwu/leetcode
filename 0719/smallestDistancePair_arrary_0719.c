#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

void PrintInfo(int* nums, int numsSize, int k)
{
    printf("k=%d, size=%d\n", k, numsSize);
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

int smallestDistancePair_1(int* nums, int numsSize, int k)
{
    if (numsSize > 9999) {return 0;}
    int *q = (int *)malloc(sizeof(int) * (numsSize * (numsSize - 1) / 2));
    int ret = 0;
    int t = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
                q[t++] = abs(nums[i] - nums[j]);
        }
    }
    //PrintInfo(q, t, k);
    qsort(q, t, sizeof(int), Cmp);
    //PrintInfo(q, t, k);
    ret = q[k - 1];
    return ret;
}


#define MAX_NUMS 1000000

int smallestDistancePair_2(int* nums, int numsSize, int k)
{
    int q[MAX_NUMS] = {0};
    int ret = 0;
    int t = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
                t = abs(nums[i] - nums[j]);
                q[t]++;
        }
    }
    //PrintInfo(q, t, k);
    int cnt = 0;
    for (int i = 0; i < MAX_NUMS; i++) {
        cnt += q[i];
        if (cnt >= k) {
            ret = i;
            break;
        }
    }
    //PrintInfo(q, t, k);
    return ret;
}

int smallestDistancePair(int* nums, int numsSize, int k)
{
    int ans = 0;
    qsort(nums, numsSize, sizeof(int), Cmp);
    int left = 0;
    int right = nums[numsSize - 1] - nums[0];
    while (left < right) {
        int mid = left + (right - left) / 2;
        int cnt = 0;
        int start = 0;
        /* 统计所有点到当前i right的点，前面一半mid个大小的，数总量 */
        for (int i = 0; i < numsSize; i++) {
            while (start < numsSize && nums[i] - nums[start] > mid) {
                start++;
            }
            cnt += i - start;
        }
        if (cnt < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

void main()
{
    int a[] = {1, 3, 1};
    int k = 1;
    int ret = smallestDistancePair(a, sizeof(a) / sizeof(int), k);
    printf("ret = %d\n", ret);
}