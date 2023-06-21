// 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

// 说明：每次只能向下或者向右移动一步。

//  

// 示例 1：


// 输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
// 输出：7
// 解释：因为路径 1→3→1→1→1 的总和最小。
// 示例 2：

// 输入：grid = [[1,2,3],[4,5,6]]
// 输出：12
//  

// 提示：

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 200
// 0 <= grid[i][j] <= 200

// 思路解析，在求可行路径的数量、最小路径和的时候，比较容易想到的办法就是：搜索 和 动态归划，由于搜索一般适合于点比较少的情况，如果数据规模大的时候，考虑动态规划。
// 算法：动态规划：由于路径的方向只能是向下或向右，因此网格的第一行的每个元素只能从左上角元素开始向右移动到达，网格的第一列的每个元素只能从左上角元素开始向下移动到达，此时的路径是唯一的，因此每个元素对应的最小路径和即为对应的路径上的数字总和。
// 对于不在第一行和第一列的元素，可以从其上方相邻元素向下移动一步到达，或者从其左方相邻元素向右移动一步到达，元素对应的最小路径和等于其上方相邻元素与其左方相邻元素两者对应的最小路径和中的最小值加上当前元素的值。由于每个元素对应的最小路径和与其相邻元素对应的最小路径和有关，因此可以使用动态规划求解。

// 动态规划的两个重要因素。
// 1. 状态的设置（初始值）。创建二维数组 dp与原始网格的大小相同，dp[i][j] 表示走到点i,j 走到dp[m-1][n-1]的最短路径和
// 2. 状态转移方程。
//      当第一行时，只能从左边走过来，则初始值可求 dp[0][j] = dp[0][j-1] + grid[0][j];
//      当第一列时，只能从上面走过来，则初始值可求。
//      其它情况，则为：dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
// 3. 最后值在dp[m-1][n-1]上


#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) return 0;

        vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(),0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < grid[0].size(); i++) {
            dp[0][i] = dp[0][i - 1] + grid[0][i];
        }
        for (int i = 1; i < grid.size(); i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        for (int i = 1; i < grid.size(); i++) {
            for (int j = 1; j < grid[0].size(); j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        for (int i = 0; i < grid.size(); i++)
            print_vertor(dp[i]);

        return dp[grid.size() - 1][grid[0].size() - 1];
    }

    void print_vertor(vector<int> & nums)
    {
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << " ";
        }
        cout << endl;
    }
};




int main()
{
    vector<vector<int>> grid = {{1,3,1},{1,5,1}};
    Solution* obj = new Solution();
    int ret = obj->minPathSum(grid);
    cout << ret << endl;

    system("pause");
    return 0;
}