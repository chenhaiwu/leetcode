#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

/* 优化代码前 */
// map<int, string> myKeyStr = {
//     {2, "abc"},
//     {3, "def"},
//     {4, "ghi"},
//     {5, "jkl"},
//     {6, "mno"},
//     {7, "pqrs"},
//     {8, "tuv"},
//     {9, "wxyz"}};

// class Solution
// {
// public:
//     vector<string> letterCombinations(string digits)
//     {
//         vector<string> letters;
//         queue<string> q;
//         int digitLen = digits.length();
//         if (digits.empty())
//             return letters;
//         // 1. push first layer
//         int idx = digits[0] - '0';
//         for (int i = 0; i < myKeyStr[idx].length(); i++)
//         {
//             string s;
//             s.push_back(myKeyStr[idx][i]);
//             q.push(s);
//         }
//         while (q.size())
//         {
//             if (q.front().length() >= digitLen)
//             {
//                 break;
//             }
//             string s = q.front();
//             q.pop();
//             int currentID = s.length();
//             idx = digits[currentID] - '0';
//             for (int i = 0; i < myKeyStr[idx].length(); i++)
//             {
//                 string new_str = s;
//                 new_str.push_back(myKeyStr[idx][i]);
//                 q.push(new_str);
//             }
//         }
//         while (!q.empty())
//         {
//             letters.push_back(q.front());
//             q.pop();
//         }
//         return letters;
//     }
// };

class Solution
{
    map<char, string> map_dit2str;
    string digits;
    vector<string> result;

public:
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
            return result;

        this->digits = digits;
        map_dit2str = {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}};

        queue<string> q;
        // 1. push first layer
        for (auto a : map_dit2str[digits[0]])
        {
            string s = "";
            q.push(s + a);
        }
        int digitLen = digits.length();
        while (q.size())
        {
            if (q.front().length() >= digitLen)
            {
                break;
            }
            string s = q.front();
            q.pop();
            int currentID = s.length();
            for (auto a : map_dit2str[digits[currentID]])
            {
                string new_str = s + a;
                q.push(new_str);
            }
        }
        while (!q.empty())
        {
            result.push_back(q.front());
            q.pop();
        }
        return result;
    }
};

main()
{
    int i, j, k, n, t;
    vector<string> sums;

    string digits = "23";

    cout << digits << endl;
    Solution obj;
    sums = obj.letterCombinations(digits);

    for (auto a : sums)
    {
        cout << a;
    }

    system("Pause");
    return 0;
}

/*
BFS 很精简
*/
// #include <vector>
// #include <string>
// #include <iostream>
// #include <unordered_map>
// using namespace std;

// class Solution
// {
//     vector<string> result;
//     string digits;
//     unordered_map<char, string> store;

// public:
//     vector<string> letterCombinations(string digits)
//     {
//         if (digits.empty())
//         {
//             return result;
//         }
//         this->digits = digits;
//         //储存字典
//         store = unordered_map<char, string>{
//             {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
//         dfs("", 0);
//         return result;
//     }

//     void dfs(string resultStr, int index)
//     {
//         int digitsSize = int(this->digits.size());
//         if (digitsSize == index)
//         {
//             result.push_back(resultStr);
//             return;
//         }
//         char targetChar = this->digits[index];
//         string targetStr = store[targetChar];
//         for (auto tmpChar : targetStr)
//         {
//             dfs(resultStr + tmpChar, index + 1); //递归调用
//         }
//         return;
//     }
// };
