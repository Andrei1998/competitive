#include <iostream>
#include <string>
#include <vector>

#define lint long long int
using namespace std;

lint *****dp;

int cnt[4];

int main()
{
    int N, L;
    cin >> N >> L;

    string train;
    cin >> train;

    for (int i = 1; i <= N; ++ i) {
        string str;
        cin >> str;
        ++ cnt[2 * (str[0] - 'A') + (str[1] - 'A')];
    }

    dp = new lint****[cnt[0] + 1];
    for (int i = 0; i <= cnt[0]; ++ i) {
        dp[i] = new lint***[cnt[1] + 1];
        for (int j = 0; j <= cnt[1]; ++ j) {
            dp[i][j] = new lint**[cnt[2] + 1];
            for (int k = 0; k <= cnt[2]; ++ k) {
                dp[i][j][k] = new lint*[cnt[3] + 1];
                for (int l = 0; l <= cnt[3]; ++ l) {
                    dp[i][j][k][l] = new lint[2];
                    for (int t = 0; t < 2; ++ t)
                        dp[i][j][k][l][t] = 0;
                }
            }
        }
    }

    if (train[1] == 'A')
        dp[0][0][0][0][0] = 1;
    else
        dp[0][0][0][0][1] = 1;

    lint ans = 0;
    for (int i = 0; i <= cnt[0] && i <= L; ++ i)
        for (int j = 0; j <= cnt[1] && i + j <= L; ++ j)
            for (int k = 0; k <= cnt[2] && i + j + k <= L; ++ k)
                for (int l = 0; l <= cnt[3] && i + j + k + l <= L; ++ l)
                    if (dp[i][j][k][l][0] || dp[i][j][k][l][1]) {
                        if (i < cnt[0])
                            dp[i + 1][j][k][l][0] += dp[i][j][k][l][0];
                        if (j < cnt[1])
                            dp[i][j + 1][k][l][1] += dp[i][j][k][l][0];
                        if (k < cnt[2])
                            dp[i][j][k + 1][l][0] += dp[i][j][k][l][1];
                        if (l < cnt[3])
                            dp[i][j][k][l + 1][1] += dp[i][j][k][l][1];

                        if (i + j + k + l == L) {
                            if (train[0] == 'A')
                                ans += dp[i][j][k][l][0];
                            else
                                ans += dp[i][j][k][l][1];
                        }
                    }

    if (ans == 0)
        cout << "NO\n";
    else {
        cout << "YES\n";
        cout << ans << '\n';
    }
    return 0;
}
