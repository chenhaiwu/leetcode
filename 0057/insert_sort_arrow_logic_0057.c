#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

int InsertNewInterver(int **ret, int row, int *colSize, int *addInter)
{
    ret[row] = (int *)malloc(sizeof(int) * 2);
    ret[row][0] = addInter[0];
    ret[row][1] = addInter[1];
    colSize[row] = 2;
    return row + 1;
}

int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes)
{
    int **ret = (int **)malloc(sizeof(int *) * (intervalsSize + 1));
    *returnColumnSizes = (int *)malloc(sizeof(int) * (intervalsSize + 1));
    int retSize = 0;
    bool hasInsert = false;
    for (int i = 0; i < intervalsSize; i++) {
        int *curInter = intervals[i];
        if (hasInsert || curInter[1] < newInterval[0]) {
            retSize = InsertNewInterver(ret, retSize, *returnColumnSizes, curInter);
            continue;
        }
        if (curInter[0] > newInterval[1]) {
            retSize = InsertNewInterver(ret, retSize, *returnColumnSizes, newInterval);
            hasInsert = true;

            retSize = InsertNewInterver(ret, retSize, *returnColumnSizes, curInter);
            continue;
        }
        newInterval[0] = newInterval[0] < curInter[0] ? newInterval[0] : curInter[0];
        newInterval[1] = newInterval[1] > curInter[1] ? newInterval[1] : curInter[1];
    }  
    if (!hasInsert) {
        retSize = InsertNewInterver(ret, retSize, *returnColumnSizes, newInterval);
    }
    *returnSize = retSize;
    return ret;
}