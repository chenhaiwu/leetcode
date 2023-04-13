#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/*
�������뵽�������һ�������������Լ���λ�ã���ô֮�����е��˶��������Լ���λ�á�
�����һ�����������ڵ�n���˵�λ�ã���ô��n����û���������Լ���λ�á�
�����һ�������ڳ����Լ�λ���Լ���n���˵�λ��֮����κ�λ�ã��������ͬn-1����λ�����
����ת�Ʒ���Ϊ: dp[i] = 1 / i + (i - 2) / i * dp[i - 1]
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