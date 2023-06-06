// 给你一个 n x n 矩阵 matrix ，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。
// 请注意，它是 排序后 的第 k 小元素，而不是第 k 个 不同 的元素。

// 你必须找到一个内存复杂度优于 O(n2) 的解决方案。

//  

// 示例 1：

// 输入：matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
// 输出：13
// 解释：矩阵中的元素为 [1,5,9,10,11,12,13,13,15]，第 8 小元素是 13
// 示例 2：

// 输入：matrix = [[-5]], k = 1
// 输出：-5
//  

// 提示：

// n == matrix.length
// n == matrix[i].length
// 1 <= n <= 300
// -109 <= matrix[i][j] <= 109
// 题目数据 保证 matrix 中的所有行和列都按 非递减顺序 排列
// 1 <= k <= n2


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 算法一：采用优先队列，堆的算法，求K小。
// 这道题让求有序矩阵中第K小的元素，这道题的难点在于数组并不是蛇形有序的，意思是当前行的最后一个元素并不一定会小于下一行的首元素，
// 所以并不能直接定位第K小的元素，只能另辟蹊径。
// 先来看一种利用堆的方法，使用一个最大堆，然后遍历数组每一个元素，将其加入堆，根据最大堆的性质，大的元素会排到最前面，
// 然后我们看当前堆中的元素个数是否大于k，大于的话就将首元素去掉，循环结束后返回堆中的首元素即为所求:
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int> pq;
        // 默认使用最大堆，但是只保留k个元素，超过的数直接pop，则遍历一遍后，大的元素先进去，后面都被弹出来了。堆顶就是留下K个最大的元素
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                pq.emplace(matrix[i][j]);
                if (pq.size() > k) {
                    pq.pop();
                }
            }
        }
        return pq.top();
    }
};

// 算法二：二分查找，比较难理解，不采用。

int main()
{
    Solution obj;
    vector<vector<int>> matrix = {{1,5,9}, {10,11,13}, {12,13,15}};
    int ret = obj.kthSmallest(matrix, 8);

    system("pause");
    return 0;
}