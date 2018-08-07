#include <iostream>
#include <map>

using namespace std;

const int MOD = 1000000000 + 7;
const int NMAX = 100000 + 5;
const int KMAX = 6;

map <int, int> freq;
int vect[NMAX];
int vectSz;

int dp[NMAX][KMAX * KMAX];

int main()
{
    ios_base :: sync_with_stdio(false);

    const int k = 3;

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        int val;
        cin >> val;
        ++ freq[val];
    }

    for (auto it: freq)
        vect[++ vectSz] = it.second;

    dp[0][0] = 1;
    for (int i = 0; i <= vectSz; ++ i)
        for (int j = 0; j <= k * (k - 1) / 2; ++ j) {
            dp[i + 1][j]     = (dp[i + 1][j]     + (1LL + vect[i + 1] * k) * dp[i][j]) % MOD;
            dp[i + 1][j]     = (dp[i + 1][j]     + ((1LL * j * vect[i + 1]) % MOD * vect[i + 1]) % MOD * dp[i][j]) % MOD;
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + (((k * (k - 1LL) / 2 - j) * vect[i + 1]) % MOD * vect[i + 1]) % MOD * dp[i][j]) % MOD;
        }

    cout << dp[vectSz][k * (k - 1) / 2] << '\n';
    return 0;
}
