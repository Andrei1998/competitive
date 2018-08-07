#include <iostream>
#include <cstring>

using namespace std;

const int NMAX = 3000 + 5;
const int MMAX = 3000 + 5;
const int MOD = 1000000000 + 7;

int dp[2][2 * NMAX][2];

void upd(int &where, int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}

int main()
{
    int N, M;
    cin >> N >> M;

    M *= 2;
    int L = 2 * N + 1;

    for (int i = 1; i <= L; i += 2)
        dp[0][i][i <= 2] = 1;
    for (int i = 0; i < M; ++ i) {
        memset(dp[(i + 1) & 1], 0, sizeof(dp[0]));
        for (int j = 1; j <= L; ++ j) {
            upd(dp[(i + 1) & 1][j - 1][(j - 1 <= 2)], dp[i & 1][j][0]);
            upd(dp[(i + 1) & 1][j + 1][0], dp[i & 1][j][0]);
            upd(dp[(i + 1) & 1][j - 1][1], dp[i & 1][j][1]);
            upd(dp[(i + 1) & 1][j + 1][1], dp[i & 1][j][1]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= L; ++ i)
        upd(ans, dp[M & 1][i][1]);
    cout << ans << '\n';
    return 0;
}
