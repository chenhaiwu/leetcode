#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    printf("total cnt=%d\n", numsSize);
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

int search(int* nums, int numsSize, int target)
{
    int ret = -1;
    int left = 0, right = numsSize - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left + 1) / 2;
        if (nums[mid] == target) {
            ret = mid;
            break;
        }
        if (nums[left] < nums[mid]) {
            if (target < nums[mid] && nums[left] <= target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return ret;
}

int search_2(int* nums, int numsSize, int target)
{
    int ret = -1;
    int left = 0, right = numsSize - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            ret = mid;
            break;
        }
        if (nums[mid] < nums[right]) {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            if (target < nums[mid] && nums[left] <= target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    return ret;
}

int main()
{
    int nums[] = {3,1};
    int ret = search(nums, sizeof(nums) / sizeof(int), 1);
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    ret = search(nums, sizeof(nums) / sizeof(int), 0);
    return ret;
}
