/* 01背包  优化前后 */

// f[i][j] 表示空间容量为j时，取到i件物品时。所获得的最大价值
#include <iostream>
using namespace std;

const int N = 1e3 + 10;
int v[N], w[N];
int f[N][N];

int main() {
    int N, V;
    cin >> N >> V;
    for (int i = 1; i <= N; i++)    cin >> v[i] >> w[i];
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= V; j++) {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])  f[i][j] = max(f[i - 1][j], f[i - 1][j - v[i]] + w[i]);
        }
    }
    cout << f[N][V] << endl;
    return 0;
}

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e3 + 10;
int v[N], w[N];
int f[N];

int main() {
    int N, V;
    cin >> N >> V;
    for (int i = 1; i <= N; i++)    cin >> v[i] >> w[i];
    for (int i = 1; i <= N; i++) 
        for (int j = V; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);
    cout << f[V] << endl;
    return 0;
}

/* 完全背包  优化前后 */
#include <iostream>
using namespace std;

const int maxn = 1e3 + 10;
int v[maxn], w[maxn];
int f[maxn][maxn];

int main() {
    int N, V;
    cin >> N >> V;
    for (int i = 1; i <= N; i++)    cin >> v[i] >> w[i];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= V; j++) {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])   f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
        }
    cout << f[N][V] << endl;
    return 0;
}

#include <iostream>
using namespace std;

const int N = 1e3 + 10;
int v[N], w[N];
int f[N];

int main() {
    int n, V;
    cin >> n >> V;
    for (int i = 1; i <= n; i++)    cin >> v[i] >> w[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= V; j++) 
            if (j >= v[i])  f[j] = max(f[j], f[j - v[i]] + w[i]);
    cout << f[V] << endl;
    return 0;
}

/* 多重背包 数据范围小不用优化 优化前后 */
#include <iostream>
using namespace std;

const int N = 1e2 + 10;
int v[N], w[N], s[N];
int f[N];

int main() {
    int n, V;
    cin >> n >> V;
    for (int i = 1; i <= n; i++)    cin >> v[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; i++)
        for (int j = V; j >= 0; j--)
            for (int k = 1; k <= s[i] && k * v[i] <= j; k++)
                f[j] = max(f[j], f[j - k * v[i]] + k * w[i]);
    cout << f[V] << endl;
    return 0;
}


#include <iostream>
using namespace std;

const int N = 25000;
int v[N], w[N];
int f[N];

int main() {
    int n, V;
    cin >> n >> V;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        int k = 1;
        while (k <= s) {
            cnt++;
            v[cnt] = a * k;
            w[cnt] = b * k;
            s -= k;
            k *= 2;
        }
        if (s > 0) {
            cnt++;
            v[cnt] = a * s;
            w[cnt] = b * s;
        }
    }
    n = cnt;            //因为这句话WA了
    for (int i = 1; i <= n; i++)
        for (int j = V; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);
    cout << f[V] << endl;            
}
