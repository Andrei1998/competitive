#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int NMAX = 2000 + 5;
lint sum[NMAX];

int N, A, B;

bool dp[NMAX][NMAX]; //dp[i][j] = first i sculptures, j sequences
int dp2[NMAX]; //dp[i] = first i sculptures (for A = 1)

lint ans;
bool works() {
    if (A > 1) {
        dp[0][0] = true;
        for (int i = 1; i <= N; ++ i) {
            for (int j = 1; j <= i && j <= B; ++ j) {
                dp[i][j] = false;
                for (int k = 1; k <= i; ++ k)
                    if (!((sum[i] - sum[k - 1]) & (~ans)))
                        if (dp[k - 1][j - 1]) {
                            dp[i][j] = true;
                            break;
                        }
            }
        }

        for (int j = A; j <= B; ++ j)
            if (dp[N][j])
                return true;
        return false;
    }
    else {
        dp2[0] = 0;
        for (int i = 1; i <= N; ++ i) {
            dp2[i] = N + 1;
            for (int k = 1; k <= i; ++ k)
                if (!((sum[i] - sum[k - 1]) & (~ans)))
                    dp2[i] = min(dp2[i], 1 + dp2[k - 1]);
        }

        return dp2[N] <= B;
    }
}

int main()
{
    cin >> N >> A >> B;

    for (int i = 1; i <= N; ++ i) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }

    ans = (1LL << 41) - 1;
    for (int bit = 40; bit >= 0; -- bit) {
        ans ^= (1LL << bit);
        if (!works())
            ans ^= (1LL << bit);
    }

    cout << ans << '\n';
    return 0;
}
