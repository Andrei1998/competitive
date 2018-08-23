#include <iostream>
#include <cstdio>

using namespace std;

inline void update(int &where, long long int val) {
    if (val < where)
        where = val;
}

const int NMAX = 100 + 5;
const int KMAX = 5000 + 5;
const int INF = 1070000000 + 5;

int N, M, K;
int dist[NMAX][NMAX];

int s[KMAX];
int t[KMAX];

int dp1[KMAX];
int dp2[KMAX];

int test() {
    cin >> N >> M >> K;

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            if (i != j)
                dist[i][j] = INF;

    for (int i = 1; i <= M; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = min(dist[a][b], c);
    }

    for (int k = 1; k <= N; ++ k)
        for (int i = 1; i <= N; ++ i)
            for (int j = 1; j <= N; ++ j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    for (int i = 1; i <= K; ++ i)
        cin >> s[i] >> t[i];
    s[K + 1] = t[K + 1] = 0;

    for (int i = 1; i <= K + 1; ++ i)
        dp1[i] = dp2[i] = INF;

    dp1[1] = dist[1][s[1]];
    for (int i = 1; i <= K; ++ i) {
        update(dp1[i + 1], 1LL * dp1[i] + dist[s[i]][t[i]] + dist[t[i]][s[i + 1]]);
        update(dp2[i + 1], 1LL * dp1[i] + dist[s[i]][s[i + 1]] + dist[s[i + 1]][t[i]]);
        update(dp1[i + 1], 1LL * dp2[i] + dist[t[i - 1]][t[i]] + dist[t[i]][s[i + 1]]);
        update(dp2[i + 1], 1LL * dp2[i] + dist[t[i - 1]][s[i + 1]] + dist[s[i + 1]][t[i]]);
    }

    int ans = dp1[K + 1];
    if (ans == INF)
        ans = -1;
    return ans;
}

int main()
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;

    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << test() << '\n';
    return 0;
}
