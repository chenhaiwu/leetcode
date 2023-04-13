#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define DEGUG_CHW
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

void PrintMatrix(int** grid, int gridSize, int* gridColSize)
{
#ifdef DEGUG_CHW
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridColSize[row]; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
#endif
}

#define MAX_NUM 101
bool g_colCheck[MAX_NUM];

int GetLessDchars(char ** w, int wordNum)
{
    int ans = 0;
    int cnt = 0;
    memset(g_colCheck, 0x0, sizeof(g_colCheck));
    int len = strlen(w[0]);
    for (int i = 0; i < len; i++) {
        bool bDel = false;
        for (int j = 1; j < wordNum; j++) {
            if (!g_colCheck[j] && w[j][i] < w[j - 1][i]) {
                ans++;
                bDel = true;
                break;
            }
        }
        if (bDel) {
            continue;
        }
        for (int j = 1; j < wordNum; j++) {
            if (w[j - 1][i] < w[j][i]) {
                g_colCheck[j] = true;
                cnt++;
            }
        }
        if (cnt == wordNum - 1) {
            break;
        }
    }
    return ans;
}

int minDeletionSize(char ** A, int ASize)
{
    if (ASize == 1) {
        return 0;
    }
    int ret = GetLessDchars(A, ASize);
    return ret;
}

int main()
{
    char *s1 = "jwkwdc";
    char *s2 = "etukoz";
    char *s3 = "yfa";
    char *s[] = {s1, s2};
    int ret = minDeletionSize(s, sizeof(s) / sizeof(char *));
    return 0;
}