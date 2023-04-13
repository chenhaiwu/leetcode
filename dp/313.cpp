// 超级丑数 是一个正整数，并满足其所有质因数都出现在质数数组 primes 中。

// 给你一个整数 n 和一个整数数组 primes ，返回第 n 个 超级丑数 。

// 题目数据保证第 n 个 超级丑数 在 32-bit 带符号整数范围内。

//  

// 示例 1：

// 输入：n = 12, primes = [2,7,13,19]
// 输出：32 
// 解释：给定长度为 4 的质数数组 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。
// 示例 2：

// 输入：n = 1, primes = [2,3,5]
// 输出：1
// 解释：1 不含质因数，因此它的所有质因数都在质数数组 primes = [2,3,5] 中。
//  
// 提示：

// 1 <= n <= 105
// 1 <= primes.length <= 100
// 2 <= primes[i] <= 1000
// 题目数据 保证 primes[i] 是一个质数
// primes 中的所有值都 互不相同 ，且按 递增顺序 排列


// 动态规划
// 考虑新丑数的诞生方式，简单推算可得：
// ​ 旧丑数序列 * 质数序列 = 新丑数序列
// 因为存在新旧的转移关系，可以考虑用动态规划解决此题。

// 因为题目要求第n个丑数，即我们需要从第一个丑数不断推移至第n个丑数，我们需要考虑已知第一个丑数，如何找出第二个丑数。

// 因为已知： 旧丑数序列 * 质数序列 = 新丑数序列

// 则我们把质数序列依次乘于第一个丑数后，就可以得到新丑数序列，新丑数序列中最小的丑数，便是第二个丑数

// 以此类推：已知前n个丑数，如何得出第n + 1个丑数

// 仍然是： 旧丑数序列 * 质数序列 = 新丑数序列
// 但是： 旧丑数序列依次乘于质数序列将会出现 n * n的复杂度，有没有办法优化呢？
// 优化方案：因为我们要求出的是下一个最小的丑数，当旧丑数序列中的 一个丑数 和 一个质数 已经贡献出过一个最小值，则它们肯定无法再次贡献出最小值，即不考虑该质数与这个丑数的乘积，只考虑该质数下的下一个丑数与它的乘积。那么，我们再定义一个pointer数组，用于记录每个质数应该与哪个旧丑数做乘积即可。





#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<long> dp(n + 1);
        int m = primes.size();
        vector<int> pointers(m, 0);
        vector<long> nums(m, 1);
        for (int i = 1; i <= n; i++) {
            long minNum = INT_MAX;
            for (int j = 0; j < m; j++) {
                minNum = min(minNum, nums[j]);
            }
            dp[i] = minNum;
            for (int j = 0; j < m; j++) {
                if (nums[j] == minNum) {
                    pointers[j]++;
                    nums[j] = dp[pointers[j]] * primes[j];
                }
            }
        }
        return dp[n];
    }
};


int main()
{
    Solution obj;
    vector<int> primes = {2,7,13,19};
    int ret = obj.nthSuperUglyNumber(12, primes);
    cout << ret << endl;
    system("pause");
    return 0;
}
