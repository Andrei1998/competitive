#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500 + 5;
const int STMAX = 3500 + 5;
const int INF = 1E9 + 15;

pair <int, int> p[STMAX];

int dp[2][NMAX][NMAX];
inline void updVal(int &where, int val) {
    if (val > where)
        where = val;
}

int main() {
    // freopen("data.in", "r", stdin);
    for (int i = 0; i < 2; ++ i)
        for (int j = 0; j < NMAX; ++ j)
            for (int k = 0; k < NMAX; ++ k)
                dp[i][j][k] = -INF;

    int cnt = 0;
    for (int i = 0; i <= 400; ++ i)
        for (int j = 0; j <= 400; ++ j)
            if (i * j <= 400 && 1 <= i + j)
                p[++ cnt] = make_pair(i, j);

    dp[0][0][0] = 0;
    for (int st = 0; st < cnt; ++ st) {
        const int x = p[st + 1].first;
        const int y = p[st + 1].second;

        for (int j = 0; j < NMAX; ++ j)
            for (int k = 0; k < NMAX; ++ k)
                dp[(st + 1) & 1][j][k] = -INF;

        for (int r = 0; r <= 500; ++ r)
            for (int b = 0; b <= 500; ++ b)
                if (dp[st & 1][r][b] >= 0) {
                    updVal(dp[(st + 1) & 1][r][b], dp[st & 1][r][b]);
                    if (r + x <= 500 && b + y <= 500)
                        updVal(dp[(st + 1) & 1][r + x][b + y], dp[st & 1][r][b] + 1);
                }
    }

    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i) {
        int R, B;
        cin >> R >> B;
        cout << "Case #" << i << ": " << dp[cnt & 1][R][B] << '\n';
    }
    return 0;
}
