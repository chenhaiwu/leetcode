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
��������⣬���ȷ������ڵ�i�����ݣ�ֻ�����������ֵĲ������Ըı�����״̬������4�ŵ��ݣ���ֻ����1,2,4��Щ�ָı䣬5�ŵ��ݣ���ֻ����1,5�����ָı䣬��Ϊ��ʼ�����еĵ��ݵ�״̬��Ϊ�رգ��������һ�����ݺ������������ӣ���ô����Щ����֮����Ӧ���ǿ����ģ���Եģ������ż�������ӣ��Ǿ��ǹرյģ����������ʱת��Ϊ�˿�1-n�����еĵ����м�������
Ȼ��ȥ����ÿ���������ӣ����������ӵĸ���������������һ�������Ż��ĵ���Ƕ���һ�������� a=b*c,b��cһ�����ڸ���a�����˻��߾͵��ڸ���a����ôͳ�����ǵ����ӵĸ���ֻ��Ҫ��j��1������a�����������ſ����������j����ô��������2,��Ȼ�������������һ����Ҳ����������ֿ��Կ�ƽ�����ͼ�1���ɴ˿����ܽ������һ�������Ƕ����ܿ�ƽ�������֣�����������һ����һ�������������ڲ��ܿ�ƽ�����֣�����������Ϊһ��ż���������ֽ�����ת��Ϊ�ҳ�1-n�п��Կ�ƽ������
����1-n�еĿ��Կ�ƽ�������֣�����36����������Կ�ƽ��������1*1��2*2...6*6������100����������Կ�ƽ�������֣�1*1,...10*10,���Է��֣�����һ��������������Կ�ƽ�������ֵĸ����������Լ��Ŀ�ƽ�������������������յĽⷨ�ͱ�Ϊ��ֱ����n�Ŀ�ƽ�����������Ľ��
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