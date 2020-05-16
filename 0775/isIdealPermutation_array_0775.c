#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define DEGUG_CHW 0
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

/* ������ʱ��ͨ��191/208 case�����
 * һ���ֲ�����Ҳ��һ��ȫ�ֵ��ã����ֻ��Ҫ�����û�зǾֲ����þͿ����ˡ�
 * ����ķǾֲ�����ָ���� A[i] > A[j], i < j������ j - i > 1 
 * */
bool isIdealPermutation_1(int* A, int ASize)
{
    bool ret = true;
    for (int i = 0; i < ASize; i++) {
        for (int j = i + 2; j < ASize; j++) {
            if (A[i] > A[j]) {
                return false;
            }
        }
    }
    return ret;
}

/* ��Сֵʱ��ͨ�����ұ�������ң���ǰ�Ǻ�ǰ���2���ȣ�ֻҪǰ���һ��ֵ�Ⱥ������Сֵ��
 * ��˵����ǰ��� i -2��ֵ�����ڷǾ��Ե���������򷵻�false.
 * */
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)
bool isIdealPermutation_2(int* A, int ASize)
{
    int minV = ASize;
    bool ret = true;
    for (int i = ASize - 1; i >= 2; i--) {
        minV = MIN(minV, A[i]);
        if (A[i - 2] > minV) {
            return false;
        }
    }
    return ret;
}

/* ��ѧ���ɷ���
 * ������һ������Ϊ n������Ԫ��Ϊ 0 �� n-1 �����顣�����������飬���� ���� ����Ϊ�������һ�������ڷǾֲ����õ����С�
 * ���� ���� ���У�0 Ӧ���������أ� ��� 0 ���±���ڵ��� 2��һ������ A[0] > A[2] = 0������һ���Ǿֲ����á����� 0 ֻ�ܳ��� * ���±� 0 �����±� 1���� A[1] = 0����Ȼ A[0] = 1������ͻ��� A[0] > A[j] = 1����Ҳ��һ���Ǿֲ����á��� A[0] = 0����ʱ��* ���ת������һ�������⡣
 * �����������ۣ����Թ��ɳ� ���� ����ĳ�ֱ�Ҫ����Ϊ Math.abs(A[i] - i) <= 1
*/
bool isIdealPermutation(int* A, int ASize)
{
    bool ret = true;
    for (int i = 0; i < ASize; i++) {
        if (abs(A[i] - i) > 1) {
            return false;
        }
    }
    return ret;
}

int main()
{
    int nums[] = {2,3,1,2,4,3};
    int retsize = isIdealPermutation(nums, sizeof(nums) / sizeof(int));
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
