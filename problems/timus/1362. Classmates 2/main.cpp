#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 100000 + 5;
vector <int> graph[NMAX];

int dp[NMAX];

void dfs(int node, int father) {
    for (auto it: graph[node])
        if (it != father)
            dfs(it, node);

    sort(graph[node].begin(), graph[node].end(), [&](const int &a, const int &b) {
        return dp[a] > dp[b];
    });

    int cnt = 0;
    for (auto it: graph[node])
        if (it != father)
            dp[node] = max(dp[node], dp[it] + (++ cnt));
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        int val;
        cin >> val;

        while (val) {
            graph[i].push_back(val);
            graph[val].push_back(i);
            cin >> val;
        }
    }

    int tanya;
    cin >> tanya;

    dfs(tanya, 0);

    cout << dp[tanya] << '\n';
    return 0;
}
