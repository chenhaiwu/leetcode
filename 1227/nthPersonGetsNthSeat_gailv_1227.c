#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/*
很容易想到，如果第一个人正好坐在自己的位置，那么之后所有的人都会坐在自己的位置。
如果第一个人正好坐在第n个人的位置，那么第n个人没可能坐在自己的位置。
如果第一个人坐在除了自己位置以及第n个人的位置之外的任何位置，情况就如同n-1个座位情况。
所以转移方程为: dp[i] = 1 / i + (i - 2) / i * dp[i - 1]
*/

double nthPersonGetsNthSeat(int n)
{
    double *dp = (double *)malloc((n + 1) * sizeof(double));
    memset(dp, 0x0, sizeof(dp));
    dp[0] = 1.00000;
    dp[1] = 1.00000;
    for (int i = 2; i <= n; i++) {
        dp[i] = 1 / (double)i + ((double)i - 2) / (double) i * dp[i - 1];
    }
    return dp[n];
}

void main()
{
    double ret = nthPersonGetsNthSeat(3);
    printf("ret = %f\n", ret);
    ret = nthPersonGetsNthSeat(2);
    printf("ret = %f\n", ret);
    ret = nthPersonGetsNthSeat(4);
    printf("ret = %f\n", ret);
    ret = nthPersonGetsNthSeat(7);
    printf("ret = %f\n", ret);
}