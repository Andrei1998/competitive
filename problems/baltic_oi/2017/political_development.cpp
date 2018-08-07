#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>

using namespace std;

inline int lsb(int x) {
    return x & (-x);
}

const int NMAX = 50000 + 5;
const int KMAX = 10;

int degree[NMAX];
vector <int> graph[NMAX];

bool vis[NMAX];

set <pair <int, int> > edges;

int g[KMAX + 1];
bool works[1 << KMAX];

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    queue <int> q;
    for (int i = 1; i <= N; ++ i) {
        cin >> degree[i];
        graph[i].resize(degree[i]);
        for (int j = 0; j < degree[i]; ++ j) {
            cin >> graph[i][j];
            ++ graph[i][j];
            edges.insert(make_pair(i, graph[i][j]));
            edges.insert(make_pair(graph[i][j], i));
        }

        if (degree[i] < K)
            q.push(i);
    }

    int ans = 1;
    while (!q.empty()) {
        int node = q.front();
        vis[node] = true;
        q.pop();

        vector <int> nodes = {node};
        for (auto it: graph[node])
            if (!vis[it]) {
                nodes.push_back(it);
                -- degree[it];
                if (degree[it] + 1 == K)
                    q.push(it);
            }

        for (int i = 0; i < nodes.size(); ++ i) {
            g[i] = (1 << i);
            for (int j = 0; j < nodes.size(); ++ j)
                if (edges.count(make_pair(nodes[i], nodes[j])))
                    g[i] |= (1 << j);
        }


        works[0] = true;
        for (int i = 1; i < (1 << nodes.size()); ++ i) {
            works[i] = false;
            if (works[i - lsb(i)]) {
                int bit = __builtin_ctz(i);
                if ((i & g[bit]) == i) {
                    works[i] = true;
                    if (__builtin_popcount(i) > ans)
                        ans = __builtin_popcount(i);
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
