#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
    2 <= arr1.length == arr2.length <= 40000
    -10^6 <= arr1[i], arr2[i] <= 10^6

    曼哈顿求矩离，不过我们使用动态规划，把表达式化简成如下：
    arr1[i] - arr1[j] + arr2[j] - arr2[i] + i-j (i > j)
    arr1[i] - arr1[j] + arr2[i] - arr2[j] + i-j (i > j)
    arr1[j] - arr1[i] + arr2[j] - arr2[i] + i-j (i > j)
    arr1[j] - arr1[i] + arr2[i] - arr2[j] + i-j (i > j)
    arr1[i] - arr1[j] + arr2[j] - arr2[i] + j-i (i < j)
    arr1[i] - arr1[j] + arr2[i] - arr2[j] + j-i (i < j)
    arr1[j] - arr1[i] + arr2[j] - arr2[i] + j-i (i < j)
    arr1[j] - arr1[i] + arr2[i] - arr2[j] + j-i (i < j)
    i 与j是一样的，只考虑i < j的情况，则表达式就变成后面4个求最大值，
    arr1[i] - arr2[i] + i;
    arr1[i] + arr2[i] + i;
    arr2[i] - arr1[i] - i;
    arr1[i] + arr2[i] - i;
    |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| 这个就相当于在二维图上找曼哈顿矩离，
    两点找曼哈顿矩离：就是在4个方向上，到（0, 0）的x , y坐标的绝对值的和，
    因为原题是要求最大值，所以先求出每个点4个方向上的最大值-最小值，这样差就是最大了。
    又因为原题，除了曼哈顿矩离除外，还有一个i的值，我们可以把i也代入进去。
*/

int maxAbsValExpr(int* arr1, int arr1Size, int* arr2, int arr2Size)
{
    int ans = 0;
    int diff[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 0; i < 4; i++) {
        int max = INT_MIN;
        int min = INT_MAX;
        for (int j = 0; j < arr1Size; j++) {
            int tmp = arr1[j] * diff[i][0] + arr2[j] * diff[i][1] + j;
            max = max > tmp ? max : tmp;
            min = min < tmp ? min : tmp;
        }
        ans = ans > (max - min) ? ans : (max - min);
    }
    return ans;
}

void main()
{
    int arr1[4] = {1,2,3,4};
    int arr2[4] = {-1, 4, 5, 6};
    int ret = maxAbsValExpr(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int));
    printf("ret = %d\n", ret);
    return;
}