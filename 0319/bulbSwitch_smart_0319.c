#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

int bulbSwitch(int n)
{
    int ret = 0;
    int *a = (int *)malloc(sizeof(int) * (n + 1));
    memset(a, 0x0, sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j += i) {
            a[j]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] % 2 == 1) {
            ret++;
        }
    }
    return ret;
}

/*
对于这道题，首先分析对于第i个灯泡，只有它的因子轮的操作可以改变它的状态，例如4号灯泡，就只会在1,2,4这些轮改变，5号灯泡，就只会在1,5这两轮改变，因为初始的所有的灯泡的状态都为关闭，所以如果一个灯泡含有奇数个因子，那么在这些操作之后他应该是开启的，相对的，如果是偶数个因子，那就是关闭的，所以问题此时转化为了看1-n的所有的灯泡有几个因子
然后去分析每个数的因子，看它们因子的个数，但是这里有一个可以优化的点就是对于一个数例如 a=b*c,b和c一定是在根号a的两端或者就等于根号a，那么统计它们的因子的个数只需要让j从1到根号a，如果灯泡序号可以整除这个j，那么因子数加2,当然如果两个因子数一样（也就是这个数字可以开平方）就加1，由此可以总结出来的一个规律是对于能开平方的数字，它的因子数一定是一个奇数，而对于不能开平方数字，它的因子数为一个偶数，所以又将问题转化为找出1-n中可以开平方的数
对于1-n中的可以开平方的数字，例如36，它里面可以开平方的数字1*1，2*2...6*6，对于100，它里面可以开平方的数字，1*1,...10*10,可以发现，对于一个数，它里面可以开平方的数字的个数就是它自己的开平方数，所以这道题的最终的解法就变为了直接求n的开平方数就是最后的结果
*/
int bulbSwitch(int n)
{
    int ret = pow(n, 0.5);
    return ret;
}

void main()
{
    int ret = bulbSwitch(1);
    printf("ret = %d\n", ret);
    ret = bulbSwitch(2);
    printf("ret = %d\n", ret);
    ret = bulbSwitch(3);
    printf("ret = %d\n", ret);
    ret = bulbSwitch(7);
    printf("ret = %d\n", ret);
}