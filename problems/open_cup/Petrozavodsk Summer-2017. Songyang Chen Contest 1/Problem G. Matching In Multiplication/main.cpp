#include <bits/stdc++.h>

// 20:07
using namespace std;

typedef long long int lint;

const int MOD = 998244353;
const int NMAX = 300000 + 5;

struct Edge {
    int a, b, w1, w2;
    bool cycle;
    int other(int node) {
        return a ^ b ^ node;
    }
    int getCost(int _a, int _b) {
        if (a == _a && b == _b)
            return w1;
        else if (a == _b && b == _a)
            return w2;
        else
            assert(false);
    }
    int getAntiCost(int _a, int _b) {
        return getCost(_b, _a);
    }
} edges[NMAX];

inline void add(int &where, const int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}
inline void mul(int &where, const int val) {
    where = (1LL * where * val) % MOD;
}

int N;
vector <int> graph[NMAX];
int h[NMAX], father[NMAX];

int prod = 1;
void traverse(int down, int up, int &prod0, int &prod1) {
    while (down != up) {
        const int fat = edges[father[down]].other(down);
        mul(prod0, edges[father[down]].getCost(fat, down));
        mul(prod1, edges[father[down]].getAntiCost(fat, down));
        edges[father[down]].cycle = true;
        down = fat;
    }
    int sum = prod0;
    add(sum, prod1);
    mul(prod, sum);
}

bool vis[NMAX];
void dfs(int node) {
    vis[node] = true;
    for (auto it: graph[node]) {
        const int son = edges[it].other(node);
        if (!vis[son]) {
            father[son] = it;
            h[son] = 1 + h[node];
            dfs(son);
        }
        else if (h[son] < h[node] && it != father[node]) {
            int prod0 = edges[it].getCost(node, son), prod1 = edges[it].getAntiCost(node, son);
            edges[it].cycle = true;
            traverse(node, son, prod0, prod1);
        }
    }
}

void dfs2(int node) {
    vis[node] = true;
    for (auto it: graph[node]) {
        const int son = edges[it].other(node);
        if (!vis[son]) {
            if (!edges[it].cycle)
                mul(prod, edges[it].getAntiCost(node, son));
            dfs2(son);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
    ios_base :: sync_with_stdio(false);
#endif
    cin >> N;
    for (int i = 1; i <= N; ++ i) {
        int a, b, w1, w2;
        cin >> a >> w1 >> b >> w2;
        edges[i].a = a, edges[i].b = b;
        edges[i].w1 = w1 % MOD, edges[i].w2 = w2 % MOD;
        graph[a].emplace_back(i);
        graph[b].emplace_back(i);
    }
    for (int i = 1; i <= N; ++ i)
        if (!vis[i])
            dfs(i);

    for (int i = 1; i <= N; ++ i)
        vis[i] = false;
    int prodTree = 1;
    for (int i = 1; i <= N; ++ i)
        if (edges[i].cycle) {
            const int a = edges[i].a;
            if (!vis[a])
                dfs2(a);
        }

    mul(prod, prodTree);
    cout << prod << endl;
    return 0;
}
