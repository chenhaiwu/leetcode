#include <stdio.h>
#include <string.h>
#include <limits.h>

/* ������λ�ص㣬��Ҫ˼����
   1�������ż������ֱ�ӳ�2
   2����������������ٿ�ǰ��һλ��ǰһλ��0����ֱ��-1������+1�����Ҫ���ɷ�������ע��ֻ������8���¾͹���
   3�������3�Ļ����Ƚ��ر𣬲���+1,����3->2->1��
   ����ע��㣺(n & 1) == 0��& ��==�����ȼ��ǣ�==�ߡ�
*/
int integerReplacement1(int m)
{
    int cnt = 0;
    unsigned int n = m;
    /* ѡ���޷��ż��ɣ�����Ҳ����ʹ��long long */
    // long long n = m;
    while (n != 1) {
        if ((n & 1) == 0) {
            n = n >> 1;
            cnt++;
        } else {
            /* ����ǰ��һλ��0����1�������0����ֱ��-1�������1����+1����������ֵ3�����ر��� */
            if ((n & 2) == 0) {
                n = n - 1;
            } else {
                if (n == 3) {
                    cnt += 2;
                    break;
                } else {
                    n = n + 1;
                }
            }
            cnt += 1;
        }
    }
    return cnt;
}

/* ʹ�õݹ����㣬���ڲ�֪�����n��ֵ��Χ��������ֱ������m���ε�ֵ�ռ䣬�����仯�������Ȳ����仯��leetcodeҲͨ��
   ���ڼ��������������ż������ֱ�ӳ�2�������ÿ졣
   ������Ŀ�����Ҫ���仯�����ȿ���INT ����ռ����£�������У����Կ���HASH�����ֵ
*/
int integerReplacement(int m)
{
    int cnt = 0;
    if (m == 1) return 0;
    if (m == 2) return 1;
    if (m == INT_MAX) return 32;
    if (m & 1) {
        int c1 = integerReplacement(m + 1);
        int c2 = integerReplacement(m - 1);
        cnt = c1 > c2 ? c2 : c1;
        cnt += 1;
    } else {
        cnt = 1 + integerReplacement(m >> 1);
    }
    return cnt;
}


void main()
{
    int ret;
    ret = integerReplacement(4);
    printf("ret = %d\n", ret);
    ret = integerReplacement(15);
    printf("ret = %d\n", ret);
    ret = integerReplacement(16);
    printf("ret = %d\n", ret);
    ret = integerReplacement(INT_MAX);
    printf("ret = %d\n", ret);
    ret = integerReplacement(INT_MAX - 1);
    printf("ret = %d\n", ret);
    return;
}