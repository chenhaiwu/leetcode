#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)

int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize)
{
    int left, right, v;
    int *ret = (int)malloc(sizeof(int) * (n + 1));
    memset(ret, 0x0, sizeof(int) * (n + 1));
    for (int i = 0; i < bookingsSize; i++) {
        left = bookings[i][0] - 1;
        right = bookings[i][1] - 1;
        v = bookings[i][2];
        ret[left] += v;
        ret[right + 1] -= v;
    }
    for (int i = 1; i < n; i++) {
        ret[i] = ret[i - 1] + ret[i];
    }
    *returnSize = n;
    return ret;
}

int main()
{
    int ret = 1;
    printf("ret=%d\n", ret);
    return 0;
}