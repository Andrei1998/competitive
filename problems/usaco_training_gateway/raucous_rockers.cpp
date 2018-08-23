/*
ID: andreip3
LANG: C++14
TASK: rockers
*/
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 20 + 5;

int N, T, M;
int v[NMAX];

int dp[NMAX][NMAX][NMAX];

inline void upd(int &where, int val) {
    if (val > where)
        where = val;
}

int main() {
    freopen("rockers.in", "r", stdin);
    freopen("rockers.out", "w", stdout);

    cin >> N >> T >> M;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];

    for (int songs = 0; songs <= N; ++ songs)
        for (int disk = 1; disk <= M; ++ disk)
            for (int used = 0; used <= 20; ++ used) {
                // Ignore song
                upd(dp[songs + 1][disk][used], dp[songs][disk][used]);
                // Ignore disk
                upd(dp[songs][disk + 1][0], dp[songs][disk][used]);
                // Place song
                if (songs + 1 <= N && used + v[songs + 1] <= T)
                    upd(dp[songs + 1][disk][used + v[songs + 1]], dp[songs][disk][used] + 1);
            }

    cout << dp[N][M + 1][0] << '\n';
    return 0;
}
