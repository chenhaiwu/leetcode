// 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

// 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

// 给定两个整数数组 gas 和 cost ，如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。

//  

// 示例 1:

// 输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
// 输出: 3
// 解释:
// 从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
// 开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
// 开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
// 开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
// 开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
// 开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
// 因此，3 可为起始索引。
// 示例 2:

// 输入: gas = [2,3,4], cost = [3,4,3]
// 输出: -1
// 解释:
// 你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
// 我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
// 开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
// 开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
// 你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
// 因此，无论怎样，你都不可能绕环路行驶一周。
//  

// 提示:

// gas.length == n
// cost.length == n
// 1 <= n <= 105
// 0 <= gas[i], cost[i] <= 104


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// violation
// class Solution {
// public:
//     int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
//         int len = gas.size();

//         for (int i = 0; i < len; i++) {
//             int remain = gas[i];
//             int j = i;

//             while (remain - cost[j] > 0) {
//                 remain = remain + gas[(j + 1) % len] - cost[j];
//                 j = (j + 1) % len;
//                 if (j == i) {
//                     return i;
//                 }
//             }
//         }
//         return -1;
//     }
// };

// greedy 思路
// 1.如果总剩余油量小于0，即消耗大于补给，则没有机会行驶一圈，所以只需要一个变量sumFuel，就能够判断是否可以跑完一圈。
// 2.可以假设让车从索引为0处开始行驶，当总剩余油量小于0时，对应索引为n，那么从0到n的位置都不可能成为起点，以其中一个位置举例，从0行驶过去时油箱里存在剩余的油，经过这个位置，都不能通过n，如果从这个位置开始，油箱空空更难以通过n位置。这样就可以将起点假设为n+1，从n+1开始重新计算总剩余油量，到某一位置剩余油量小于0，则再更新起点。
// 3.通过1来判断是否能够跑一圈，能的话，我们再进行讨论，假设出发位置更新到倒数第二个，我们来讨论一下边界条件（由于题目是循环思想，而我们按照线性表来考虑，因此需要着重讨论右边界是否满足条件）：倒数第二个位置如果可以通过，最后一个位置一定能通过，如果倒数第二不能通过，新位置更新到倒数第一，那么该位置一定为起始点。
// 4.本题的贪心体现在局部区间排除不可能位置，整体区间去除所有的不可能位置，即得到最终的结果。
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = gas.size();
        int totalFuel = 0;
        int curFuel = 0;
        int start = 0;

        for (int i = 0; i < len; i++) {
            totalFuel += gas[i] - cost[i];
            curFuel += gas[i] - cost[i];

            if (curFuel < 0) {
                start = i + 1;
                curFuel = 0;
            }
        }
        if (totalFuel < 0) {
            return -1;
        }
        return start;
    }
};


int main()
{
    Solution obj;
    vector<int> gas = {1,2,3,4,5};
    vector<int> cost = {3,4,5,1,2};
    int ret = obj.canCompleteCircuit(gas, cost);

    system("pause");
    return 0;
}



