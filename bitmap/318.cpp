// 给你一个字符串数组 words ，找出并返回 length(words[i]) * length(words[j]) 的最大值，并且这两个单词不含有公共字母。如果不存在这样的两个单词，返回 0 。

//  

// 示例 1：

// 输入：words = ["abcw","baz","foo","bar","xtfn","abcdef"]
// 输出：16 
// 解释：这两个单词为 "abcw", "xtfn"。
// 示例 2：

// 输入：words = ["a","ab","abc","d","cd","bcd","abcd"]
// 输出：4 
// 解释：这两个单词为 "ab", "cd"。
// 示例 3：

// 输入：words = ["a","aa","aaa","aaaa"]
// 输出：0 
// 解释：不存在这样的两个单词。
//  

// 提示：

// 2 <= words.length <= 1000
// 1 <= words[i].length <= 1000
// words[i] 仅包含小写字母



#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
s

// 如果检查两个单词是否有相同的字母，使用的是暴力的话，会超时，可以优化成使用位的操作
// 求两个单词的是否包含相同的字母，使用位&操作，可以优化
class Solution {
public:
    // int wordsHasCross(string &word1, string &word2) {
    //     int len1 = word1.length();
    //     int len2 = word2.length();
    //     for (int i = 0; i < len1; i++) {
    //         for (int j = 0; j < len2; j++) {
    //             if (word1[i] == word2[j]) {
    //                 return 1;
    //             }
    //         }
    //     }
    //     return 0;
    // }


    int maxProduct(vector<string>& words) {
        int len = words.size();
        vector< vector<int> > m;
        m.resize(len);
        for (int i = 0; i < len; i++) {
            m[i].resize(len);
        }

        // second init
        // vector<vector<int> > m(len, vector<int>(len, 0));
        vector<int> wl(len, 0);
        vector<int> wordmask(len, 0);
        for (int i = 0; i < len; i++) {
            wl[i] = words[i].length();
            for (int j = 0; j < wl[i]; j++) 
                wordmask[i] |= 1 << (words[i][j] - 'a');
        }

        int max = 0;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < i; j++) {
                // if (!wordsHasCross(words[i], words[j])) {
                if ((wordmask[i] & wordmask[j]) == 0) {
                    m[i][j] = wl[i] * wl[j];
                    max = max > m[i][j] ? max : m[i][j];
                    cout << "m[" << i << "][" << j << "]:" << m[i][j] << "max:" << max << endl;
                }
            }
        }
        return max;
    }
};



int main()
{
    Solution obj;
    vector<string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
    int ret = obj.maxProduct(words);

    system("pause");
    return 0;
}