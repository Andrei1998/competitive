/*
ID: andreip3
LANG: C++14
TASK: bigbrn
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int NMAX = 1000 + 5;

int N;
bool mat[NMAX][NMAX];
int dp[NMAX][NMAX];

int main() {
    ifstream cin("bigbrn.in");
    ofstream cout("bigbrn.out");

    int T = 0;
    cin >> N >> T;
    while (T --) {
        int l, c;
        cin >> l >> c;
        mat[l][c] = 1;
    }

    int ans = 0;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            if (!mat[i][j]) {
                dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                ans = max(ans, dp[i][j]);
            }
    cout << ans << '\n';
    return 0;
}
