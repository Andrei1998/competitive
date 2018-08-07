#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 100000 + 5;

int N;
vector <int> graph[NMAX];

int dp[NMAX];
int dpBest[NMAX];

void dfs(int node, int father) {
    int best1 = -1, best2 = -1;
    for (auto it: graph[node])
        if (it != father) {
            dfs(it, node);
            dpBest[node] = max(dpBest[node], dpBest[it]);

            if (dp[it] > best1) {
                best2 = best1;
                best1 = dp[it];
            }
            else if (dp[it] > best2)
                best2 = dp[it];
        }

    dp[node] = 1 + best1;
    dpBest[node] = max(dpBest[node], best1 + best2 + 2);
}

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N;
    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int R;
    cin >> R;

    dfs(R, 0);

    int Q = 0;
    cin >> Q;

    while (Q --) {
        int node;
        cin >> node;

        cout << dpBest[node] << '\n';
    }
    return 0;
}
