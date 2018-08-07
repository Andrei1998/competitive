#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

const int NMAX = 2000 + 5;
const int MMAX = 100000 + 5;

struct Edge {
    int a, b;
    bool available;
    Edge(int _a = 0, int _b = 0):
        a(_a), b(_b), available(true) {}

    inline int other(int node) {
        return a ^ b ^ node;
    }
} edges[MMAX];

vector <int> graph[NMAX];

int vis[NMAX];
int cnt;
int tmp;
int h[NMAX];
int low[NMAX];

int toAdd;
int ans;

void dfs(int node, int fatherEdge) {
    vis[node] = tmp;
    ++ cnt;
    for (auto it: graph[node]) {
        int son = edges[it].other(node);
        if (edges[it].available) {
            if (vis[son] < tmp) {
                h[son] = low[son] = 1 + h[node];
                dfs(son, it);

                if (low[son] > h[node])
                    ++ toAdd;
            }
            else if (it != fatherEdge)
                low[node] = min(low[node], h[it]);
        }
    }
}

int main()
{
    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        edges[i].a = a;
        edges[i].b = b;

        graph[a].push_back(i);
        graph[b].push_back(i);
    }

    for (int i = 1; i <= M; ++ i) {
        edges[i].available = false;
        ++ tmp;
        cnt = 0, toAdd = 0;

        dfs(1, 0);

        edges[i].available = true;
        if (cnt == N)
            ans += toAdd;
    }

    cout << ans / 2 << '\n';
    return 0;
}
