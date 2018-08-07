#include <iostream>
#include <algorithm>

using namespace std;

typedef long long int lint;

const int NMAX = 2000 + 5;

int N, x;
int a[NMAX];

int dp[NMAX][NMAX];

int main()
{
    cin >> N >> x;

    lint ans = 0;
    for (int i = 0; i < N; ++ i) {
        cin >> a[i];
        ans += a[i];
        dp[0][i] = a[i];
    }

    for (int rots = 1; rots < N; ++ rots) {
        lint cost = 1LL * rots * x;
        for (int i = 0; i < N; ++ i) {
            dp[rots][i] = min(a[i], dp[rots - 1][(i + N - 1) % N]);
            cost += dp[rots][i];
        }

        if (cost < ans)
            ans = cost;
    }

    cout << ans << '\n';
    return 0;
}
