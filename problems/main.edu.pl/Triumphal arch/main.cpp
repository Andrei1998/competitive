#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 300000 + 5;

vector <int> graph[NMAX];

int K;
int dp[NMAX];
void dfs(int node, int father) {
    dp[node] = 1;
    for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it)
        if (*it != father) {
            dfs(*it, node);
            dp[node] += dp[*it];
        }
    dp[node] -= K;
    if (dp[node] < 1)
        dp[node] = 1;
}

bool works() {
    dfs(1, 0);
    return dp[1] == 1;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int st = 0;
    int dr = N;
    int ans;

    while (st <= dr) {
        K = (st + dr) >> 1;
        if (works()) {
            ans = K;
            dr = K - 1;
        }
        else
            st = K + 1;
    }

    cout << ans << '\n';
    return 0;
}
