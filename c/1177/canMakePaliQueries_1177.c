#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/*  �㷨1����Ϊ����������������ֻҪ��i->j�У���������������ĸ���ΪM����MΪ�������������ĸ��� (M-1)/2<=k��
    �����ż������(M)/2 <= k �ͷ���������ֱ����������ԣ����ֳ�ʱ����ά����i->j����ż�����
    �ռ临�Ӷȣ�O(1)��ʱ�临�Ӷȣ�O(n(item) * len(start-end) * 26)����������£�O(N * N * 26)
    �㷨2����취ά����i->j�������������������һ����ά����[i][26], i<=100000��ά����0->iλ�õ��ַ�����
    �ռ临�Ӷȣ�O(N * 26)��ʱ�临�Ӷȣ�O(n(item) * 26)����������£�O(N * 26)
    �㷨3�����������Ż�����Ҫ��26����ĸ�ĸ��������Դ�һ��������Ȼ��ʹ��BITλ����ʾ������ǰ�����ƶ�ʱ���Զ�Ӧ��ĸ��BIT����
    ���ԭ��Ϊ1�����0�����ԭ��Ϊ0�����1. �����õ�һ��hash[N]��ֵ����ʾ��ĸ�����
    Ҫ��i->j������������ʹ��j+1 - i ��1��ʼ�ţ�0ȫ��0. ��������-����Ϊ0��ż��-����=��������Ӧ �������ǣ�
    hash[j + 1] = 1, hash[i] = 0���򱣳����1�����������ͬ�����Ϊż����
*/

#define MAX_CHAR 26
#define MAX_NUM 100002
int g_hash2[MAX_NUM];
/* // �㷨2
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