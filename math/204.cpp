// 给定整数 n ，返回 所有小于非负整数 n 的质数的数量 。

//  

// 示例 1：

// 输入：n = 10
// 输出：4
// 解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
// 示例 2：

// 输入：n = 0
// 输出：0
// 示例 3：

// 输入：n = 1
// 输出：0
//  

// 提示：

// 0 <= n <= 5 * 106


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


// 求数字n，质数的个数，直接求，发现超时
// class Solution {
// public:
//     bool isPrime(int n) {
//         for (int i = 2; i * i <= n; i++) {
//             if (n % i == 0) {
//                 return false;
//             }
//         }
//         return true;
//     }

//     int countPrimes(int n) {
//         int ans = 0;

//         for (int i = 2; i < n; i++) {
//             if (isPrime(i)) {
//                 ans += 1;
//             }
//         }

//         return ans;
//     }
// };

// 这种方法的正确性是比较显然的：这种方法显然不会将质数标记成合数；另一方面 当从小到大遍历到数x时，倘若它是合数，则它一定是某个小于x的质数y的整数倍，故根据此方法的步骤，我们在遍历到 y 时，
// 就一定会在此时将 x 标记为 isPrime[]=0 isPrime[x]=0。因此，这种方法也不会将合数标记为质数。

// 当然这里还可以继续优化，对于一个质数 x  如果按上文说的我们从 2 2x 开始标记其实是冗余的，应该直接从 x⋅x 开始标记，因为 
// 2x,3x,… 这些数一定在 x 之前就被其他数的倍数标记过了，例如 2 2 的所有倍数， 3 3的所有倍数等

class Solution {
public:
    int countPrimes(int n) {
        int ans = 0;
        vector<int> isPrimes(n, 1);

        for (int i = 2; i < n; i++) {
            if (isPrimes[i]) {
                ans += 1;

                if ((long long)(i * i) < n) {
                    for (int j = i * i; j < n; j += i) {
                        isPrimes[j] = 0;
                    }
                }
            }
        }

        return ans;
    }
};

int main()
{
    Solution obj;
    // vector<int> nums = {1,2,3,4,5,6,7};
    int k = 10;
    int ret = obj.countPrimes(k);
    // for (int i = 0; i < nums.size(); i++) {
    //         cout << nums[i] << " ";
    // }
    system("pause");
    return 0;
}