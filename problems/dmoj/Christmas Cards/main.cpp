#include <iostream>

#define lint long long int
using namespace std;

const lint INF = 1LL << 60;

int N;
int c[5005];
int d[5005];

lint dp[5005][5005];

inline void upd(lint &dp, lint val) {
    if (val < dp)
        dp = val;
}

int main()
{
    for (int i = 0; i < 5005; ++ i)
        for (int j = 0; j < 5005; ++ j)
            dp[i][j] = INF;

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> c[i] >> d[i];

    dp[1][1] = 0;
    for (int i = 1; i <= N; ++ i)
        for (int j = i; j <= N; ++ j)
            if (dp[i][j] < INF) {
                upd(dp[i + 1][j], dp[i][j]);
                upd(dp[i + 1][min(N, j + d[i])], dp[i][j] + c[i]);
            }

    cout << dp[N][N] << '\n';
    return 0;
}
