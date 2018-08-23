#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500 + 5;
const int INF = 2E9 + 15;
typedef long long int lint;

int a, b, n, m;
int mat[NMAX][NMAX];
int v[NMAX];
int l[NMAX], r[NMAX];

static inline lint getVolume(int minimum, int area) {
    if (!minimum)
        return 0;
    return area * ((1LL * minimum * n * m - 1) / (n * m - area));
}

lint ans;
stack <int> stk;

void solve(int width) {
    while (!stk.empty()) stk.pop();
    stk.push(0);
    for (int i = 1; i <= m; ++ i) {
        while (!stk.empty() && v[stk.top()] >= v[i])
            stk.pop();
        l[i] = stk.top();
        stk.push(i);
    }
    while (!stk.empty()) stk.pop();
    stk.push(m + 1);
    for (int i = m; i; -- i) {
        while (!stk.empty() && v[stk.top()] >= v[i])
            stk.pop();
        r[i] = stk.top();
        stk.push(i);
    }

    for (int i = 1; i <= m; ++ i) {
        const int L = min(r[i] - l[i] - 1, b);
        ans = max(ans, getVolume(v[i], width * L));
    }
}

void slv() {
    v[0] = v[m + 1] = -INF;
    for (int l1 = 1; l1 <= n; ++ l1) {
        for (int i = 1; i <= m; ++ i)
            v[i] = mat[l1][i];
        for (int l2 = l1; l2 <= n && l2 - l1 + 1 <= a; ++ l2) {
            for (int i = 1; i <= m; ++ i)
                v[i] = min(v[i], mat[l2][i]);
            solve(l2 - l1 + 1);
        }
    }
}

int main() {
    //freopen("data.in", "r", stdin);

    cin >> a >> b >> n >> m;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            cin >> mat[i][j];

    slv();
    swap(a, b);
    slv();

    cout << ans << '\n';
    return 0;
}
