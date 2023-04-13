/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

// #include "securec.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 1; i <= numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

bool TestInline(int x1, int y1, int x2, int y2, int x3, int y3)
{
    long long lx1 = (long long)x1;
    long long ly1 = (long long)y1;
    long long lx2 = (long long)x2;
    long long ly2 = (long long)y2;
    long long lx3 = (long long)x3;
    long long ly3 = (long long)y3;
    return ((ly1 - ly2) * (lx3 - lx2) == (lx1 - lx2) * (ly3 - ly2));
}

int Baoli(int** p, int n)
{
    int ans = INT_MIN;
    bool bAllthesame = true;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i][0] == p[j][0] && p[i][1] == p[j][1]) {
                continue;
            }
            bAllthesame = false;
            int tmpcnt = 0;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                if (TestInline(p[i][0], p[i][1], p[j][0], p[j][1], p[k][0], p[k][1])) {
                    tmpcnt++;
                }
            }
            ans = ans > tmpcnt ? ans : tmpcnt;
        }
    }
    if (bAllthesame) {
        ans = n;
    } else {
        return ans + 2;
    }
    return ans;
}

int maxPoints(int** points, int pointsSize, int* pointsColSize)
{
    int ans;
    if (pointsSize < 3) return pointsSize;
    ans = Baoli(points, pointsSize);
    return ans;
}

// #define MAP_ROW 6
// #define MAP_COL 2
// int g_map[MAP_ROW][MAP_COL] = {{1,1},{3,2},{5,3},{4,1},{2,3},{1,3}};
// int g_col[MAP_ROW] = {2,2,2,2,2,2};

// int main()
// {
//     int gridSize = MAP_ROW;
//     int **grid = NULL;
//     int *gridColSize = NULL;

//     /* ¥Ó???¥Î¨Ò™]¤J‰ë?¤¤»Ý­nªº?¦s¦}®ÚÕu¥Î¨Ò™]¤Jªì©l¤Æ */
//     grid = malloc(gridSize * sizeof(int *));
//     if (grid == NULL) {
//         return -1;
//     }
//     gridColSize = malloc(gridSize * sizeof(int));
//     if (gridColSize == NULL) {
//         return -1;
//     }
//     for (int i = 0; i < gridSize; i++) {
//         gridColSize[i] = g_col[i];
//         grid[i] = malloc(gridColSize[i] * sizeof(int));
//         if (grid[i] == NULL) {
//             return -1;
//         }
//     }
//     for (int i = 0; i < gridSize; i++) {
//         for (int j = 0; j < gridColSize[i]; j++) {
//             grid[i][j] = g_map[i][j];
//         }
//     }

//     int result = maxPoints(grid, gridSize, gridColSize);

//     /* ?©ñ??¥Î¨Ò™]¤J‰ë?¤¤¥Ó?ªº?¦s */
//     for (int i = 0; i < gridSize; i++) {
//         free(grid[i]);
//     }
//     free(gridColSize);
//     free(grid);
// }