#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/*
    ���s�@�ĤG???�U?�A��[0,0]-[0,4]~6��5�C�A�̦Z�@��u���@�C�C
    1�G��?�@�ī܋몺ret�r�Ŧ�A�Τ_�O�s�C�@���r�Ū�����ާ@�r�Ŧ�C
    2�G??�C�ĥ�?�r�šA?��from->to��m?���ݭn���V���B?�C
    3�G�l��?��^�ȫO�s��?�G���C
    char * GetFrom2ToSteps()
    1�G��from����A��to����A�{�@��?�A�Θ򤧚V��?�̵u�A?�����k�@�w�O�̤�??�C
    2�G�i�H�����ϥ�to(x, y) - from(x, y)�A
    3�G�`�N�@�U�̦Z�@��u���@�C�A��?�i�H���z�A�p�G���ݭn�V�A������^!�A�ݭn�V�p�U�G
        �p�G to.x == 5, ?��ܭn����̦Z�@��A?�����V���ت��A�A�V�C�C
        �䥦���A���ޭ���?���A?�����V�C�A�A�V��C
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
        // ���V�C
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
        // ���V�C
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