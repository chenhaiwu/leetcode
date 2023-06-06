// 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

//  

// 示例 1:

// 输入: nums = [1,2,3,4,5,6,7], k = 3
// 输出: [5,6,7,1,2,3,4]
// 解释:
// 向右轮转 1 步: [7,1,2,3,4,5,6]
// 向右轮转 2 步: [6,7,1,2,3,4,5]
// 向右轮转 3 步: [5,6,7,1,2,3,4]
// 示例 2:

// 输入：nums = [-1,-100,3,99], k = 2
// 输出：[3,99,-1,-100]
// 解释: 
// 向右轮转 1 步: [99,-1,-100,3]
// 向右轮转 2 步: [3,99,-1,-100]
//  

// 提示：

// 1 <= nums.length <= 105
// -231 <= nums[i] <= 231 - 1
// 0 <= k <= 105



#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> tmpnums(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            tmpnums[(i + k) % n] = nums[i];
        }
        nums.assign(tmpnums.begin(), tmpnums.end());
    }
};

int main()
{
    Solution obj;
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 2;
    obj.rotate(nums, k);
    for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << " ";
    }
    system("pause");
    return 0;
}