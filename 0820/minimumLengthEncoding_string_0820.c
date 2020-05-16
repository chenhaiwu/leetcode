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

void RevertWords(char ** words, int wordsSize)
{
    char tmp;
    for (int i = 0; i < wordsSize; i++) {
        char *word = words[i];
        int len = strlen(word);
        char *p1 = word;
        char *p2 = word + len - 1;
        while (p1 < p2) {
            tmp = *p1;
            *p1 = *p2;
            *p2 = tmp;
            p1++;
            p2--;
        }
    }
}

int Cmp(void *a, void *b)
{
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;
    return strcmp(s1, s2);
}

int minimumLengthEncoding(char ** words, int wordsSize)
{
    RevertWords(words, wordsSize);
    qsort(words, wordsSize, sizeof(char *), Cmp);
    int tmp = 0, sum = 0;
    for (int i = 0; i < wordsSize - 1; i++) {
        int tmp = strlen(words[i]);
        if (strncmp(words[i], words[i + 1], tmp) == 0) {
            tmp = 0;
        } else {
            tmp += 1;
        }
        sum += tmp;
    }
    sum = sum + strlen(words[wordsSize - 1]) + 1;
    return sum;
}

int main()
{
    return 0;
}