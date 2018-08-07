#include <iostream>

using namespace std;

const int NMAX = 100 + 5;

int N, W;
int w[NMAX];
int v[NMAX];

int dp[NMAX][NMAX][3 * NMAX];

void upd(int &where, int val) {
    if (val > where)
        where = val;
}

int main()
{
    cin >> N >> W;
    for (int i = 1; i <= N; ++ i)
        cin >> w[i] >> v[i];

    int quota = w[1];
    for (int i = 1; i <= N; ++ i)
        w[i] -= quota;

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j <= i; ++ j)
            for (int g = 0; g <= 3 * j; ++ g) {
                upd(dp[i + 1][j][g], dp[i][j][g]);
                upd(dp[i + 1][j + 1][g + w[i + 1]], dp[i][j][g] + v[i + 1]);
            }

    int ans = 0;
    for (int j = 0; j <= N; ++ j)
        for (int g = 0; g <= 3 * j; ++ g)
            if (1LL * quota * j + g <= W)
                ans = max(ans, dp[N][j][g]);

    cout << ans << '\n';
    return 0;
}
