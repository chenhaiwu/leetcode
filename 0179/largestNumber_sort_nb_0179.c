#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* 
 * ´¡¤J±Æ§Ç
 */


#define NUM_LEN 11
#define MAX_NUM 10000

char ** PreHanlde(int* nums, int numsSize)
{
    char **sNum = (int **)malloc(sizeof(char *) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        sNum[i] = (char *)malloc(sizeof(char) * NUM_LEN);
        memset(sNum[i], 0x0, NUM_LEN);
        sprintf(sNum[i], "%d", nums[i]);
        printf("%s\n", sNum[i]);
    }
    return sNum;
}

void AfterHandle(char **sNum, int* nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++) {
        free(sNum[i]);
    }
    free(sNum);
}

int Cmp(void *a, void *b)
{
    char *p1 = *(char **)(a);
    char *p2 = *(char **)(b);
    char tmp1[NUM_LEN * 2] = {0};
    char tmp2[NUM_LEN * 2] = {0};
    strcat(tmp1, p1);
    strcat(tmp1, p2);
    strcat(tmp2, p2);
    strcat(tmp2, p1);
    return strcmp(tmp2, tmp1);
}

char * largestNumber(int* nums, int numsSize)
{
    int **sNum = PreHanlde(nums, numsSize);
    char *ret = (char *)malloc(MAX_NUM);
    memset(ret, 0x0, MAX_NUM);
    printf("Try to qsort\n");
    qsort(sNum, numsSize, sizeof(char *), Cmp);
    for (int i = 0; i < numsSize; i++) {
        printf("%s\n", sNum[i]);
        strcat(ret, sNum[i]);
    }
    AfterHandle(sNum, nums, numsSize);
    /* ¥h°£³Ì¥ª£ªº0 */
    int len = strlen(ret);
    bool bFirstZero = true;
    int start = 0;
    while (bFirstZero && start + 1 < len) {
        if (ret[start] == '0') {
            start++;
        } else {
            bFirstZero = false;
        }
    }
    if (start == 0) {
        return ret;
    } else {
        char *newRet = (char *)malloc(len - start + 1);
        memcpy(newRet, ret + start, len - start + 1);
        free(ret);
        return newRet;
    }
}

int main()
{
    int a[] = {0,0};
    int aSize = sizeof(a) / sizeof(int);
    int k = 3;
    int retSize;
    char *ret = largestNumber(a, aSize);
    printf("%s\n", ret);
    free(ret);
    return 0;
}