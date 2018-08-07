/*
ID: andreip3
PROG: range
LANG: C++11
*/

#include <fstream>

using namespace std;

const int NMAX = 250 + 5;

int dp[NMAX][NMAX];
int cnt[NMAX];

int main()
{
    ifstream cin("range.in");
    ofstream cout("range.out");

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j) {
            char ch;
            cin >> ch;

            if (ch == '1')
                dp[i][j] = 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);

            ++ cnt[dp[i][j]];
        }

    for (int i = n; i; -- i)
        cnt[i] += cnt[i + 1];

    for (int i = 2; i <= n; ++ i)
        if (cnt[i])
            cout << i << ' ' << cnt[i] << '\n';
    return 0;
}
