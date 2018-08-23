#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int NMAX = 100000 + 5;
const int MMAX = 500000 + 5;

int N, M;
vector <int> graph[NMAX];

int h[NMAX];
int low[NMAX];
int sz[NMAX];
bool vis[NMAX];

typedef long long int lint;

lint ans[NMAX];

void dfs(int node) {
    vis[node] = true;
    sz[node] = 1;
    int sum = N - 1; // Nodes in upper component
    for (int i = 0; i < graph[node].size(); ++ i) {
        int it = graph[node][i];
        if (!vis[it]) {
            h[it] = low[it] = 1 + h[node];
            dfs(it);
            sz[node] += sz[it];
            if (low[it] < h[node]) {
                if (low[it] < low[node])
                    low[node] = low[it];
            }
            else {
                sum -= sz[it];
                ans[node] += sz[it] * (sz[it] - 1LL);
            }
        }
        else
            low[node] = min(low[node], h[it]);
    }
    ans[node] += sum * (sum - 1LL);
}

int main()
{
    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1);

    for (int i = 1; i <= N; ++ i)
        cout << N * (N - 1LL) - ans[i] << '\n';
    return 0;
}
