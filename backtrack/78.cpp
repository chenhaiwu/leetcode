// 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

// 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

//  

// 示例 1：

// 输入：nums = [1,2,3]
// 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
// 示例 2：

// 输入：nums = [0]
// 输出：[[],[0]]
//  

// 提示：

// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10
// nums 中的所有元素 互不相同


// 具体回溯算法参考90.cpp的解释，这里可以重复，更简单点

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;

        backtrack(nums, res, path, 0);

        return res;
    }
    void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& path, int start) {
        if (start > nums.size()) return;
        res.push_back(path);

        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtrack(nums, res, path, i + 1);
            path.pop_back();
        }
    }
};


void print_vertor(vector<int> & nums)
{
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

int main()
{
    Solution obj;
    vector<int> nums = {1,2,2};
    vector<vector<int>> res = obj.subsets(nums);

    for (int i = 0; i < res.size(); i++) {
        print_vertor(res[i]);
    }


    system("pause");
    return 0;
}