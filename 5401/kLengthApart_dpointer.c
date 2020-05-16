#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>


bool kLengthApart(int* nums, int numsSize, int k)
{
    if (k == 0) {
        return true;
    }
    int left = 0;
    int right = 0;
    // right 指向第一个1
    while (right < numsSize && nums[right] == 0) {
        right++;
    }
    left = right;
    right = left + 1;
    if (right == numsSize) {
        return true;
    }
    while (right < numsSize) {
        while (right < numsSize && nums[right] == 0) {
            right++;
        }
        if (right == numsSize) {
            return true;
        }
        if (right - left - 1 < k) {
            return false;
        }
        left = right;
        right++;
    }
    return true;
}

void main()
{
    int a[] = {1,0,0,0,1,0,0,1};
    bool ans = kLengthApart(a, sizeof(a) / sizeof(int), 2);
    return ans;
}