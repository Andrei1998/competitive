#include <iostream>
#include <queue>

using namespace std;

const int MOD = 1000000000 + 7;
const int NMAX = 2000 + 5;

int p[NMAX];
int degree[NMAX];

queue <int> q;

int dp[NMAX];

int main()
{
    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        cin >> p[i];
        if (p[i] > 0)
            ++ degree[p[i]];
    }

    int cnt = 0;
    for (int i = 1; i <= N; ++ i)
        if (degree[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (p[node] == -1)
            ++ cnt;
        else
            q.push(p[node]);
    }

    dp[0] = 1;
    for (int i = 1; i <= cnt; ++ i)
        dp[i] = ((i - 1LL) * (dp[i - 1] + dp[i - 2])) % MOD;
    cout << dp[cnt] << '\n';
    return 0;
}
