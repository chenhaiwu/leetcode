#define MAX_LEN 1001
#define MOD 1000000007

/*
 *首先，每一列可能有4种状态，此处盗官方题解的图。

假设只有一列，那么4种状态对应的值是dp = [1, 0, 0, 1]
dp[0] 可以什么也不做所以是1.
dp[1] dp[2] 只有一列的话，不可能只铺一块砖，所以是0. 一个是上面有，一个是下面有
dp[3] 铺一竖列，占据两块砖，只有这一种可能所以是1.

假设有两列，那么第二列
new_dp[0] = dp[3] 这表示当前列为空的解法数。同时要保证前一列铺好，否则最后铺不满，前一列铺好只可能是dp[3]，那么在dp[3]的基础上什么也不做就可以到new_dp[0]
new_dp[1] = dp[0] + dp[2] 分别对应：（1）前一列没铺，那来一个L型的砖，铺满前一列（必须保证前一列铺好），同时把当前列的第一块铺好 （2）前一列的下一块砖铺好了，那么来一块横铺的砖就可以铺满前一列，且当前列第一块铺好
new_dp[2] = dp[0] + dp[1] 同上
new_dp[3] = dp[3] + dp[1] + dp[2] + dp[0] 这表示当前列铺满的解法数，对应4中情况 （1）前一列铺满了，当前列来一个竖块 （2）（3）前一列铺了一块，那来一个L型的砖，就可以即铺满前列，也可以铺满当前列 （4）前一列什么也没铺，那么要同时铺满前列和当前列，可以有两种铺发，两个横的或者两个竖的，但是两个竖的与（1）是重复的，所以这里只有一种可能，就是两个横的砖。

计算N-1次，最后的dp[3]就是全铺满的解法数。
*/
int numTilings(int N)
{
    long long dp0 = 1, dp1 = 0, dp2 = 0, dp3 = 1;
    long long newdp0, newdp1, newdp2, newdp3;
    for (int i = 1; i < N; i++) {
        newdp0 = (dp3 % MOD);
        newdp1 = (dp0 + dp2) % MOD;
        newdp2 = (dp0 + dp1) % MOD;
        newdp3 = (dp0 + dp1 + dp2 + dp3) % MOD;
        // swap newdp & dp
        dp0 = newdp0;
        dp1 = newdp1;
        dp2 = newdp2;
        dp3 = newdp3;
    }
    return (int)dp3;
}
