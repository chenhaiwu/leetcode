#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MIN(a, b) (a) < (b) ? (a) : (b)

int findMin_1(int* nums, int numsSize)
{
    int ret = INT_MAX;
    for (int i = 0; i < numsSize; i++) {
        ret = MIN(ret, nums[i]);
    }
    return ret;
}

int findMin(int* nums, int numsSize)
{
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {            
            right = mid;
        } else {
            right = right - 1;
        }
    }
    return nums[left];
}

int main()
{
    //int retsize = removeSubfolders(s, words, 4);
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
