#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

int longestSubarray(int* nums, int numsSize, int limit)
{
    int ans = 0;
    int left = 0;
    int right = 0;
    int max = INT_MIN;
    int min = INT_MAX;
    if (numsSize == 1) {
        return 1;
    }
    max = MAX(max, nums[0]);
    min = MIN(min, nums[0]);
    left = right;
    right = left + 1;
    max = MAX(max, nums[1]);
    min = MIN(min, nums[1]);
    if (right == numsSize) {
        return max - min >= limit ? 2 : 1;
    }
    while (right < numsSize) {
        max = MAX(max, nums[right]);
        min = MIN(min, nums[right]);
        if (max - min <= limit) {
            ans = MAX(right - left + 1, ans);
            right++;
        } else {
            while (left <= right && max - min > limit) {
                if (nums[left] == min) {
                    int t = INT_MAX;
                    for (int i = left + 1; i <= right; i++) {
                        t = MIN(t, nums[i]);
                    }
                    min = t;
                }
                if (nums[left] == max) {
                    int t = INT_MIN;
                    for (int i = left + 1; i <= right; i++) {
                        t = MAX(t, nums[i]);
                    }
                    max = t;
                }
                left++;
            }
        }
    }
    return ans;
}

void main()
{
    int a[] = {10,1,2,4,7,2};
    int ans = longestSubarray(a, sizeof(a) / sizeof(int), 5);
    return ans;
}