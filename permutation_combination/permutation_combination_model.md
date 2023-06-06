排列组合
排列组合概念首先需要理解清楚，组合是没有顺序的，例如[1,2],[2,1]是同一种组合。而排列是有顺序的，例如[1,2],[2,1]是同俩种不同的排列。由此可见排列与组合有很多相似的地方，但是也有些微小的差距，所以在代码实现上也会有些不同。

组合
通常可以用以下代码模板进行求组合问题：


    vector<int> path;
    vector<vector<int>> result;
    void backtracking(int n, int k, int startIndex) {
        if (path.size() == k) {
            result.emplace_back(path);
            return;
        }
        for (int i = startIndex; i <= (n - (k - path.size()) + 1); ++i) {
            path.emplace_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }

排列
和组合的区别在于，此时我们需要使用used数组防止集合中出现重复元素（即树枝去重），而且每一个for循环是从0开始的即从数组第一个元素开始进行遍历的，因为我们排列是有顺序，每一次需要从头开始去寻找新的符合条件的集合。
通常可以用以下代码模板进行求排列问题：


    vector<int> path;
    vector<vector<int>> result;
    void backTracking(vector<int> &nums, vector<bool> &used) {
        if (path.size() == nums.size()) {
            result.emplace_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i] == true) continue;
            used[i] = true;
            path.emplace_back(nums[i]);
            backTracking(nums, used);
            used[i] = false;
            path.pop_back();
        }
    }

