#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/*  算法1：因为可以任意排序，所以只要从i->j中，如果长度中奇数的个数为M，若M为奇数，则奇数的个数 (M-1)/2<=k，
    如果是偶数，则(M)/2 <= k 就符合条件。直接在上面调试，发现超时，不维护从i->j的奇偶情况。
    空间复杂度：O(1)；时间复杂度：O(n(item) * len(start-end) * 26)，极限情况下：O(N * N * 26)
    算法2：想办法维护从i->j的奇数个数情况，创建一个二维数据[i][26], i<=100000，维护从0->i位置的字符个数
    空间复杂度：O(N * 26)；时间复杂度：O(n(item) * 26)，极限情况下：O(N * 26)
    算法3：还可以再优化，不要存26个字母的个数，可以存一个整数，然后使用BIT位来表示。当从前往后移动时，对对应字母的BIT操作
    如果原来为1，则变0，如果原来为0，则变1. 这样得到一个hash[N]的值，表示字母情况。
    要求i->j的情况，则可以使用j+1 - i 从1开始放，0全放0. 利用奇数-奇数为0，偶数-奇数=奇数，对应 过来就是：
    hash[j + 1] = 1, hash[i] = 0，则保持这个1，如果性质再同，则变为偶数。
*/

#define MAX_CHAR 26
#define MAX_NUM 100002
int g_hash2[MAX_NUM];
/* // 算法2
int g_hash[MAX_NUM][MAX_CHAR];
int GetJishuNum1(char * s, int* queriesItem)
{
    int ret = 0;
    int hash[MAX_CHAR] = {0};
    for (int i = queriesItem[0]; i <= queriesItem[1]; i++) {
        hash[s[i] - 'a']++;
    }
    for (int i = 0; i < MAX_CHAR; i++) {
        if (hash[i] % 2 == 1) {
            ret++;
        }
    }
    return ret;
}

void PrintHash(char *s)
{
    printf("%s\n", s);
    for (int i = 0; i <= strlen(s); i++) {
        for(int j = 0; j < MAX_CHAR; j++) {
            printf("%d ", g_hash[i][j]);
        }
        printf("\n");
    }
}

int GetJishuNum2(char * s, int* queriesItem)
{
    int ret = 0;
    int hash[MAX_CHAR] = {0};
    int start = queriesItem[0]; 
    int end = queriesItem[1] + 1;

    for (int i = 0; i < MAX_CHAR; i++) {
        if ((g_hash[end][i] - g_hash[start][i]) % 2 == 1) {
            ret++;
        }
    }
    return ret;
}

void PreHandle2(char * s)
{
    int len = strlen(s);
    memset(g_hash[0], 0x0, sizeof(int) * MAX_CHAR);
    for (int i = 1; i <= len; i++) {
        memcpy(g_hash[i], g_hash[i - 1], sizeof(int) * MAX_CHAR);
        g_hash[i][s[i - 1] - 'a']++;
    }
    //PrintHash(s);
}
*/

int BitSet(int mask, int bit)
{
    return mask | (1 << bit);
}

int BitClr(int mask, int bit)
{
    return mask & (~(1 << bit));
}

bool BitTest(int mask, int bit)
{
    if ((mask & (1 << bit)) >> bit == 1) {
        return true;
    } else {
        return false;
    }
}

int GetJishuNum(char * s, int* queriesItem)
{
    int ret = 0;
    int hash[MAX_CHAR] = {0};
    int start = queriesItem[0]; 
    int end = queriesItem[1] + 1;

    for (int i = 0; i < MAX_CHAR; i++) {
        if (BitTest(g_hash2[end], i) != BitTest(g_hash2[start], i)) {
            ret++;
        }
    }
    return ret;
}

void PreHandle(char * s)
{
    int len = strlen(s);
    g_hash2[0] = 0;
    int idx;
    for (int i = 1; i <= len; i++) {
        g_hash2[i] = g_hash2[i - 1];
        idx = s[i - 1] - 'a';
        if (BitTest(g_hash2[i], idx)) {
            g_hash2[i] = BitClr(g_hash2[i], idx);
        } else {
            g_hash2[i] = BitSet(g_hash2[i], idx);
        }
    }
}

bool CheckValue(char * s, int* queriesItem)
{
    int m = GetJishuNum(s, queriesItem);
    int k = queriesItem[2];
    if (m % 2 == 1) {
        m = m - 1;
    }
    if (k >= m / 2) {
        return true;
    } else {
        return false;
    }
}

bool* canMakePaliQueries(char * s, int** queries, int queriesSize, int* queriesColSize, int* returnSize)
{
    bool *ret = (bool *)malloc(queriesSize * sizeof(bool));
    *returnSize = queriesSize;
    PreHandle(s);
    for (int i = 0; i < queriesSize; i++) {
        ret[i] = CheckValue(s, queries[i]);
    }
    return ret;
}

void main()
{
    printf("ret = %d\n", ret);
}