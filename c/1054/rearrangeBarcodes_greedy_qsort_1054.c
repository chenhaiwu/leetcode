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
#define MAX_NUM 10001
typedef struct _mynode {
    int c;
    int cnt;
} MyNode;
MyNode g_flag[MAX_NUM];
int g_num;

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

void PrintArray2(MyNode* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("(%d,%d)", nums[i].c, nums[i].cnt);
    }
    printf("\n");
#endif
}

int Cmp(const void *a, const void *b)
{
    MyNode *ta = (MyNode *)a;
    MyNode *tb = (MyNode *)b;
    if (ta->cnt == tb->cnt) {
        return ta->c - tb->c;
    }
    return tb->cnt - ta->cnt;
}

void PreHandle(int* barcodes, int barcodesSize)
{
    memset(g_flag, 0x0, sizeof(g_flag));
    g_num = 0;
    for (int i = 0; i < barcodesSize; i++) {
        g_flag[barcodes[i]].cnt++;
        g_flag[barcodes[i]].c = barcodes[i];
    }
}

int* rearrangeBarcodes(int* barcodes, int barcodesSize, int* returnSize)
{
    PreHandle(barcodes, barcodesSize);
    int *ret = (int *)malloc(sizeof(int) * barcodesSize);
    int maxIdx = 1;
    int maxCnt = g_flag[1].cnt;
    for (int i = 2; i < MAX_NUM; i++) {
        if (g_flag[i].cnt > maxCnt) {
            maxIdx = i;
            maxCnt = g_flag[i].cnt;
        }
    }

    int danIdx = 0;
    int suanIdx = 1;
    while (danIdx < barcodesSize && g_flag[maxIdx].cnt > 0) {
        ret[danIdx] = g_flag[maxIdx].c;
        g_flag[maxIdx].cnt--;
        danIdx += 2;
    }
    PrintArray(ret, barcodesSize);
    for (int i = 1; i < MAX_NUM; i++) {
        if (g_flag[i].cnt == 0) {
            continue;
        }
        while (danIdx < barcodesSize && g_flag[i].cnt > 0) {
            ret[danIdx] = g_flag[i].c;
            danIdx += 2;
            g_flag[i].cnt--;
        }
        while (suanIdx < barcodesSize && g_flag[i].cnt > 0) {
            ret[suanIdx] = g_flag[i].c;
            suanIdx += 2;
            g_flag[i].cnt--;
        }
        if (suanIdx == barcodesSize - 1) {
            break;
        }
    }
    *returnSize = barcodesSize;
    return ret;
}

int main()
{
    int a[] = {1,1,1,1,2,2,3,3};
    int retSize;
    int *ret = rearrangeBarcodes(a, sizeof(a) / sizeof(int), &retSize);
    PrintArray(ret, retSize);
    // printf("ret=%s\n", ret);
    return 0;
}