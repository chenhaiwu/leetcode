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

void CpyStringWithPattan(char *ret, char *spatten, int start, int num)
{
    int patLen = strlen(spatten);
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < patLen; j++) {
            ret[start + i * patLen + j] = spatten[j];
        }
    }
}

char * strWithout3a3b(int A, int B)
{
    char *ret = (char *)malloc(A + B + 1);
    ret[A + B] = '\0';
    int la = A;
    int lb = B;
    if (la == lb) {
        CpyStringWithPattan(ret, "ab", 0, la);
        return ret;
    }
    int pos = 0;
    while (la > 0 && lb > 0) {
        if (la > lb) {
            CpyStringWithPattan(ret, "aab", pos, 1);
            la -= 2;
            lb -= 1;
            pos += 3;
        } else if (la < lb) {
            CpyStringWithPattan(ret, "bba", pos, 1);
            la -= 1;
            lb -= 2;
            pos += 3;
        } else {
            if (A > B) {
                CpyStringWithPattan(ret, "ab", pos, la);
            } else {
                CpyStringWithPattan(ret, "ab", pos, la);
            }
            pos += 2 * la;
            la = 0;
            lb = 0;
        }
    }
    if (la > 0) {
        CpyStringWithPattan(ret, "a", pos, la);
    }
    if (lb > 0) {
        CpyStringWithPattan(ret, "b", pos, lb);
    }

    return ret;
}

int main()
{
    char *ret = strWithout3a3b(1, 3);
    printf("%s\n", ret);
    ret = strWithout3a3b(4, 1);
    printf("%s\n", ret);
    ret = strWithout3a3b(4, 4);
    printf("%s\n", ret);
    free(ret);
    return 0;
}