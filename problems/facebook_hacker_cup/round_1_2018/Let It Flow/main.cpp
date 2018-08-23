#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000000 + 7;

inline void add(int &where, int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}

int N;
string mat[3];

const int NMAX = 1000 + 5;
int dp[3][NMAX];

int solve() {
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;

    for (int j = 0; j < N; ++ j) {
        for (int i = 0; i < 3; ++ i) {
            if (dp[i][j] && mat[i][j] == '.') {
                for (int delta: {-1, 1}) {
                    int iprime = i + delta;
                    if (0 <= iprime && iprime < 3 && mat[iprime][j] == '.')
                        add(dp[iprime][j + 1], dp[i][j]);
                }
            }
        }
    }

    return dp[2][N];
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;
    for (int t = 1; t <= T; ++ t) {
        cin >> N;
        for (int i = 0; i < 3; ++ i)
            cin >> mat[i];
        cout << "Case #" << t << ": " << solve() << endl;
    }
    return 0;
}
