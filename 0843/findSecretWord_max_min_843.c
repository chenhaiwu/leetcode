#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX_CHARS 6

int WordMatch(char *word1, char *word2)
{
    int ret = 0;
    for (int i = 0; i < MAX_CHARS; i++) {
        if (word1[i] == word2[i]) {
            ret++;
        }
    }
    return ret;
}

void SortList(char** wordlist, int wordlistSize)
{
    int max_sum = INT_MIN;
    int max_i = -1;
    for (int i = 0; i < wordlistSize; i++) {
        int tmp_sum = 0;
        for (int j = 0; j < wordlistSize; j++) {
            if (WordMatch(wordlist[i], wordlist[j]) > 0) {
                tmp_sum++;
            }
        }
        if (max_sum < tmp_sum) {
            max_sum = tmp_sum;
            max_i = i;
        }
    }
    char *p = wordlist[max_i];
    wordlist[max_i] = wordlist[0];
    wordlist[0] = p;
}

int SearchList(char** wordlist, int *wordlistSize, Master* master)
{
    int newWordSize = 0;
    SortList(wordlist, *wordlistSize);
    char *guessWord = wordlist[0];
    int match_num = guess(master, guessWord);
    if (match_num == MAX_CHARS) {
        return match_num;
    }
    for (int i = 1; i < *wordlistSize; i++) {
        if (WordMatch(guessWord, wordlist[i]) == match_num) {
            wordlist[newWordSize++] = wordlist[i];
        }
    }
    *wordlistSize = newWordSize;
    return match_num;
}

void findSecretWord(char** wordlist, int wordlistSize, Master* master)
{
    char **newWordlist = (char **)malloc(sizeof(char *) * wordlistSize);
    memcpy(newWordlist, wordlist, sizeof(char *) * wordlistSize);
    int match_num;
    int newWordSize = wordlistSize;
    while (true) {
        match_num = SearchList(newWordlist, &newWordSize, master);
        if (match_num == MAX_CHARS) {
            break;
        }
    }
    return;
}

bool* canMakePaliQueries(char * s, int** queries, int queriesSize, int* queriesColSize, int* returnSize)
{
    bool *ret = (bool *)malloc(queriesSize * sizeof(bool));
    *returnSize = queriesSize;
    for (int i = 0; i < queriesSize; i++) {
        ret[i] = CheckValue(s, queries[i]);
    }
    return ret;
}

void main()
{
    findSecretWord(7);
    printf("ret = %f\n", ret);
}