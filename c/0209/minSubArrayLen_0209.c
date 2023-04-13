
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
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

#define MAXN 10000
int g_qianzuihe[MAXN];

void CountQianzuihe(int* nums, int numsSize)
{
    g_qianzuihe[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        g_qianzuihe[i + 1] = g_qianzuihe[i] + nums[i];
    }
}

int minSubArrayLen_1(int s, int* nums, int numsSize)
{
    int w;
    bool bFind = false;
    CountQianzuihe(nums, numsSize);
    for (w = 1; w <= numsSize; w++) {
        for (int i = 0; i + w <= numsSize; i++) {
            int sum = g_qianzuihe[i + w] - g_qianzuihe[i];
            if (sum >= s) {
                bFind = true;
                break;
            }            
        }
        if (bFind) {
            break;
        }
    }
    return bFind ? 0 : w;
}

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)
int minSubArrayLen(int s, int* nums, int numsSize)
{
    int w = INT_MAX;
    int left = 0;
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        while (sum >= s) {
            w = MIN(w, i - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    return w == INT_MAX ? 0 : w;
}

int main()
{
    int nums[] = {2,3,1,2,4,3};
    int retsize = minSubArrayLen(7, nums, sizeof(nums) / sizeof(int));
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
