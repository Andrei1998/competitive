#include <iostream>

using namespace std;

const int KMAX = 10;
const int NMAX = 100 + 5;

int MOD, N, K;

#define lsb(x) ((x) & (-(x)))
int forbidden[1 << KMAX];

int dp[NMAX][1 << KMAX];

int main()
{
    cin >> MOD >> N >> K;
    N /= 2;

    int M = 0;
    cin >> M;

    while (M --) {
        int a, b;
        cin >> a >> b;
        -- a, -- b;
        forbidden[1 << a] |= (1 << b);
    }

    for (int i = 1; i < (1 << K); ++ i)
        forbidden[i] = forbidden[lsb(i)] | forbidden[i ^ lsb(i)];

    //DP
    for (int mask = 0; mask < (1 << K); ++ mask)
        dp[0][mask] = 1;

    for (int l = 1; l <= N; ++ l)
        for (int mask = 0; mask < (1 << K); ++ mask) {
            long long int val = 0;
            for (int dish = 0; dish < 10; ++ dish)
                if (!(forbidden[mask] & (1 << dish)))
                    for (int cnt = 0; cnt < l; ++ cnt)
                        val += dp[cnt][mask | (1 << dish)] * dp[l - cnt - 1][mask];
            dp[l][mask] = val % MOD;
        }
    cout << dp[N][0] << '\n';
    return 0;
}
