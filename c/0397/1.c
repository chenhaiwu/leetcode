#include <stdio.h>
#include <string.h>
#include <limits.h>

/* 分析移位特点，主要思想是
   1：如果是偶数，则直接除2
   2：如果是奇数，则再看前面一位，前一位是0，则直接-1，否则+1；这个要归纳法分析，注意只分析到8以下就够了
   3：如果是3的话，比较特别，不能+1,而是3->2->1的
   编码注意点：(n & 1) == 0，& 与==的优先级是，==高。
*/
int integerReplacement1(int m)
{
    int cnt = 0;
    unsigned int n = m;
    /* 选用无符号即可，或者也可以使用long long */
    // long long n = m;
    while (n != 1) {
        if ((n & 1) == 0) {
            n = n >> 1;
            cnt++;
        } else {
            /* 区别前面一位是0还是1，如果是0，则直接-1，如果是1，则+1，但是最后的值3，有特别性 */
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

/* 使用递归来算，由于不知道入参n的值范围，不方便直接申请m整形的值空间，来记忆化，所以先不记忆化，leetcode也通过
   由于计算的量并不大，有偶数可以直接除2，消化得快。
   类似题目，如果要记忆化，优先考虑INT 数组空间了事，如果不行，可以考虑HASH存过程值
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