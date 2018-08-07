/*
ID: andreip3
LANG: C++14
TASK: theme
*/
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5000 + 5;

int N, v[NMAX];
short dp[2][NMAX];

int main() {
    freopen("theme.in", "r", stdin);
    freopen("theme.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    v[N + 1] = 1000;

    int ans = 1;
    for (int i = N; i; -- i) {
        memset(dp[i & 1], 0, sizeof dp[i & 1]);
        for (int j = i - 1; j; -- j) {
            if (v[i] - v[i + 1] == v[j] - v[j + 1])
                dp[i & 1][j] = 1 + dp[(i + 1) & 1][j + 1];
            else
                dp[i & 1][j] = 1;
            ans = max(ans, min(i - j, (int)dp[i & 1][j]));
        }
    }

    if (ans < 5)
        ans = 0;
    cout << ans << '\n';
    return 0;
}
