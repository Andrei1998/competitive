#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000000 + 7;
inline void add(int &where, const int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}

const int NMAX = 3000 + 5;
int N, M;
int dp[NMAX][NMAX];

int main() {
    cin >> N >> M;
    for (int n = 0; n <= N; ++n) {
        for (int m = 0; m <= M; ++m) {
            if (n == 0 || m == 0) {
                dp[n][m] = 1;
                continue;
            }
            dp[n][m] = dp[n - 1][m]; // No tents on the first row
            add(dp[n][m], (4LL * m * dp[n - 1][m - 1]) % MOD); // A single tent on the first row and none on its column
            if (n >= 2)
                add(dp[n][m], (m * (n - 1LL) * dp[n - 2][m - 1]) % MOD); // A single tent on the first row and one more on its column
            if (m >= 2)
                add(dp[n][m], (m * (m - 1LL) / 2 * dp[n - 1][m - 2]) % MOD); // Two tents on the first row and none on their columns
        }
    }
    cout << (dp[N][M] + MOD - 1) % MOD << endl;
    return 0;
}

