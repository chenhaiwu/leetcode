#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define DEGUG_CHW 0
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

int FuncMin(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

#define MAX_LEN 1001
int g_valueState[MAX_LEN][2];

/* flag=1为上次idx-1交换了位置，flag=0为上次idx-1没有交换位置
// idx为此时的索引
// g_valueState[idx][flag]为在flag状态下且idx索引以前都是递增，把idx（包括idx）之后的变为递增需
*/
int GetSteps(int idx, int* A, int* B, int ASize, int flag)
{
    if (idx == ASize) {
        return 0;
    }
    /* 两个状态的记忆化 */
    if (g_valueState[idx][flag] != -1) {
        return g_valueState[idx][flag];
    }
    int swap = INT_MAX, noswap = INT_MAX;
    /* 选择不换，但是一定要满足题目要求，分开两个状态（前一个状态是换的，还是没换过的）检查 */
    if ((flag == 0 && A[idx - 1] < A[idx] && B[idx - 1] < B[idx]) ||
        (flag == 1 && A[idx - 1] < B[idx] && B[idx - 1] < A[idx])) {
        swap = GetSteps(idx + 1, A, B, ASize, 0);
    }
    /* 满足换的条件，然后算出换的值，再与上面这一步不换进行对比，取较小值 */
    if ((flag == 0 && A[idx - 1] < B[idx] && B[idx - 1] < A[idx]) ||
        (flag == 1 && A[idx - 1] < A[idx] && B[idx - 1] < B[idx])) {
        noswap = GetSteps(idx + 1, A, B, ASize, 1) + 1;
    }
    swap = FuncMin(swap, noswap);
    g_valueState[idx][flag] = swap;
    return swap;
}

int minSwap(int* A, int ASize, int* B, int BSize)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < ASize; j++) {
            g_valueState[j][i] = -1;
        }
    } 
    for (int i = 0; i < 2; i++) {
        PrintArray(g_valueState[i], ASize);
    }
    int s = GetSteps(1, A, B, ASize, 1) + 1;
    int n = GetSteps(1, A, B, ASize, 0);
    int ans = FuncMin(s, n);
    return ans;
}

int main()
{
    int a[] = {1, 3, 5, 4};
    int b[] = {1, 2, 3, 7};
    int ret = minSwap(a, sizeof(a) / sizeof(int), b, sizeof(b) / sizeof(int));
    printf("ret=%d\n");
    return 0;
}
