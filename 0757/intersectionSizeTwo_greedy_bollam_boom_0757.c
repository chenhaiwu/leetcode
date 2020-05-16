#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>


/*
1.���������䰴��������������С�����������һ�����ҵ��С��������
2.�������left,mid,righ����ǰ����������еĵ�һ������[left,mid]��Χ�ڣ��ڶ�����(mid,right]��Χ�ڣ�mid���Ϊ-1��ʾ[left,right]�����ѡ������
3.�����������������䣬��������¼��ֳ���:
a.�������䲻�ཻ����ȻҪ����������ѡ2����������left=leftPoint��right=rightPoint��mid = -1
b.���������ཻһ��������Ҫ����������ѡ1����������left = leftPoint��right = rightPoint��mid = leftPoint
c.��mid��ֵ��leftPoint > midʱ�������ֳ�������left,right,mid��������Ҫ��ѡ1����:
i.rightPoint > right
ii.rightPoint <= right
d.��������������Ҫ����������ѡ���ˣ�����left,right,mid����
*/
int Compare(const void *p1, const void *p2)
{
    int **interval1 = (int **)p1;
    int **interval2 = (int **)p2;

    if (interval1[0][0] == interval2[0][0]) {
        return interval1[0][1] - interval2[0][1];
    }

    return interval1[0][0] - interval2[0][0];
}

int intersectionSizeTwo(int** intervals, int intervalsSize, int* intervalsColSize){
    int i;
    int count = 2;
    int left = 0;
    int right = 0;
    int mid = -1;
    int leftPoint = 0;
    int rightPoint = 0;

    if (intervalsSize <= 0) {
        return 0;
    }

    qsort(intervals, intervalsSize, sizeof(int **), Compare);

    left = intervals[0][0];
    right = intervals[0][1];
    for (i = 1; i < intervalsSize; i++) {
        leftPoint = intervals[i][0];
        rightPoint = intervals[i][1];

        if (leftPoint > right) {
            count += 2;
            left = leftPoint;
            right = rightPoint;
            mid = -1;
        } else if (leftPoint == right) {
            count += 1;
            left = leftPoint;
            right = rightPoint;
            mid = leftPoint;
        } else if (mid != -1 && leftPoint > mid) {
            count += 1;
            if (rightPoint > right) {
                mid = right;
                right = right < rightPoint ? rightPoint : right;
            } else {
                mid = -1;
                right = right > rightPoint ? rightPoint : right;
            }
            left = leftPoint;
        } else {
            left = leftPoint;
            right = right > rightPoint ? rightPoint : right;
        }
    }

    return count;
}