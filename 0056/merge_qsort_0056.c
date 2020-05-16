#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

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

void PrintMatrix(int** grid, int gridSize, int* gridColSize)
{
#ifdef DEGUG_CHW
    for (int row = 0; row < gridSize; row++) {
        printf("[%d %d]\n", grid[row][0], grid[row][1]);
    }
#endif
}

#define MAX_NUM 100
int g_retSize;

int Cmp(void *a, void *b)
{
    int *ta = *(int **)a;
    int *tb = *(int **)b;
    if (ta[0] == tb[0]) {
        return ta[1] - tb[1];
    }
    return ta[0] - tb[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, 
    int* returnSize, int** returnColumnSizes)
{
    g_retSize = 0;
    int retSize = MAX_NUM;
    int retColSize = intervalsColSize[0];
    int **result = NULL;
    if (intervalsSize == 0 || *returnColumnSizes == NULL) {
        *returnSize = 0;
        return NULL;
    }

    result = malloc(retSize * sizeof(int *));
    *returnColumnSizes = malloc(retSize * sizeof(int));

    PrintMatrix(intervals, intervalsSize, intervalsColSize);
    qsort(intervals, intervalsSize, sizeof(int *), Cmp);
    PrintMatrix(intervals, intervalsSize, intervalsColSize);

    int left = intervals[0][0];
    int right = intervals[0][1];
    (*returnColumnSizes)[g_retSize] = 2;
    result[g_retSize] = malloc(2 * sizeof(int));
    result[g_retSize][0] = left;
    result[g_retSize][1] = right;
    g_retSize++;
    for (int i = 1; i < intervalsSize; i++) {
        int left_i = intervals[i][0];
        int right_i = intervals[i][1]; 
        // (*returnColumnSizes)[i] = 2;
        if (right_i <= right) {
            continue;
        } else if (left_i <= right && right_i > right) {
            result[g_retSize - 1][1] = right_i;
            right = right_i;
        } else {
            left = left_i;
            right = right_i;
            (*returnColumnSizes)[g_retSize] = 2;
            result[g_retSize] = malloc(2 * sizeof(int));
            result[g_retSize][0] = left;
            result[g_retSize][1] = right;
            g_retSize++;
        }
    }
    *returnSize = g_retSize;
    PrintMatrix(result, *returnSize, *returnColumnSizes);
    return result;
}

// #define MAP_ROW 4
// #define MAP_COL 2
// int g_map[MAP_ROW][MAP_COL] = {{1,3}, {8,10}, {2,6}, {15,18}};
#define MAP_ROW 2
#define MAP_COL 2
int g_map[MAP_ROW][MAP_COL] = {{1,3}, {3,10}};

int main()
{
    int gridSize = MAP_ROW;
    int **grid = NULL;
    int *gridColSize = NULL;
    int **result = NULL;
    int returnSize;
    int *returnColumnSizes = NULL;

    /* ¥Ó???¥Î¨Ò™]¤J‰ë?¤¤»Ý­nªº?¦s¦}®ÚÕu¥Î¨Ò™]¤Jªì©l¤Æ */
    grid = malloc(gridSize * sizeof(int *));
    if (grid == NULL) {
        return -1;
    }
    gridColSize = malloc(gridSize * sizeof(int));
    if (gridColSize == NULL) {
        return -1;
    }
    for (int i = 0; i < gridSize; i++) {
        gridColSize[i] = MAP_COL;
        grid[i] = malloc(MAP_COL * sizeof(int));
        if (grid[i] == NULL) {
            return -1;
        }
    }
    /* ???¥Î¨Òªº™]¤J‰ë???¦¨¥Î¨Ò™]¤Jªº¤G??? */
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            grid[i][j] = g_map[i][j];
        }
    }

    /* `¦æ??¥Î¨Ò?¥Xªº±µ¤f¨ç? */
    result = merge(grid, gridSize, gridColSize, &returnSize, &returnColumnSizes);

    /* ?©ñ??¨ç?¤¤¥Ó?ªº?¦s */
    for (int row = 0; row < returnSize; row++) {
        printf("[%d %d]\n", result[row][0], result[row][1]);
        free(result[row]);
    }
    free(returnColumnSizes);
    free(result);

    /* ?©ñ??¥Î¨Ò™]¤J‰ë?¤¤¥Ó?ªº?¦s */
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(gridColSize);
    free(grid);
    return 0;
}
