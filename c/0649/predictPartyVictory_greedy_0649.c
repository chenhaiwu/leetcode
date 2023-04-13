#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

/* 
 *  ������������һ��һ�ֵ�ɱ��ֱ���������Ϊ0��r_count:���ŵ�R��Ա���� d_count:���ŵ�D��Ա����
    kill_r:������ɱ��R��Ա���� kill_d:������ɱ��D��Ա����
 */


char * predictPartyVictory(char * senate1)
{
    int totalR = 0, totalD;
    int len = strlen(senate1);
    char *senate = (char *)malloc(len);
    memcpy(senate, senate1, len);
    for (int i = 0; i < len; i++) {
        if (senate[i] == 'R') {
            totalR++;
        }
    }
    totalD = len - totalR;
    int pos = 0, kill_r = 0, kill_d = 0;
    while (totalR && totalD) {
        pos = pos % len;
        if (senate[pos] == 'R') {
            if (kill_r > 0) {
                kill_r--;
                totalR--;
                senate[pos] = 'S';
            } else {
                kill_d++;
            }
        } else if (senate[pos] == 'D') {
            if (kill_d > 0) {
                kill_d--;
                totalD--;
                senate[pos] = 'S';
            } else {
                kill_r++;
            }
        }
        pos++;
    }
    return totalD == 0 ? "Radiant" : "Dire";
}

int main()
{
    int *ret = predictPartyVictory("RRDDD");
    printf("ret=%sn", ret);
    return 0;
}