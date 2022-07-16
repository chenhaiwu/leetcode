#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int i, j, k, n, t;
    vector<int> a;
    queue<int> b;
    map<int, int> c;

    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> t;
        auto search = c.find(t);
        if (search == c.end()) {
            c[t] = 1;
            cout << "not find:" << t << endl;
        } else {
            c[t]++;
            cout << "find :" << t << ": count:" << c[t] << endl;
        }
    }
    for (auto iter = c.begin(); iter != c.end(); iter++) {
        cout << iter->first << ":" << iter->second << " ";
    }

    for (auto iter : c) {
        cout << iter.first << ":" << iter.second << endl;
    }
    

    return 0;
}