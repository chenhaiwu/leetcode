#define RUN_TIMES 80000

int Swap(int* array, int arraySize)
{
    int result = 0;
    int tmp;
    int start = 0;

    for (int i = 0; i < arraySize; i++) {
        if (array[i] != array[array[i]]) {
            tmp = array[i];
            array[i] = array[tmp];
            array[tmp] = tmp;
            result++;
            i = start;
            if (result > RUN_TIMES) {
                return 0;
            }
        }
        start = i;
    }
    return result;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int* Test(int* nums, int numsSize, int* returnSize){
    int *result = NULL;

    result = malloc(numsSize * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < numsSize; i++) {
        result[i] = 0;
    }

    *returnSize = numsSize;
    return result;
}

int main()
{
    int nums[] = {1,2,1};
    int numsSize = sizeof(nums) / sizeof(int);
    int *result;
    int returnSize;

    result = Test(nums, numsSize, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    free(result);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAP_ROW 6
#define MAP_COL 2
int g_map[MAP_ROW][MAP_COL] = {{8,0}, {4,4}, {8,1}, {5,0}, {6,1}, {5,2}};

void PrintMatrix(int** grid, int gridSize, int* gridColSize)
{
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridColSize[row]; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

int** Test(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes)
{
    int retSize = gridSize;
    int retColSize = gridColSize[0];
    int **result = NULL;

    result = malloc(retSize * sizeof(int *));
    *returnColumnSizes = malloc(retSize * sizeof(int));

    /* todo */

    *returnSize = retSize;
    for (int i = 0; i < retSize; i++) {
        (*returnColumnSizes)[i] = gridColSize[i];
        result[i] = malloc(gridColSize[i] * sizeof(int));
        for (int num = 0; num < gridColSize[i]; num++) {
            // result[i][num] = num;
        }
    }
    return result;
}

int main()
{
    int gridSize = MAP_ROW;
    int **grid = NULL;
    int *gridColSize = NULL;
    int **result = NULL;
    int returnSize;
    int *returnColumnSizes = NULL;

    /* 申请测试用例输入参数中需要的内存并根据用例输入初始化 */
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
    /* 将测试用例的输入参数转换成用例输入的二维数组 */
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            grid[i][j] = g_map[i][j];
        }
    }

    /* 运行测试用例给出的接口函数 */
    result = Test(grid, gridSize, gridColSize, &returnSize, &returnColumnSizes);

    /* 释放测试函数中申请的内存 */
    for (int row = 0; row < returnSize; row++) {
        for (int col = 0; col < returnColumnSizes[row]; col++) {
            printf("%d ", result[row][col]);
        }
        printf("\n");
        free(result[row]);
    }
    free(returnColumnSizes);
    free(result);

    /* 释放测试用例输入参数中申请的内存 */
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(gridColSize);
    free(grid);
}

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

int Cmp(const void *a, const void *b)
{
    // int *ta = *(int **)a;
    // int *tb = *(int **)b;
    int ta = *(int *)a;
    int tb = *(int *)b;

    return ta > tb;      /* 升序排序 */
    // return ta < tb;   /* 降序排序 */
}