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

#define MAX_LEN 50002
#define MAX_WORDS_LEN 5001
#define MAX_TONG 26
int g_dataLen[MAX_TONG];
int g_data[MAX_TONG][MAX_LEN];

int numMatchingSubseq(char * S, char ** words, int wordsSize)
{
    if (wordsSize == 0) {
        return 0;
    }
    memset(g_dataLen, 0x0, sizeof(int) * MAX_TONG);
    memset(g_data, -1, sizeof(int) * MAX_TONG * MAX_LEN);
    int len = strlen(S);
    for (int i = 0; i < len; i++) {
        int idx = S[i] - 'a';
        for (int j = g_dataLen[idx]; j <= i; j++) {
            /* 这样做完以后，所以的26 * len，全部赋值 */
            g_data[idx][j] = i;
        }
        /* g_dataLen 表示上一次出现idx这个字符的起始位置 */
        g_dataLen[idx] = i + 1;
    }
    int ans = 0;
    for (int i = 0; i < wordsSize; i++) {
        int wordlen = strlen(words[i]);
        int start = 0;
        for (int j = 0; j < wordlen; j++) {
            int idx = words[i][j] - 'a';
            start = g_data[idx][start];
            if (start == -1) {
                break;
            }
            if (j == wordlen - 1) {
                ans++;
                break;
            }
            start++;
        }
    }
    return ans;
}

int main()
{
    char *s = "abcde";
    char *s1 = "a";
    char *s2 = "bb";
    char *s3 = "acd";
    char *s4 = "ace";
    char *words[4];
    words[0] = s1;
    words[1] = s2;
    words[2] = s3;
    words[3] = s4;
    int retsize = numMatchingSubseq(s, words, 4);
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
