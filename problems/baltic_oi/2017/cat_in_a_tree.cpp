#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <queue>
#include <vector>

using namespace std;

const int NMAX = 2 * 100000 + 5;

int N, D;
vector <int> graph[NMAX];

int dist[NMAX];
int h[NMAX];

void dfs(int node, int father) {
    for (auto it: graph[node])
        if (it != father) {
            h[it] = 1 + h[node];
            dfs(it, node);
        }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    //freopen("data.in", "r", stdin);

    cin >> N >> D;
    for (int i = 2; i <= N; ++ i) {
        int node;
        cin >> node;
        ++ node;
        graph[i].push_back(node);
        graph[node].push_back(i);
    }

    dfs(1, 0);

    vector <pair <int, int> > v;
    for (int i = 1; i <= N; ++ i)
        v.push_back(make_pair(-h[i], i));
    sort(v.begin(), v.end());

    queue <int> q;

    int ans = 0;
    for (int i = 0; i < N; ++ i) {
        int node = v[i].second;
        if (!dist[node]) {
            ++ ans;
            dist[node] = 1;
            q.push(node);
            while (!q.empty()) {
                node = q.front();
                q.pop();
                if (dist[node] == D)
                    continue;

                for (auto it: graph[node])
                    if (!dist[it] || dist[node] + 1 < dist[it]) {
                        dist[it] = 1 + dist[node];
                        q.push(it);
                    }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
