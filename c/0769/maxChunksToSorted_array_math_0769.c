#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

int maxChunksToSorted(int* arr, int arrSize)
{
    int ans = 0;
    int max = INT_MIN;
    for (int i = 0; i < arrSize; i++) {
        max = MAX(max, arr[i]);
        if (max == i) {
            ans++;
        }
    }
    return ans;
}

int main()
{
    int nums[5] = {1, 0, 2, 3, 4};
    int retsize = maxChunksToSorted(nums, sizeof(nums) / sizeof(int));
    return 0;
}
