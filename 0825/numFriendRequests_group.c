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

bool CheckRequest(int a, int b)
{
    bool ret = true;
    if (b > a || (b > 100 && a < 100)) {
        return false;
    }
    if (b <= a / 2 + 7) {
        return false;
    }
    return true;
}

int numFriendRequests_1(int* nums, int numsSize)
{
    int ret = 0;
    if (numsSize <= 0) {
        return 0;
    }

    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            if (i == j) {
                continue;
            }
            if (CheckRequest(nums[i], nums[j])) {
                ret++;
            }
        }
    }

    return ret;
}

#define AGES_NUM 121
int g_ages[AGES_NUM];

int numFriendRequests(int* nums, int numsSize)
{
    int ret = 0;
    if (numsSize <= 0) {
        return 0;
    }
    memset(g_ages, 0x0, sizeof(g_ages));

    for (int i = 0; i < numsSize; i++) {
        g_ages[nums[i]]++;
    }
    for (int i = 1; i < AGES_NUM; i++) {
        int cntA = g_ages[i];
        if (cntA == 0) {
            continue;
        }
        for (int j = 1; j <= i; j++) {
            int cntB = g_ages[j];
            if (cntB == 0) {
                continue;
            }
            if (j > 100 && i < 100) {
                continue;
            }
            if (j <= i / 2 + 7) {
                continue;
            }
            if (i != j) {
                ret += (cntA * cntB);
            } else {
                ret += (cntA * (cntB - 1));
            }
        }
    }

    return ret;
}

int main()
{
    int nums[] = {16, 17, 18};
    int ret = numFriendRequests(nums, sizeof(nums) / sizeof(int));
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    printf("ret=%d\n", ret);
    return 0;
}
