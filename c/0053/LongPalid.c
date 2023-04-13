#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

int maxSubArray(int* nums, int numsSize)
{
    int he = nums[0];
    int zuida = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (he > 0) {
            he = he + nums[i];
        } else {
            he = nums[i];   
        }
        zuida = MAX(zuida, he);
    }
    return zuida;
}

void main()
{
    printf("hello world\n");
}