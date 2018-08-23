#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;
lint L, R;

lint dp[20][20 * 10][2];

inline void upd(lint &where, const lint val) {
    if (val > where)
        where = val;
}

int N;
int nr[20];

int main()
{
    cin >> L >> R;

    lint r = R;
    while (r) {
        nr[++ N] = r % 10;
        r /= 10;
    }
    reverse(nr + 1, nr + N + 1);

    memset(dp, -1, sizeof dp);
    dp[0][0][0] = 0;
    lint pow10 = 1;
    for (int i = 0; i < N; ++ i)
        pow10 *= 10;

    for (int i = 0; i < N; ++ i) {
        pow10 /= 10;
        for (int s = 0; s <= 9 * i; ++ s) {
            if (dp[i][s][0] != -1)
                for (int c = 0; c <= nr[i + 1]; ++ c)
                    upd(dp[i + 1][s + c][c < nr[i + 1]], dp[i][s][0] + c * pow10);
            if (dp[i][s][1] != -1)
                for (int c = 0; c <= 9; ++ c)
                    upd(dp[i + 1][s + c][1], dp[i][s][1] + c * pow10);
        }
    }

    int ans = 0;
    for (int s = 0; s < 20 * 10; ++ s)
        if (dp[N][s][0] >= L || dp[N][s][1] >= L)
            ++ ans;
    cout << ans << '\n';
    return 0;
}
