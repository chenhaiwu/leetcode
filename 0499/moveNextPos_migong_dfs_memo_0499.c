/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <limits.h>
// #include <stdbool.h>
// #include <math.h>

// // #include "securec.h"

// #define MAX(a, b) (a) > (b) ? (a) : (b)
// #define MIN(a, b) (a) < (b) ? (a) : (b)

// #define DEGUG_CHW 1
// void PrintArray(int *nums, int numsSize)
// {
// #ifdef DEGUG_CHW
//     for (int i = 1; i <= numsSize; i++) {
//         printf("%d ", nums[i]);
//     }
//     printf("\n");
// #endif
// }

// #define MAX_N 31
// int g_ret;
// int g_row;
// int g_cols[MAX_N];
// int g_dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
// int g_visit[MAX_N][MAX_N];
// char g_path[MAX_N];
// int g_startx;
// int g_starty;
// int g_holex;
// int g_holey;
// int **g_maze;
// #define MAX_STEPS 30000

// void InitV(int** maze, int mazeSize, int* mazeColSize, int* ball, int ballSize, int* hole, int holeSize)
// {
//     g_ret = INT_MAX;
//     g_row = mazeSize;
//     for (int i = 0; i < mazeSize; i++) {
//         g_cols[i] = mazeColSize[i];
//     }
//     g_maze = maze;
//     g_startx = ball[0];
//     g_starty = ball[1];
//     g_holex = hole[0];
//     g_holey = hole[1];
//     memset(g_visit, 0x0, sizeof(g_visit));
//     memset(g_path, 0x0, sizeof(g_path));
// }

// int CheckOneLine(int row, int col, int dir, int *newr, int *newc, int *findhole)
// {
//     int newrow = row;
//     int newcol = col;
//     int ans = 0;
//     for (;;) {
//         int nx = newrow + g_dirs[dir][0];
//         int ny = newcol + g_dirs[dir][1];
//         if (nx < 0) {
//             *newr = 0;
//             *newc = col;
//             ans = row;
//             *findhole = false;
//             break;
//         }
//         if (nx == g_row) {
//             *newr = g_row - 1;
//             *newc = col;
//             ans = *newr - row;
//             *findhole = false;
//             break;
//         }
//         if (ny < 0) {
//             *newr = row;
//             *newc = 0;
//             ans = col;
//             *findhole = false;
//             break;
//         }
//         if (ny == g_cols[row]) {
//             *newr = row;
//             *newc = g_cols[row] - 1;
//             ans = *newc - col;
//             *findhole = false;
//             break;
//         }
//         if (nx == g_holex && ny == g_holey) {
//             *findhole = true;
//             if (nx == row) {
//                 ans = ny >= col ? ny - col : col - ny;
//             } else {
//                 ans = nx >= row ? nx - row : row - nx;
//             }
//             break;
//         }
//         if (g_maze[nx][ny] == 1) {
//             *findhole = false;
//             if (nx == row) {
//                 *newr = nx;
//                 if (ny > col) {
//                     *newc = ny - 1;
//                     ans = ny - *newc;
//                 } else {
//                     *newc = ny + 1;
//                     ans = col - *newc;
//                 }
//             } else {
//                 *newc = ny;
//                 if (nx > row) {
//                     *newr = nx - 1;
//                     ans = nx - *newr;
//                 } else {
//                     *newr = nx + 1;
//                     ans = row - *newr;
//                 }
//             }
//             break;
//         }
//         newrow = nx;
//         newcol = ny;
//     }
//     return ans;
// }

// bool IsExitMatrix(int m, int n, int i, int j)
// {
//     bool ans = false;
//     if (i < 0 || i == m || j < 0 || j == n) {
//         ans = true;
//     }
//     return ans;
// }

// void Step(int r, int c, int steps)
// {
//     if (steps > g_ret) {
//         return;
//     }
//     if (r == g_holex && c == g_holey) {
//         printf("finish value, steps=%d\n", steps);
//         if (g_ret > steps)
//             g_ret = steps;
//         return;
//     }

//     int ans = INT_MAX;
//     for (int k = 0; k < 4; k++) {
//         int new1x = g_dirs[k][0];
//         int new1y = g_dirs[k][1];
//         if (!IsExitMatrix(g_row, g_cols[r], new1x, new1y) && g_maze[new1x][new1y] == 1) continue;
//         int newr;
//         int newc;
//         bool bFind = false;
//         int jumpsteps = CheckOneLine(r, c, k, &newr, &newc, &bFind);
//         if (jumpsteps == 0) continue;
//         if (g_visit[newr][newc] == 1) continue;

//         g_visit[newr][newc] = 1;
//         Step(newr, newc, steps + jumpsteps);

//         // ans = MIN(ans, curTime);
//     }
//     return;
// }

// void Dfs(int** maze, int mazeSize, int* mazeColSize, int* ball, int ballSize, int* hole, int holeSize)
// {
//     InitV(maze, mazeSize, mazeColSize, ball, ballSize, hole, holeSize);
//     g_visit[g_startx][g_starty] = 1;
//     Step(g_startx, g_starty, 0);
//     return;
// }

// char * findShortestWay(int** maze, int mazeSize, int* mazeColSize, int* ball, int ballSize, int* hole, int holeSize)
// {
//     char *ans;
//     Dfs(maze, mazeSize, mazeColSize, ball, ballSize, hole, holeSize);
    
//     // handle result
//     return ans;
// }


// #define MAP_ROW 5
// #define MAP_COL 5
// int g_map[MAP_ROW][MAP_COL] = {{0,0,0,0,0},{1,1,0,0,1},{0,0,0,0,0},{0,1,0,0,1},{0,1,0,0,0}};
// int g_col[MAP_ROW] = {5,5,5,5,5};


/**/
#define MAXSIZE 900
int holeX;
int holeY;
char bestWay[MAXSIZE]; 
int bestStepCnt;
char curWay[MAXSIZE];
const char action[4] = { 'd', 'l', 'r', 'u' };

void moveNextPos(int** maze, int mazeSize, int* mazeColSize, int curX, int curY, int curStepCnt, int index, char lastMove) {
	if (curStepCnt > bestStepCnt) {
		return;
	} else if (curStepCnt == bestStepCnt) {
		if ((curX == holeX && curY == holeY) && (strcmp(curWay, bestWay) < 0)) {
			memset(bestWay, 0, sizeof(char) * MAXSIZE);
			strcpy(bestWay, curWay);
		}
		return;
	} 
	
	if (curX == holeX && curY == holeY) {
		memset(bestWay, 0, sizeof(char) * MAXSIZE);
		strcpy(bestWay, curWay);
		bestStepCnt = curStepCnt;
		return;
	}

	maze[curX][curY] = 2;
	for (int k = 0; k < 4; k++) {
		if (lastMove != action[3 - k]) {
			int stepToMove = 0;
			int XToMove = 0;
			int YToMove = 0;
			if (action[k] == 'd') {
				for (int i = 1; i < mazeSize - curX; i++) {
					if (maze[curX + i][curY] == 1) {
						stepToMove = i - 1;
						break;
					}
					if (curX + i == holeX && curY == holeY) {
						stepToMove = i;
						break;
					}
					stepToMove = i;
				}
				XToMove += stepToMove;
			} else if (action[k] == 'l') {
				for (int i = 1; i <= curY; i++) {
					if (maze[curX][curY - i] == 1) {
						stepToMove = i - 1;
						break;
					}
					if (curX == holeX && curY - i == holeY) {
						stepToMove = i;
						break;
					}
					stepToMove = i;
				}
				YToMove -= stepToMove;
			} else if (action[k] == 'r') {
				for (int i = 1; i < mazeColSize[curX] - curY; i++) {
					if (maze[curX][curY + i] == 1) {
						stepToMove = i - 1;
						break;
					}
					if (curX == holeX && curY + i == holeY) {
						stepToMove = i;
						break;
					}
					stepToMove = i;
				}
				YToMove += stepToMove;
			} else if (action[k] == 'u') {
				for (int i = 1; i <= curX; i++) {
					if (maze[curX - i][curY] == 1) {
						stepToMove = i - 1;
						break;
					}
					if (curX - i == holeX && curY == holeY) {
						stepToMove = i;
						break;
					}
					stepToMove = i;
				}
				XToMove -= stepToMove;
			}

			if (stepToMove == 0 || maze[curX + XToMove][curY + YToMove] == 2) {
				continue;
			}

			curWay[index] = action[k];
			moveNextPos(maze, mazeSize, mazeColSize, curX + XToMove, curY + YToMove, curStepCnt + stepToMove, index + 1, action[k]);
			curWay[index] = '\0';
		}
	}
	maze[curX][curY] = 0;
	return;
}

char *findShortestWay(int** maze, int mazeSize, int* mazeColSize, int* ball, int ballSize, int* hole, int holeSize) {
	bestStepCnt = MAXSIZE;
	memset(bestWay, 0, sizeof(char) * MAXSIZE);
	memset(curWay, 0, sizeof(char) * MAXSIZE);
	int curX = ball[0];
	int curY = ball[1];
	holeX = hole[0];
	holeY = hole[1];

	maze[curX][curY] = 2;
	moveNextPos(maze, mazeSize, mazeColSize, curX, curY, 0, 0, '\0');
	maze[curX][curY] = 0;
	if (bestStepCnt == MAXSIZE) {
		strcpy(bestWay, "impossible");
	}
	return bestWay;
}



// int main()
// {
//     int gridSize = MAP_ROW;
//     int **grid = NULL;
//     int *gridColSize = NULL;

//     /* 申请测试用例输入参数中需要的内存并根据用例输入初始化 */
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
//     int b[] = {4, 3};
//     int h[] = {3, 0};
//     char *result = findShortestWay(grid, gridSize, gridColSize, b, 2, h, 2);

//     /* 释放测试用例输入参数中申请的内存 */
//     for (int i = 0; i < gridSize; i++) {
//         free(grid[i]);
//     }
//     free(gridColSize);
//     free(grid);
// }