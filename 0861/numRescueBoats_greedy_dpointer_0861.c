#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

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

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

int numRescueBoats(int* people, int peopleSize, int limit)
{
    int ans = 0;
    qsort(people, peopleSize, sizeof(int), Cmp);
    PrintArray(people, peopleSize);
    int left = 0;
    int right = peopleSize - 1;
    int times = 2;
    while (left <= right) {
        int cur = people[right];
        right--;
        times = 1;
        while (right >= left && times > 0 && cur + people[right] <= limit) {
            cur += people[right];
            right--;
            times--;
        }
        while (left <= right && times > 0 && cur + people[left] <= limit) {
            cur += people[left];
            left++;
            times--;
        }
        ans++;
    }
    return ans;
}

int main()
{
    int a[] = {2,2,3,2,3};
    int w = 6;
    int ret = numRescueBoats(a, sizeof(a)/sizeof(int), w);
    printf("ret=%d\n", ret);
    return 0;
}