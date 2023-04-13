#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

/* 
 * 只要还有能量，就一直让令牌正面朝上，直到没有能量的时候，让一个令牌反面朝上从而获得能量继续之前的操作。
一定要小心处理边界条件，不然很有可能会写出错误的答案。这里要牢牢记住，在有能量时候，只能让令牌正面朝上，直到能量不够用了才能让令牌反面朝上
 */
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

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

int bagOfTokensScore(int* tokens, int tokensSize, int p)
{
    if (tokensSize == 0) {
        return 0;
    }
    PrintArray(tokens, tokensSize);
    qsort(tokens, tokensSize, sizeof(int), Cmp);
    PrintArray(tokens, tokensSize);
    int left = 0;
    int right = tokensSize - 1;
    int ans = 0;
    int score = 0;
    while (left <= right) {
        if (p >= tokens[left]) {
            p -= tokens[left];
            left++;
            score++;
            ans = MAX(score, ans);
        } else {
            if (score <= 0) {
                break;
            }
            score--;
            p += tokens[right];
            right--;
        }
    }
    return ans;
}

int g_test[] = {10,3,2,1,9,8,7,11};
int main()
{
    int len = sizeof(g_test) / sizeof(int);
    int *input = (int *)malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        input[i] = g_test[i];
    }
    int p = 5;
    qsort(input, len, sizeof(int), Cmp);
    PrintArray(input, len);
    int ret = bagOfTokensScore(input, len, p);
    printf("ret=%d\n", ret);
    return 0;
}