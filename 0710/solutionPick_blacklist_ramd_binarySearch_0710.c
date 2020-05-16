#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAXNUM 100001
typedef struct {
    int n;
    int *blacklist;
    int blackSize;
} Solution;


int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

Solution* solutionCreate(int N, int* blacklist, int blacklistSize) {
    Solution* slu = (Solution *)malloc(sizeof(Solution));
    slu->n = N;
    slu->blackSize = blacklistSize;
    slu->blacklist = (int *)malloc(sizeof(int) * blacklistSize);
    for (int i = 0; i < blacklistSize; i++) {
        slu->blacklist[i] = blacklist[i];
    }
    qsort(slu->blacklist, slu->blackSize, sizeof(int), Cmp);
    return slu;
}

int solutionPick(Solution* obj) {
    int size = obj->n - obj->blackSize;
    int k = rand() % (size);
    int left = 0;
    int right = obj->blackSize - 1;
    if (obj->blacklist[left] - left > k) {
        return k;
    }
    while (left < right) {
        int mid = (left + right + 1) / 2;
        int firstHalfWriteNum = obj->blacklist[mid] - mid;
        if (firstHalfWriteNum > k) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }
    if (left == right && obj->blacklist[left] - left <= k) {
        return k + left + 1;
    } else {
        return k;
    }
}

void solutionFree(Solution* obj) {
    if (obj) {
        free(obj->blacklist);
        obj->blacklist = NULL;
        free(obj);
    }
    obj = NULL;
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(N, blacklist, blacklistSize);
 * int param_1 = solutionPick(obj);
 
 * solutionFree(obj);
*/

int main()
{
    int a[] = {1,5,9,1,5,9};
    int k = 2;
    int t = 3;
    bool ret = containsNearbyAlmostDuplicate(a, sizeof(a)/sizeof(int), k, t);
    printf("ret=%d\n", ret);
    return 0;
}