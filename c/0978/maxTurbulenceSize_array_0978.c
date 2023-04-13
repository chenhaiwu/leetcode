#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)

int CheckFirst(int* A, int ASize)
{
    int ret = 0;
    if (ASize == 1) {
        return 1;
    }
    if (ASize == 2) {
        return A[0] != A[1] ? 2 : 1;
    }
    /*
    if (ASize == 3) {
        if (A[0] == A[1] && A[0] != A[2]) {
            return 2;
        }
        if ()
    }
    */
   return ret;
}

int maxTurbulenceSize_1(int* A, int ASize)
{
    int ret = 1;
    bool isBig = false;
    int i, j;
    if (ASize < 3) {
        return CheckFirst(A, ASize);
    }

    for (i = 1; i < ASize; i++) {
        if (A[i] == A[i - 1]) {
            continue;
        }
        if (A[i] > A[i - 1]) {
            isBig = true;
        } else {
            isBig = false;
        }
        for (j = i + 1; j < ASize; j++) {
            if (isBig && A[j] < A[j - 1]) {
                isBig = false;
                continue;
            }
            if (!isBig && A[j] > A[j - 1]) {
                isBig = true;
                continue;
            }
            ret = MAX(ret, j + 1 - i);
            break;
        }
        if (j == ASize) {
            ret = MAX(ret, ASize + 1 - i);
        }
    }
    return ret;
}

int CompareFlag(int a, int b)
{
    return (a > b) ? 1 : ((a == b) ? 0 : -1);
}

int maxTurbulenceSize(int* A, int ASize)
{
    if (ASize == 0) {
        return 0;
    }
    int ret = 1;
    int isBig;
    int left = 0, right = left + 1;
    while (right < ASize) {
        isBig = CompareFlag(A[right - 1], A[right]);
        if (right == ASize - 1 || isBig * CompareFlag(A[right], A[right + 1]) != -1) {
            if (isBig != 0 ) {
                ret = MAX(ret, right + 1 - left);
            }
            left = right;
        }
        right++;
    }
    return ret;
}

int main()
{
    int a[] = {9,4,2,10,7,8,8,1,9};
    int ret = maxTurbulenceSize(a, sizeof(a) / sizeof(int));
    printf("ret=%d\n", ret);
    return 0;
}