#include <bits/stdc++.h>

using namespace std;

const int NMAX = 256;
const int INF = 100000000;

int total, N;
int dp[NMAX][NMAX];
int l[NMAX];

int doRound(int nr) {
    int aux = (nr * 1000) / total;
    if (aux % 10 >= 5) {
        aux /= 10;
        ++ aux;
    }
    else
        aux /= 10;
    return aux;
}

void solve() {
    cin >> total >> N;

    int n = total;
    for (int i = 1; i <= N; ++ i) {
        cin >> l[i];
        n -= l[i];
    }
    while (n --) l[++ N] = 0;

    for (int i = 0; i <= N + 1; ++ i)
        for (int j = 0; j <= total + 1; ++ j)
            dp[i][j] = -INF;
    dp[0][0] = 0;

    int sum = 0;
    for (int i = 1; i <= N; ++ i) {
        sum += l[i];
        for (int cnt = sum; cnt <= total; ++ cnt)
            for (int k = l[i]; k <= cnt; ++ k) {
                assert(i >= 1 && cnt - k >= 0 && i < NMAX  && cnt - k < NMAX);
                dp[i][cnt] = max(dp[i][cnt], dp[i - 1][cnt - k] + doRound(k));
            }
    }
    cout << dp[N][total] << endl;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    //freopen("data.in", "r", stdin);

    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
