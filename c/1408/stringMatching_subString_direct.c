#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 101
int g_flag[MAX_N];

// #define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}
// s1 sub
bool IsSubString(char *s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 > len2) return false;
    for (int i = 0; i + len1 <= len2; i++) {
        if (strncmp(s1, &s2[i], len1) == 0) {
            return true;
        }
    }
    return false;
}

char ** stringMatching(char ** words, int wordsSize, int* returnSize)
{
    memset(g_flag, 0x0, sizeof(g_flag));
    for (int i = 0; i < wordsSize; i++) {
        char *s1 = words[i];
        for (int j = 0; j < wordsSize; j++) {
            if (i == j) continue;
            char *s2 = words[j];
            if (IsSubString(s1, s2)) {
                g_flag[i] = 1;
                break;
            }
        }
    }
    PrintArray(g_flag, wordsSize);
    int ans = 0;
    char **ret = (char **)malloc(wordsSize * sizeof(char *));
    for (int i = 0; i < wordsSize; i++) {
        if (g_flag[i] == 0) continue;
        int len = strlen(words[i]);
        ret[ans] = (char *)malloc(len + 1);
        memset(ret[ans], 0x0, len + 1);
        strcpy(ret[ans], words[i]);
        ans++;
    }
    *returnSize = ans;
    return ret;
}
