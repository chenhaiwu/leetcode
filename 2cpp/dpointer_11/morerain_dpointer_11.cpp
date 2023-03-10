#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0;
        int r = height.size() - 1;
        int ans = 0;
        while (l < r) {
            int w = r - l;
            int h = min(height[l], height[r]);
            ans = max(ans, w * h);
            if (height[l] <= height[r]) {
                l++;
            } else {
                r--;
            }
        }
        return ans;
    }
};

int main()
{
    Solution obj;
    vector<int> v = {1,8,6,2,5,4,8,3,7};
    int ret = obj.maxArea(v);
    cout << ret << endl;

    system("pause");
    return 0;
}