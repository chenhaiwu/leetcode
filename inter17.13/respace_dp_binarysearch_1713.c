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

#define MAXLEN 10002

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

int Cmp(void *a, void *b)
{
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;
    return strcmp(s1, s2);
}

bool IsWordExist(char** dictionary, int dictionarySize, char *str, int len)
{
    int left = 0;
    int right = dictionarySize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int ret = strncmp(dictionary[mid], str, len);
        if (ret == 0) {
            int ret2 = strlen(dictionary[mid]);
            if (ret2 == len) {
                return true;
            } else if (ret2 > len) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else if (ret > 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return false;
}

bool IsWordExist2(char** dictionary, int dictionarySize, char *str, int len)
{
    for (int i = 0; i < dictionarySize; i++) {
        if (strlen(dictionary[i]) == len && strncmp(dictionary[i], str, len) == 0) {
            return true;
        }
    }
    return false;
}

int respace(char** dictionary, int dictionarySize, char* sentence)
{
    qsort(dictionary, dictionarySize, sizeof(char *), Cmp);
    int len = strlen(sentence);
    int *dp = (int *)malloc(sizeof(int) * (len + 1));
    dp[0] = 1;
    for (int i = 0; i <= len; i++) {
        if (i > 0) {
            dp[i] = dp[i - 1] + 1;
        }
        for (int j = 0; j <= i; j++) {
            if (IsWordExist(dictionary, dictionarySize, sentence + j, i - j + 1)) {
                dp[i] = MIN(dp[i], dp[j]);
            }
        }
    }
    int ans = dp[len] - 1;
    PrintArray(dp, len + 1);
    free(dp);
    return ans;
}

int main()
{
    return 0;
}

class Solution:
    def respace(self, dictionary: List[str], sentence: str) -> int:
        dictionary = {*dictionary}
        n = len(sentence)
        d = [0] * (n + 1)
        for i in range(n + 1):
            d[i] = d[i - 1] + 1
            for j in range(i + 1):
                if sentence[j: i] in dictionary:
                    d[i] = min(d[i], d[j])
        return d[-1] - 1
