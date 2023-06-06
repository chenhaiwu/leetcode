// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

//  

// 示例 1：

// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
// 示例 2：

// 输入：nums = [0,1]
// 输出：[[0,1],[1,0]]
// 示例 3：

// 输入：nums = [1]
// 输出：[[1]]
//  

// 提示：

// 1 <= nums.length <= 6
// -10 <= nums[i] <= 10
// nums 中的所有整数 互不相同




#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// algorithm
// 1. 这是一个全排列问题

class Solution {
public:
    void backtrace(vector<vector<int>> &res, vector<int> &outarray, int first, int len)
    {
        if (first == len) {
            res.emplace_back(outarray);
            return;
        }

        for (int i = first; i < len; i++) {
            swap(outarray[i], outarray[first]);
            backtrace(res, outarray, first + 1, len);
            swap(outarray[i], outarray[first]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        int len = nums.size();
        backtrace(res, nums, 0, len);
        return res;
    }
};



int main()
{
    Solution obj;
    vector<int> nums = {1,2,3};
    vector<vector<int>> ret = obj.permute(nums);
    for (int i = 0; i < ret.size(); i++) {
        for (auto &w : ret[i]) {
            cout << w << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}