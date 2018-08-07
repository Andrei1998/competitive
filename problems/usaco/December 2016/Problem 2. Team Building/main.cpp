#include <iostream>
#include <algorithm>
#include <cstdio>

//11:52
using namespace std;

const int NMAX = 1000 + 5;
const int KMAX = 10 + 2;
const int MOD = 1000000000 + 9;

int N, M, K;
int fj[NMAX];
int fp[NMAX];

int dp[NMAX][NMAX][KMAX];

int main()
{
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++ i)
        cin >> fj[i];
    for (int i = 1; i <= M; ++ i)
        cin >> fp[i];

    sort(fj + 1, fj + N + 1);
    sort(fp + 1, fp + M + 1);

    for (int i = 0; i <= N; ++ i)
        for (int j = 0; j <= M; ++ j)
            dp[i][j][0] = 1;

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= M; ++ j)
            for (int k = 1; k <= K; ++ k) {
                dp[i][j][k] = dp[i - 1][j][k] + dp[i][j - 1][k];
                if (dp[i][j][k] >= MOD)
                    dp[i][j][k] -= MOD;

                if (fj[i] > fp[j]) {
                    dp[i][j][k] += dp[i - 1][j - 1][k - 1];
                    if (dp[i][j][k] >= MOD)
                        dp[i][j][k] -= MOD;
                }

                dp[i][j][k] -= dp[i - 1][j - 1][k];
                if (dp[i][j][k] < 0)
                    dp[i][j][k] += MOD;
            }

    cout << dp[N][M][K] << '\n';
    return 0;
}
