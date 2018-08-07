#include <iostream>

#define lint long long int
using namespace std;

int n;
int k;

const int NMAX = 1e6 + 5;
int c[NMAX];
lint dp[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    cin >> k >> n;

    if (k > n + 1) {
        cout << "-1\n";
        return 0;
    }

    for (int i = 1; i <= n; ++ i)
        cin >> c[i];

    if (k == 1)
        ++ k;
    if (k < n)
        n = k;

    dp[1] = c[1];
    dp[2] = c[1] + c[2];
    for (int i = 3; i <= n; ++ i)
        dp[i] = c[i] + max(1LL * c[i - 1], dp[i - 2]);

    if (k == n + 1)
        cout << dp[n] << '\n';
    else
        cout << max(1LL * c[n], dp[n - 1]) << '\n';
    return 0;
}
