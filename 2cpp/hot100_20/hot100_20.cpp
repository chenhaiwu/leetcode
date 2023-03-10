#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution
{
    string s;

public:
    bool isValid(string s)
    {
        bool ret = true;
        this->s = s;
        stack<char> myStack;
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            char ch = s[i];
            if (ch == '(' || ch == '{' || ch == '[')
            {
                myStack.push(ch);
            }
            else
            {
                if (myStack.empty())
                {
                    ret = false;
                    break;
                }
                else
                {
                    char left = myStack.top();
                    myStack.pop();
                    if ((left == '(' && ch != ')') || (left == '[' && ch != ']') || (left == '{' && ch != '}'))
                    {
                        ret = false;
                        break;
                    }
                }
            }
        }
        if (!myStack.empty())
        {
            ret = false;
        }
        return ret;
    }
};

int main()
{
    Solution obj;
    bool ret = obj.isValid("()()");
    cout << ret << endl;
    ret = obj.isValid("{[]");
    cout << ret;

    system("pause");
    return 0;
}