#include <bits/stdc++.h>

using namespace std;

const int MOD1 = 1000000000 + 7;
const int MOD2 = 1000000000 + 9;

int pow(int a, int b, int MOD) {
    int ans = 1, aux = a;
    while (b) {
        if (b & 1)
            ans = (1LL * ans * aux) % MOD;
        aux = (1LL * aux * aux) % MOD;
        b >>= 1;
    }
    return ans;
}
int inv(int a, int MOD) { return pow(a, MOD - 2, MOD); }

const int NMAX = 100000 + 5;

int vl1[NMAX], vl2[NMAX];
map <pair <int, int>, int> colors;

vector <pair <int, pair <int, int> > > graph[NMAX];

bool vis[NMAX];
void dfs(int node) {
    vis[node] = true;
    for (auto it: graph[node]) {
        const int son = it.first;
        const int rat1 = it.second.first;
        const int rat2 = it.second.second;
        if (!vis[son]) {
            vl1[son] = (1LL * vl1[node] * rat1) % MOD1;
            vl2[son] = (1LL * vl2[node] * rat2) % MOD2;
            dfs(son);
        }
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    while (M --) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        graph[a].emplace_back(b, make_pair((1LL * c * inv(d, MOD1)) % MOD1, (1LL * c * inv(d, MOD2)) % MOD2));
        graph[b].emplace_back(a, make_pair((1LL * d * inv(c, MOD1)) % MOD1, (1LL * d * inv(c, MOD2)) % MOD2));
    }

    vl1[1] = vl2[1] = 1;
    dfs(1);

    for (int i = 1; i <= N; ++ i) {
        if (!colors.count(make_pair(vl1[i], vl2[i]))) {
            const int label = colors.size() + 1;
            colors[make_pair(vl1[i], vl2[i])] = label;
        }
        cout << colors[make_pair(vl1[i], vl2[i])] << '\n';
    }
    return 0;
}
