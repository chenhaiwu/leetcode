#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int FindRow(int** matrix, int matrixSize, int* matrixColSize, int target, int *value)
{
    int top = 0;
    int bottom = matrixSize - 1;
    int mid;
    while (top <= bottom) {
        mid = top + (bottom - top) / 2;
        if (matrix[mid][0] == target) {
            *value = target;
            // printf("row=%d, value=%d\n", mid, matrix[mid][0]);
            return mid;
        } else if (matrix[mid][0] > target) {
            bottom = mid - 1;
        } else {
            top = mid + 1;
        }
    }
    top = top > 0 ? top - 1 : 0;
    *value = matrix[top][0];
    // printf("row=%d, value=%d\n", top, matrix[top][0]);
    return top;
}

bool FindCol(int** matrix, int matrixSize, int* matrixColSize, int target, int row)
{
    int top = 0;
    int bottom = matrixColSize[0] - 1;
    int mid;
    while (top <= bottom) {
        mid = top + (bottom - top) / 2;
        if (matrix[row][mid] == target) {
            return true;
        } else if (matrix[row][mid] > target) {
            bottom = mid - 1;
        } else {
            top = mid + 1;
        }
    }
    
    return false;
}

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
    if (matrixSize == 0 || matrixColSize == NULL || matrixColSize[0] == 0) {
        return false;
    }
    int v;
    int row = FindRow(matrix, matrixSize, matrixColSize, target, &v);
    if (v == target) {
        return true;
    }
    return FindCol(matrix, matrixSize, matrixColSize, target, row);
}