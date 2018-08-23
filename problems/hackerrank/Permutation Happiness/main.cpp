#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000000 + 7;
const int NMAX = 3000 + 5;

int dp[NMAX][NMAX];

void add(int &where, int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}

int main() {
    dp[2][1] = 2;
    for (int i = 2; i < 3000; ++ i)
        for (int cnt = 0; cnt <= i; ++ cnt)
            if (dp[i][cnt]) {
                add(dp[i + 1][cnt], (2LL * cnt * dp[i][cnt]) % MOD);
                add(dp[i + 1][cnt + 1], (i + 1LL - 2 * cnt) * dp[i][cnt] % MOD);
            }

    int q = 0;
    cin >> q;

    while (q --) {
        int n, k;
        cin >> n >> k;
        k = n - k;

        int ans = 0;
        for (int i = 0; i <= k; ++ i)
            add(ans, dp[n][i]);
        cout << ans << '\n';
    }
    return 0;
}
