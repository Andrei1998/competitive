/*
ID: andreip3
PROG: game1
LANG: C++11
*/
#include <fstream>
#include <algorithm>

using namespace std;

int v[105];
int dp[105][105];

int main() {
    ifstream cin("game1.in");
    ofstream cout("game1.out");

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++ i)
        cin >> v[i];

    for (int i = n; i; -- i)
        for (int j = i; j <= n; ++ j)
            dp[i][j] = max(v[i] - dp[i + 1][j], v[j] - dp[i][j - 1]);

    //Print
    int sum = 0;
    for (int i = 1; i <= n; ++ i)
        sum += v[i];
    int dif = dp[1][n];

    int a = (sum + dif) / 2;
    int b = (sum - dif) / 2;
    cout << a << ' ' << b << '\n';
    return 0;
}
