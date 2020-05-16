#include <stdlib.h>
#include <stdio.h>

int Cmp(void *a, void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta - tb;
}

double Find(int *a, int len1, int *b, int len2)
{
    int len = len1 + len2;
    int *c = (int *)malloc((len + 1) * sizeof(int));
    for (int i = 0; i < len1; i++) {
        c[i] = a[i];
    }
    for (int i = 0; i < len2; i++) {
        c[len1 + i] = b[i];
    }
    qsort(c, len, sizeof(int), Cmp);
    for (int i = 0; i < len; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");
    double ans = (double)((len % 2 == 1) ? (c[len / 2]) : (c[(len - 1) / 2] + c[len / 2]) / 2);
    free(c);
    return ans;
}

int main()
{
    int a[] = {5, 3, 1};
    int b[] = {10, 11, 2};
    double ans = Find(a, sizeof(a) / sizeof(int), b, sizeof(b) / sizeof(int));
    printf("%f\n", ans);
    return 0;
}