#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

/* 
 * Ö»Òª»¹ÓÐÄÜÁ¿£¬¾ÍÒ»Ö±?ÃÁîÅÆÕýÃæ³¯ÉÏ£¬Ö±µ½Ã»ÓÐÄÜÁ¿µÄÊ±ºò£¬ÈÃÒ»¸öÁîÅÆ·´Ãæ³¯ÉÏ´Ó¶ø»ñµÃÄÜÁ¿¼ÌÐøÖ®Ç°µÄ²Ù×÷¡?
Ò»¶¨ÒªÐ¡ÐÄ´¦Àí±ß½çÌõ¼þ£¬²»?»ºÜÓÐ¿ÉÄÜ»áÐ´³ö´íÎóµÄ´ð°¸¡£ÕâÀïÒªÀÎÀÎ¼Ç×¡£¬ÔÚÓÐÄÜÁ¿Ê±ºò£¬Ö»ÄÜÈÃÁîÅÆÕýÃæ³¯ÉÏ£¬Ö±µ½ÄÜÁ¿²»¹»ÓÃÁË²ÅÄÜÈÃÁîÅÆ·´Ãæ³¯É?
 */

typedef struct _mynode {
    int bV;
    int bIdx;
    int aV;
} MyNode;

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
        printf("(%d,%d)", nums[i].bV, nums[i].bIdx);
    }
    printf("\n");
#endif
}

#define MAX_NUM 10001
MyNode g_mynode[MAX_NUM];
int g_flagA[MAX_NUM];

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

int Cmp2(const void *a, const void *b)
{
    MyNode *ta = (MyNode *)a;
    MyNode *tb = (MyNode *)b;
    if (ta->bV == tb->bV) {
        return ta->bIdx - tb->bIdx;
    }
    return ta->bV - tb->bV;
}

int Cmp3(const void *a, const void *b)
{
    MyNode *ta = (MyNode *)a;
    MyNode *tb = (MyNode *)b;
    return ta->bIdx - tb->bIdx;
}

void PreHandle(int* A, int ASize, int* B, int BSize)
{
    for (int i = 0; i < BSize; i++) {
        g_mynode[i].bIdx = i;
        g_mynode[i].bV = B[i];
    }
    qsort(A, ASize, sizeof(int), Cmp);
    PrintArray(A, ASize);
    qsort(g_mynode, BSize, sizeof(MyNode), Cmp2);
    PrintArray2(g_mynode, BSize);
    memset(g_flagA, 0x0, sizeof(int) * ASize);
}

int FindBestValFromA(int* A, int ASize, int startA, int v)
{
    int ans = -1;
    for (int i = startA; i < ASize; i++) {
        if (A[i] > v) {
            ans = i;
            break;
        }
    }
    return ans;
}

int CurrentUnselV(int* A, int ASize, int start)
{
    int ans = start;
    for (int i = start; i < ASize; i++) {
        if (g_flagA[i] == 0) {
            ans = i;
            g_flagA[i] = 1;
            break;
        }
    }
    return ans;
}

void SetAllSmallVal(int* A, int ASize, int idx)
{
    /* g_mynodeÖÐ´Óidx¿ªÊ¼£¬A¾ÍÃ»ÓÐ±ÈËü´óµÄ£¬´ÓµÚ0¸öÔªËØ¿ªÊ¼ÕÒ£¬Ö»Òªflag²»Îª£¬Ôò¾ÍÌîÉÏ?? */
    int startA = 0;
    for (int i = idx; i < ASize; i++) {
        startA = CurrentUnselV(A, ASize, startA);
        g_mynode[i].aV = A[startA];
    }
}

int* advantageCount(int* A, int ASize, int* B, int BSize, int* returnSize)
{
    PreHandle(A, ASize, B, BSize);
    int startA = 0;
    int bigAIdx;
    for (int i = 0; i < BSize; i++) {
        bigAIdx = FindBestValFromA(A, ASize, startA, g_mynode[i].bV);
        if (bigAIdx == -1) {
            SetAllSmallVal(A, ASize, i);
            break;
        } else {
            g_mynode[i].aV = A[bigAIdx];
            g_flagA[bigAIdx] = 1;
            startA = bigAIdx + 1;
        }
    }
    qsort(g_mynode, BSize, sizeof(MyNode), Cmp3);
    PrintArray2(g_mynode, BSize);
    int *ret = (int *)malloc(sizeof(int) * ASize);
    for (int i = 0; i < ASize; i++) {
        ret[i] = g_mynode[i].aV;
    }
    *returnSize = ASize;
    PrintArray(ret, ASize);
    return ret;
}

int main()
{
    int a[] = {2,7,11,15};
    int b[] = {1,10,4,11};
    int retSize;
    int *ret = advantageCount(a, sizeof(a)/sizeof(int), b, sizeof(b)/sizeof(int), &retSize);
    printf("ret=%d\n", ret);
    return 0;
}