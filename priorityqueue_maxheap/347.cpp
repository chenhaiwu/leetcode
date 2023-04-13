// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

//  

// 示例 1:

// 输入: nums = [1,1,1,2,2,3], k = 2
// 输出: [1,2]
// 示例 2:

// 输入: nums = [1], k = 1
// 输出: [1]
//  

// 提示：

// 1 <= nums.length <= 105
// k 的取值范围是 [1, 数组中不相同的元素的个数]
// 题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
//  

// 进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/top-k-frequent-elements
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;


// algorithm
// 1. 先使用hash表进行每个数字出现的次数key: number; value: counts
// 2. 再求一个数组中前面K个最大数，要求nlogn，这个就不能直接使用快排都可能超时，因此使用优先队列+最大堆的算法
// 本题的关键是：求数组的前K个最大值, 前K个最大值元素，使用最小堆
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        unordered_map<int, int> occur_map;
        // for (auto it = nums.begin(); it != nums.end(); it++)
        //     occur[*it]++;

        for (auto& v : nums)
            occur_map[v]++;

        //2.利用优先队列，将出现次数排序
        //自定义优先队列的比较方式，小顶堆
        struct myComparison
        {
            bool operator() (pair<int, int> &p1, pair<int, int> &p2) {
                return p1.second > p2.second;   // 小顶堆是大于号
            }
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, myComparison> pq;

        for (auto & a : occur_map) {
            pq.push(a);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        // 导出结果
        vector<int> ret;
        while (!pq.empty()) {
            ret.push_back(pq.top().first);
            pq.pop();
        }
        return ret;
    }
};



int main()
{
    Solution obj;
    vector<int> nums = {1,1,1,2,2,3};
    vector<int> ret = obj.topKFrequent(nums, 2);

    system("pause");
    return 0;
}