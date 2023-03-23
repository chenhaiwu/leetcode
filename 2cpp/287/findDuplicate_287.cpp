#include <iostream>
#include <vector>

using namespace std;

// 常规解法一：利用一个flags数组，做哈希，统计他的flag，如果记录为2，则表示已经有重复的。
/*
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        vector<int> flags(n + 1, 0);
        int ret;
        for (int i = 0; i < n; i++) {
            flags[nums[i]]++;
            if (flags[nums[i]] == 2) {
                ret = nums[i];
                break;
            }
        }
        return ret;
    }
};

*/

//
//方法三：快慢指针
//预备知识
// 本方法需要读者对 「Floyd 判圈算法」（又称龟兔赛跑算法）有所了解，它是一个检测链表是否有环的算法，LeetCode 中相关例题有 141. 环形链表，142. 环形链表 II。

// 思路和算法
// 我们对 \textit{nums}nums 数组建图，每个位置 ii 连一条 i\rightarrow \textit{nums}[i]i→nums[i] 的边。由于存在的重复的数字 \textit{target}target，因此 \textit{target}target 这个位置一定有起码两条指向它的边，因此整张图一定存在环，且我们要找到的 \textit{target}target 就是这个环的入口，那么整个问题就等价于 142. 环形链表 II。
// 我们先设置慢指针 \textit{slow}slow 和快指针 \textit{fast}fast ，
// 慢指针每次走一步，快指针每次走两步，根据「Floyd 判圈算法」两个指针在有环的情况下一定会相遇，
// 此时我们再将 \textit{slow}slow 放置起点 00，两个指针每次同时移动一步，相遇的点就是答案。

// 综上
// 1.数组中有一个重复的整数 <==> 链表中存在环
// 2.找到数组中的重复整数 <==> 找到链表的环入口

// 至此，问题转换为 142 题。那么针对此题，快、慢指针该如何走呢。根据上述数组转链表的映射关系，可推出
// 142 题中慢指针走一步 slow = slow.next ==> 本题 slow = nums[slow]
// 142 题中快指针走两步 fast = fast.next.next ==> 本题 fast = nums[nums[fast]]



class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};


int main()
{
    Solution obj;
    vector<int> v = {1,3,4,2,2};
    int ret = obj.findDuplicate(v);
    cout << ret << endl;

    system("pause");
    return 0;
}



/*
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。
假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。

 

示例 1：

输入：nums = [1,3,4,2,2]
输出：2
示例 2：

输入：nums = [3,1,3,4,2]
输出：3


提示：

1 <= n <= 10 5
nums.length == n + 1
1 <= nums[i] <= n
nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
 

进阶：

如何证明 nums 中至少存在一个重复的数字?
你可以设计一个线性级时间复杂度 O(n) 的解决方案吗？

*/