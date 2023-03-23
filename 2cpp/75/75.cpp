#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    // void sortColors(vector<int>& nums) {
    //     int v1 = 0, v2 = 0, v3 = 0;
    //     for (auto it = nums.begin(); it != nums.end(); it++) {
    //         if (*it == 0) v1++;
    //         else if (*it == 1) v2++;
    //         else v3++;
    //     }

    //     int v = v1 + v2 + v3;
    //     cout << v1 << v2 << v3 << v << endl;
    //     nums.clear();
    //     for (int i = 0; i < v; i++) {
    //         if (i < v1) {
    //             nums.push_back(0);
    //         } else if (i < v1 + v2) {
    //             nums.push_back(1);
    //         } else {
    //             nums.push_back(2);
    //         }
    //     }
    // }
    void sortColors(vector<int>& nums) {
        int v1 = 0, v2 = 0, v3 = 0;
        for (auto it = nums.begin(); it != nums.end(); it++) {
            if (*it == 0) v1++;
            else if (*it == 1) v2++;
            else v3++;
        }

        int v = v1 + v2 + v3;
        cout << v1 << v2 << v3 << v << endl;
        for (int i = 0; i < v; i++) {
            if (i < v1) {
                nums[i] = 0;
            } else if (i < v1 + v2) {
                nums[i] = 1;
            } else {
                nums[i] = 2;
            }
        }
    }
};

int main()
{
    Solution obj;
    vector<int> v = {2,0,2,1,1,0};
    obj.sortColors(v);

    system("pause");
    return 0;
}


