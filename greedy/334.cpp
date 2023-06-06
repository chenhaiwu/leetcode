// 给你一个整数数组 nums ，判断这个数组中是否存在长度为 3 的递增子序列。

// 如果存在这样的三元组下标 (i, j, k) 且满足 i < j < k ，使得 nums[i] < nums[j] < nums[k] ，返回 true ；否则，返回 false 。

//  

// 示例 1：

// 输入：nums = [1,2,3,4,5]
// 输出：true
// 解释：任何 i < j < k 的三元组都满足题意
// 示例 2：

// 输入：nums = [5,4,3,2,1]
// 输出：false
// 解释：不存在满足题意的三元组
// 示例 3：

// 输入：nums = [2,1,5,0,4,6]
// 输出：true
// 解释：三元组 (3, 4, 5) 满足题意，因为 nums[3] == 0 < nums[4] == 4 < nums[5] == 6
//  

// 提示：

// 1 <= nums.length <= 5 * 105
// -231 <= nums[i] <= 231 - 1
// 你能实现时间复杂度为 O(n) ，空间复杂度为 O(1) 的解决方案吗？

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// baoli算法
// 1: 三重循环，剪枝，注意数组长度一定要大于3，同时这里的递增，一定就是强增，不可以是相等；---》结果超时

// class Solution {
// public:
//     bool increasingTriplet(vector<int>& nums) {
//         int len = nums.size();
//         if (len < 3) {
//             return false;
//         }

//         for (int k = 2; k < len; i++) {
//             for (int j = 1; j < k; j++) {
//                 if (nums[j] > nums[k])
//                     continue;
//                 for (int i = 0; i < j; i++) {
//                     if (nums[i] > nums[j])
//                         continue;
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
// };

// 此题暴力解想都不用想，必然超过10的8次方，而进阶要求的O(N) 对于数组而言无非就是从前往后，从后往前遍历俩种方式。此时解决问题就从重新定义问题入手
// 如果数组nums中存在一个下标 ii 满足1≤i<n-1使得在nums[i] 的左边存在一个元素小于nums[i] 且在 nums[i] 的右边存在一个元素大于nums[i]，则数组 nums 中存在递增的三元子序列。
// 在nums[i] 的左边存在一个元素小于nums[i] 等价于在nums[i] 的左边的最小元素小于 nums[i]，在nums[i] 的右边存在一个元素大于nums[i] 等价于在nums[i] 的右边的最大元素大于nums[i]，
// 因此可以维护数组 nums 中的每个元素左边的最小值和右边的最大值。

// 创建两个长度为 n的数组leftMin 和rightMax，对于0≤i<n，leftMin[i] 表示 nums[0] 到 nums[i] 中的最小值，rightMax[i] 表示 nums[i] 到 nums[n−1] 中的最大值。


class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return false;
        }
        vector<int> leftMin(n);
        leftMin[0] = nums[0];
        for (int i = 1; i < n; i++) {
            leftMin[i] = min(leftMin[i - 1], nums[i]);
        }

        vector<int> rightMax(n);
        rightMax[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], nums[i]);
        }

        for (int i = 0; i < n; i++) {
            if (leftMin[i] < nums[i] && nums[i] < rightMax[i]) {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    Solution obj;
    vector<int> nums = {20,100,10,12,5,13};
    bool ret = obj.increasingTriplet(nums);
    // for (int i = 0; i < ret.size(); i++) {
    //     for (auto &w : ret[i]) {
    //         cout << w << " ";
    //     }
    //     cout << endl;
    // }
    system("pause");
    return 0;
}