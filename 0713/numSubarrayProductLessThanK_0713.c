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
    printf("total cnt=%d\n", numsSize);
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

#define MAXNUM 1000
int g_hash[MAXNUM];
int g_value[MAXNUM];
int g_cnts[MAXNUM];
int g_totalcnt;

void PreHandle(int* nums, int numsSize)
{
    memset(g_hash, 0x0, sizeof(g_hash));
    for (int i = 0; i < numsSize; i++) {
        g_hash[nums[i]]++;
    }
    g_totalcnt = 0;
    for (int i = 0; i < MAXNUM; i++) {
        if (g_hash[i] != 0) {
            g_value[g_totalcnt] = i;
            g_cnts[g_totalcnt] = g_hash[i];
            g_totalcnt++;
        }
    }

    PrintArray(g_value, g_totalcnt);
    PrintArray(g_cnts, g_totalcnt);
}

int GetCurOnlyNum(int m, int n)
{
    int ret = 1;
    int chushu = 1;
    for (int i = 1; i <= m; i++) {
        ret *= (n - i + 1);
        chushu *= i;
    }
    return ret / chushu;
}

int GetTotalCnt(int start, int k)
{
    int ret = 0;
    if (start >= g_totalcnt || g_value[start] > k) {
        return 0;
    }
    /*
    ��Ե�ǰg_value[start]Ԫ�����������ѡһ��������value=g_cnt[start]��c(1, n)
    ���ѡ����������c(2, n)
    ���ѡ����������c(3, n)
    ...
    һֱ��������ѡ������Ԫ�أ���֤value ��m�η���С��k����������
    �����ӣ�����ֱ����������ֻѡ��ЩԪ�أ���������ô���ַ�����

    ����������Ҫ�������ѡ��ЩԪ�أ���Ԫ�ظ���Ϊ start+1, k��ֵ���䡣
    ���ѡ��һ����start+1, k / value 
    ...
    ���ѡ��m������start+1, k / value ��m�η� =0

    Ȼ������濴�������Щ�������ظ��ģ�ֻҪ������ü��ɡ�
    */
    int lastV = g_value[start];
    int curCnt = g_cnts[start];
    int v = lastV;
    int curSel = 0;
    int notSel = 0;
    /* Not select */
    notSel += GetTotalCnt(start + 1, k);
    /* Select */
    for (int i = 0; i < curCnt && v < k; i++) {
        curSel += GetCurOnlyNum(i + 1, curCnt);
        curSel += GetTotalCnt(start + 1, k / v);
        v *= lastV;
    }
    printf("curIdx=%d, k=%d, notSel=%d, sel=%d\n", start, k, notSel, curSel);
    return notSel + curSel;
}

int numSubarrayProductLessThanK1(int* nums, int numsSize, int k)
{
    if (numsSize <= 0) {
        return 0;
    }
    PreHandle(nums, numsSize);

    int ret;
    ret = GetTotalCnt(0, k);
    return ret;
}

int numSubarrayProductLessThanK2(int* nums, int numsSize, int k)
{
    if (numsSize <= 0) {
        return 0;
    }

    int cnt = 0;
    int sum = 1;

    for (int i = 0; i < numsSize; i++) {
        sum = nums[i];
        if (sum < k) {
            cnt++;
        }
        for (int j = i + 1; j < numsSize; j++) {
            sum *= nums[j];
            if (sum < k) {
                cnt++;
            } else {
                break;
            }
        }
    }
    return cnt;
}

int numSubarrayProductLessThanK(int* nums, int numsSize, int k)
{
    if (numsSize <= 0) {
        return 0;
    }
    int left = 0;
    int right = 0;
    int cnt = 0;
    int sum = 1;

    for (right = 0; right < numsSize; right++) {
        sum *= nums[right];
        while (left <= right && sum > k) {
            sum /= nums[left++];
        }
        cnt += (right - left + 1);
    }
    return cnt;
}

int main()
{
    int nums[] = {10,5,2,6};
    int k = 100;
    int ret = numSubarrayProductLessThanK(nums, sizeof(nums) / sizeof(int), k);
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return ret;
}
