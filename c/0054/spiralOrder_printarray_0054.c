#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAP_ROW 2
#define MAP_COL 1
int g_map[MAP_ROW][MAP_COL] = {{1,2}};

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

void PrintOneCircle(int** matrix, int *ret, int left, int top, int right, int bottom, int *idx)
{
    int start = *idx;
    // ��ӡ��һ��
    for (int i = left; i <= right; i++) {
        ret[start++] = matrix[top][i];
    }
    // ��ӡ������
    for (int i = top + 1; i <= bottom; i++) {
        ret[start++] = matrix[i][right];
    }
    // ��ӡ�����
    for (int i = right - 1; i >= left; i--) {
        ret[start++] = matrix[bottom][i];
    }
    // ��ӡ������
    for (int i = bottom - 1; i >= top + 1; i--) {
        ret[start++] = matrix[i][left];
    }
    *idx = start;
    PrintArray(ret, start);
}

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    if (matrixSize == 0 || matrixSize == NULL || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int m = matrixSize;
    int n = matrixColSize[0];
    int *ret = (int *)malloc(sizeof(int) * m * n);
    // [left, right] = [0, m / 2], {top, bottom}=[0, n / 2]
    int circleIdx = 0;
    int idx = 0, lastidx = 0;
    for (; circleIdx < m / 2 && circleIdx < n / 2; circleIdx++) {
        PrintOneCircle(matrix, ret, circleIdx, circleIdx, n - 1 - circleIdx, m - 1 - circleIdx, &idx);
        if (lastidx == idx) {
            break;
        }
        lastidx = idx;
    }
    if (circleIdx < n / 2 && m % 2 == 1) {
        // ��ӡһ��
        for (int i = circleIdx; i <= n - 1 - circleIdx; i++) {
            ret[idx++] = matrix[circleIdx][i];
        }
    }
    PrintArray(ret, idx);
    if (circleIdx < m / 2 && n % 2 == 1) {
        // ��ӡһ��
        for (int i = circleIdx; i <= m - 1 - circleIdx; i++) {
            ret[idx++] = matrix[i][circleIdx];
        }
    }
    PrintArray(ret, idx);
    if (m == n && m % 2 == 1) {
        ret[idx++] = matrix[circleIdx][circleIdx];
    }
    PrintArray(ret, idx);
    
    PrintArray(ret, m * n);
    *returnSize = idx;
    return ret;
}

int main()
{
    int gridSize = MAP_ROW;
    int **grid = NULL;
    int *gridColSize = NULL;
    int returnSize;

    /* ����������������������Ҫ���ڴ沢�������������ʼ�� */
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
    /* �������������������ת������������Ķ�ά���� */
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            grid[i][j] = g_map[i][j];
        }
    }

    /* ���в������������Ľӿں��� */
    int *result = spiralOrder(grid, gridSize, gridColSize, &returnSize);

    /* �ͷŲ��Ժ�����������ڴ� */
    free(result);

    /* �ͷŲ����������������������ڴ� */
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(gridColSize);
    free(grid);
}