#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/*
    熌????熛[0,0]-[0,4]~6︽5程︽Τ
    1ビ?熌嬰ret才﹃ノ玂–Ω才簿巨才﹃
    2??–熌ヘ?才?衡from->to竚?簿惠璶簿塚˙?
    3ㄧ?玂?狦い
    char * GetFrom2ToSteps()
    1熛from橋to橋渰樼?壩橋ぇ歏?程祏?ǐ猭﹚琌程ぶ??
    2钡ㄏノto(x, y) - from(x, y)
    3猔種程︽Τи?安墇狦ぃ惠璶塚钡!惠璶塚
        狦 to.x == 5, ?ボ璶簿程︽?簿塚︽ヘ塚
        ㄤウぃ恨熌?春?簿塚塚︽
*/

#define MAXLEN 100
#define ROWS 6
#define COLS 5
int g_matrix[ROWS][COLS];
int g_from[2];
int g_to[2];

void PreHandle()
{
    for (int i = 0; i < ROWS - 1; i++) {
        for (int j = 0; j < COLS; j++) {
            g_matrix[i][j] = i * ROWS + j;
        }
    }
    g_matrix[ROWS - 1][0] = 25;
    for (int j = 1; j < COLS; j++) {
        g_matrix[ROWS - 1][j] = -1;
    }
}

char * GetFrom2ToSteps()
{
    if (g_from[0] == g_to[0] && g_from[1] == g_to[1]) {
        return "!";
    }
    int rowSteps = g_to[0] - g_from[0];
    int colSteps = g_to[1] - g_from[1];
    int len = abs(rowSteps) + abs(colSteps) + 1 + 1;
    char *ret = (char *)malloc(len);
    memset(ret, 0x0, len);
    int i = 0, j = 0;
    int k = 0;
    if (g_from[0] == ROWS - 1) {
        // 塚
        for (j = 0; j < abs(rowSteps); j++) {
            if (rowSteps < 0) {
                ret[j] = 'U';
            } else {
                ret[j] = 'D';
            }            
        }
        for (i = 0; i < abs(colSteps); i++) {
            if (colSteps < 0) {
                ret[i + j] = 'L';
            } else {
                ret[i + j] = 'R';
            }
        }
        ret[i + j] = '!';

    } else {
        // 塚
        for (i = 0; i < abs(colSteps); i++) {
            if (colSteps < 0) {
                ret[i] = 'L';
            } else {
                ret[i] = 'R';
            }
        }
        for (j = 0; j < abs(rowSteps); j++) {
            if (rowSteps < 0) {
                ret[i + j] = 'U';
            } else {
                ret[i + j] = 'D';
            }            
        }
        ret[i + j] = '!';        
    }
    return ret;
}

char * alphabetBoardPath(char * target)
{
    char *ret = (char *)malloc(MAXLEN);
    char *p = ret;
    memset(ret, 0x0, MAXLEN);
    PreHandle();
    int len = strlen(target);
    int idx;
    g_from[0] = 0;
    g_from[1] = 0;
    char *onestep;
    for (int i = 0; i < len; i++) {
        idx = target[i] - 'a';
        g_to[0] = idx / COLS;
        g_to[1] = idx % COLS;
        onestep = GetFrom2ToSteps();
        g_from[0] = g_to[0];
        g_from[1] = g_to[1];
        int retLen = strlen(onestep);
        strcpy(p, onestep);
        p += retLen;
        if (retLen > 1) {
            free(onestep);
        }
        printf("%s\n", ret);
    }
    return ret;
}

int main()
{
    char * ret = alphabetBoardPath("zb");
    printf("%s\n", ret);
    free(ret);
    return 0;
}