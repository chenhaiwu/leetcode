#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool InitCheck(char * start, char * end, int *ret)
{
    *ret = 1;
    int len1 = strlen(start);
    int len2 = strlen(end);
    if (len1 != len2) {
        return false;
    }
    if (len1 == 0) {
        return true;
    }
    if (len1 == 1) {
        return *start == *end;
    }
    int startL = 0;
    int startR = 0;
    int endL = 0;
    int endR = 0;
    for (int i = 0; i < len1; i++) {
        if (start[i] == 'L') {
            startL++;
        }
        if (start[i] == 'R') {
            startR++;
        }
        if (end[i] == 'L') {
            endL++;
        }
        if (end[i] == 'R') {
            endR++;
        }
    }
    if (startL != endL || startR != endR) {
        return false;
    }
    *ret = 0;
    return true;
}

bool canTransform(char * start, char * end)
{
    int len1 = strlen(start);
    int len2 = strlen(end);
    int check = 0;
    bool ret = InitCheck(start, end, &check);
    if (check) {
        return ret;
    }
    int i = 0;
    int j = 0;
    while (i < len1 && j < len1) {
        if (start[i]  == 'X') {
            i++;
        } else if (end[j]  == 'X') {
            j++;
        } else if (start[i] == end[j]) {
            if (start[i] == 'L' && i < j) {
                return false;
            }
            if (start[i] == 'R' && i > j) {
                return false;
            }
            i++;
            j++;
        } else {
            return false;
        }
    }
    return true;
}

void main()
{
    char *s1 = "RXXLRXRXL";
    char *s2 = "XRLXXRRLX";
    char *start = (char *)malloc(strlen(s1) + 1);
    memset(start, 0x0, strlen(s1) + 1);
    memcpy(start, s1, strlen(s1));
    char *end = (char *)malloc(strlen(s2) + 1);
    memset(end, 0x0, strlen(s2) + 1);
    memcpy(end, s2, strlen(s2));
    bool ret = canTransform(start, end);
    printf("ret = %d\n", ret);
}