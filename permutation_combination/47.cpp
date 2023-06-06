// 给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。

//  

// 示例 1：

// 输入：nums = [1,1,2]
// 输出：
// [[1,1,2],
//  [1,2,1],
//  [2,1,1]]
// 示例 2：

// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]




// 这道题目和46.全排列的区别在与给定一个可包含重复数字的序列，要返回所有不重复的全排列。
// 这里又涉及到去重了。
// 在40.组合总和II 、90.子集II我们分别详细讲解了组合问题和子集问题如何去重。
// 那么排列问题其实也是一样的套路。
// 还要强调的是去重一定要对元素进行排序，这样我们才方便通过相邻的节点来判断是否重复使用了。
// 我以示例中的 [1,1,2]为例 （为了方便举例，已经排序）抽象为一棵树，去重过程如图：

// 图中我们对同一树层，前一位（也就是nums[i-1]）如果使用过，那么就进行去重。
// 一般来说：组合问题和排列问题是在树形结构的叶子节点上收集结果，而子集问题就是取树上所有节点的结果。
// 在46.全排列中已经详细讲解了排列问题的写法，在40.组合总和II 、90.子集II中详细讲解了去重的写法，所以这次我就不用回溯三部曲分析了，直接给出代码，如下：


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// algorithm
// 1. 这是一个全排列问题， 不过更难一点的是要求去重
// 2. 去重的话，一定要先排序，可以调用库函数 sort完成排序过程
// 3. 去重的逻辑核心如下：

class Solution {
private:
    vector<int> path;
public:
    void backtrace(vector<vector<int>>& res, vector<int>& nums, vector<int> &used, vector<int>& path, int first, int len)
    {
        if (first == len) {
            res.emplace_back(path);
            return;
        }

        for (int i = 0; i < len; i++) {
            if (used[i] || (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])) {
                continue;
            }

            used[i] = 1;
            path.emplace_back(nums[i]);
            backtrace(res, nums, used, path, first + 1, len);
            used[i] = 0;
            path.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int len = nums.size();
        vector<int> used(len, 0);
        // used.resize(len);
        // used.clear();
        vector<int> path;
        // path.resize(len);
        // path.clear();
        sort(nums.begin(), nums.end());

        vector<vector<int>> res;
        backtrace(res, nums, used, path, 0, len);
        return res;
    }
};

// class Solution {
//     vector<int> vis;

// public:
//     void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
//         if (idx == nums.size()) {
//             ans.emplace_back(perm);
//             return;
//         }
//         for (int i = 0; i < (int)nums.size(); ++i) {
//             if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
//                 continue;
//             }
//             perm.emplace_back(nums[i]);
//             vis[i] = 1;
//             backtrack(nums, ans, idx + 1, perm);
//             vis[i] = 0;
//             perm.pop_back();
//         }
//     }

//     vector<vector<int>> permuteUnique(vector<int>& nums) {
//         vector<vector<int>> ans;
//         vector<int> perm;
//         vis.resize(nums.size());
//         sort(nums.begin(), nums.end());
//         backtrack(nums, ans, 0, perm);
//         return ans;
//     }
// };

int main()
{
    Solution obj;
    vector<int> nums = {1,2,1};
    vector<vector<int>> ret = obj.permuteUnique(nums);
    for (int i = 0; i < ret.size(); i++) {
        for (auto &w : ret[i]) {
            cout << w << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}