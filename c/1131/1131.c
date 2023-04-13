#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
    2 <= arr1.length == arr2.length <= 40000
    -10^6 <= arr1[i], arr2[i] <= 10^6

    ����������룬��������ʹ�ö�̬�滮���ѱ��ʽ��������£�
    arr1[i] - arr1[j] + arr2[j] - arr2[i] + i-j (i > j)
    arr1[i] - arr1[j] + arr2[i] - arr2[j] + i-j (i > j)
    arr1[j] - arr1[i] + arr2[j] - arr2[i] + i-j (i > j)
    arr1[j] - arr1[i] + arr2[i] - arr2[j] + i-j (i > j)
    arr1[i] - arr1[j] + arr2[j] - arr2[i] + j-i (i < j)
    arr1[i] - arr1[j] + arr2[i] - arr2[j] + j-i (i < j)
    arr1[j] - arr1[i] + arr2[j] - arr2[i] + j-i (i < j)
    arr1[j] - arr1[i] + arr2[i] - arr2[j] + j-i (i < j)
    i ��j��һ���ģ�ֻ����i < j�����������ʽ�ͱ�ɺ���4�������ֵ��
    arr1[i] - arr2[i] + i;
    arr1[i] + arr2[i] + i;
    arr2[i] - arr1[i] - i;
    arr1[i] + arr2[i] - i;
    |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| ������൱���ڶ�άͼ���������پ��룬
    �����������پ��룺������4�������ϣ�����0, 0����x , y����ľ���ֵ�ĺͣ�
    ��Ϊԭ����Ҫ�����ֵ�����������ÿ����4�������ϵ����ֵ-��Сֵ���������������ˡ�
    ����Ϊԭ�⣬���������پ�����⣬����һ��i��ֵ�����ǿ��԰�iҲ�����ȥ��
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