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

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

typedef struct _mynode {
    int starttime;
    int endtime;
    int profile;
} MyNode;

#define MAX_NUM 10000
MyNode g_data[MAX_NUM];
int g_dp[MAX_NUM];

/*
序列型dp
dp[i]表示到第i个所能赚到的最大金钱
建立一个类保存工作的startTime,endTime,profit
根据endTime从小到大排序
转移:
if(job[j].end<=job[i].start) dp[i]=Math.max(dp[i],dp[j]+job[i].profit);
没有的话,dp[i]=Math.max(dp[i-1],job[i].profit); 第i个选择第i-1个的状态或选择自己单独一个
*/
void PreHandle(int* startTime, int startTimeSize, int* endTime, int* profit)
{
    for (int i = 0; i < startTimeSize; i++) {
        g_data[i].starttime = startTime[i];
        g_data[i].endtime = endTime[i];
        g_data[i].profile = profit[i];
    }
}

int Cmp(const void *a, const void *b)
{
    MyNode *ta = (MyNode *)a;
    MyNode *tb = (MyNode *)b;
    if (ta->endtime == tb->endtime) {
        return ta->starttime - tb->starttime;
    }
    return ta->endtime > tb->endtime;
}

int jobScheduling(int* startTime, int startTimeSize, int* endTime, int endTimeSize, 
    int* profit, int profitSize)
{
    PreHandle(startTime, startTimeSize, endTime, profit);
    qsort(g_data, startTimeSize, sizeof(MyNode), Cmp);
    int n = startTimeSize;
    for (int i = 0; i < n; i++) {
        g_dp[i] = g_data[i].profile;
    }
    for (int i = 1; i < n; i++) {
        // Not select
        g_dp[i] = MAX(g_dp[i - 1], g_data[i].profile);
        // Select
        for (int j = i - 1; j >= 0; j--) {
            if (g_data[j].endtime <= g_data[i].starttime) {
                g_dp[i] = MAX(g_dp[j] + g_data[i].profile, g_dp[i]);
                // 注意这里是可以break，因为j从i的最大值往小的找，只要找到一个j符合条件的，
                // 就说明这个是离i最近的可以执行完的任务
                break;
            }
        }
    }
    return g_dp[n - 1];
}

int main()
{
    int nums1[] = {1,2,3,3};
    int nums2[] = {3,4,5,6};
    int nums3[] = {50,10,40,70};
    int k = sizeof(nums1) / sizeof(int);
    int retsize = jobScheduling(nums1, k, nums2, k, nums3, k);
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
#if 0

int main()
{
    printf("hello world\n");
    return 0;
}
#endif