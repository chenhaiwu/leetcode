// 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

// 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。

//  

// 示例 1：

// 输入：nums = [1,2,2]
// 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
// 示例 2：

// 输入：nums = [0]
// 输出：[[],[0]]
//  

// 提示：

// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10


// 回溯法
// 一般情况下，看到题目要求「所有可能的结果」，而不是「结果的个数」，我们就知道需要暴力搜索所有的可行解了，可以用「回溯法」。
// 「回溯法」实际上一个类似枚举的搜索尝试过程，主要是在搜索尝试过程中寻找问题的解，当发现已不满足求解条件时，就「回溯」返回，尝试别的路径。
// 回溯法是一种算法思想，而递归是一种编程方法，回溯法可以用递归来实现。
// 回溯法的整体思路是：搜索每一条路，每次回溯是对具体的一条路径而言的。对当前搜索路径下的的未探索区域进行搜索，则可能有两种情况：
// 当前未搜索区域满足结束条件，则保存当前路径并退出当前搜索；
// 当前未搜索区域需要继续搜索，则遍历当前所有可能的选择：如果该选择符合要求，则把当前选择加入当前的搜索路径中，并继续搜索新的未探索区域。
// 上面说的未搜索区域是指搜索某条路径时的未搜索区域，并不是全局的未搜索区域。
// 回溯法搜所有可行解的模板一般是这样的：


// res = []
// path = []

// def backtrack(未探索区域, res, path):
//     if path 满足条件:
//         res.add(path) # 深度拷贝
//         # return  # 如果不用继续搜索需要 return
//     for 选择 in 未探索区域当前可能的选择:
//         if 当前选择符合要求:
//             path.add(当前选择)
//             backtrack(新的未探索区域, res, path)
//             path.pop()

// backtrack 的含义是：未探索区域中到达结束条件的所有可能路径，path 变量是保存的是一条路径，res 变量保存的是所有搜索到的路径。所以当「未探索区域满足结束条件」时，需要把 path 放到结果 res 中。
// path.pop() 是啥意思呢？它是编程实现上的一个要求，即我们从始至终只用了一个变量 path，所以当对 path 增加一个选择并 backtrack 之后，需要清除当前的选择，防止影响其他路径的搜索。

// 提醒
// 下面的正规写法对应了全局共享一个 path 的写法，简化写法是每次新建 path。这里是一个容易出错的细节。

// 正规写法中全局共享一个 path，每次添加到 res 中，需要深度拷贝。python中是需要 copy.deepcopy(path) ；C++ 的 vector 的 push_back() 函数，本身就是深度拷贝。另外由于是全局的 path，因此每次需要对 path 进行 push 和 pop 操作，
// 简化写法的 Python 解法在每次搜索位置区域的时候，使用的是产生一个新数组 path + [s[:i]] ，这样好处是方便：不同的路径使用的是不同的 path，因此不需要 path.pop() 操作；而且 res.append(path) 的时候不用深度拷贝一遍 path。
// 一：求不含重复元素的数组的子集
// 正规写法
// 对于 78. 子集 而言，找出没有重复数字的数组所有子集，按照模板，我们的思路应该是这样的：

// 未探索区域：剩余的未搜索的数组 nums[index: N - 1] ；
// 每个 path 是否满足题目的条件： 任何一个 path 都是子集，都满足条件，都要放到 res 中 ;
// 当前 path 满足条件时，是否继续搜索：是的，找到 nums[0:index-1] 中的子集之后， nums[index] 添加到老的 path 中会形成新的子集。
// 未探索区域当前可能的选择：每次选择可以选取 s 的 1 个字符，即 nums[index] ；
// 当前选择符合要求：任何 nums[index] 都是符合要求的，直接放到 path 中；
// 新的未探索区域：nums 在 index 之后的剩余字符串， nums[index + 1 : N - 1] 。

// 如果你能理解上面的回溯法，那么包含重复元素的数组的子集，只不过一个小的改进。

// 比如说求 nums = [1,2,2] 的子集，那么对于子集 [1,2] 是选择了第一个 2，那么就不能再选第二个 2 来构成 [1,2] 了。所以，此时的改动点，就是先排序，每个元素 nums[i] 添加到 path 之前，判断一下 nums[i] 是否等于 nums[i - 1] ，如果相等就不添加到 path 中。


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;

        sort(nums.begin(), nums.end());
        backtrack(nums, res, path, 0);

        return res;

    }
    void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& path, int start) {
        if (start > nums.size()) return;

        res.push_back(path);
        for (int i = start; i < nums.size(); i++) {
            if (i != start && nums[i] == nums[i - 1]) continue;
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
    vector<vector<int>> res = obj.subsetsWithDup(nums);

    for (int i = 0; i < res.size(); i++) {
        print_vertor(res[i]);
    }


    system("pause");
    return 0;
}