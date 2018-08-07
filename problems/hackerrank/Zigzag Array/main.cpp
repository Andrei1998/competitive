#include <iostream>

using namespace std;

const int NMAX = 100 + 5;

int N;
int v[NMAX];
int dp[NMAX][NMAX];

int main() {
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    if (N <= 2) {
        cout << "0\n";
        return 0;
    }
    int ans = 2;
    for (int i = 1; i <= N; ++ i)
        for (int j = i + 1; j <= N; ++ j) {
            dp[i][j] = 2;
            for (int k = 1; k < i; ++ k)
                if (!(v[k] < v[i] && v[i] < v[j]) && !(v[k] > v[i] && v[i] > v[j]))
                dp[i][j] = max(dp[i][j], 1 + dp[k][i]);

            if (dp[i][j] > ans)
                ans = dp[i][j];
        }
    cout << N - ans << '\n';
    return 0;
}
