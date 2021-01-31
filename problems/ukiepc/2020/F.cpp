#include <bits/stdc++.h>

using namespace std;

#define int long long int

const int NMAX = 2000 + 5;

int strt[NMAX];

int costs[NMAX][NMAX];

int need[NMAX];
vector<pair<int, int> > graph[NMAX];
int N, M, p, g;

priority_queue<pair<int, int>> pq;
int dist[NMAX];

bool vsts[NMAX];

void dijkstra(int node) {
    const int init_node = node;
    memset(vsts, 0, sizeof vsts);
    for (int i = 1; i <= N; ++i) {
        dist[i] = numeric_limits<int>::max();
    }
    dist[node] = 0;
    pq.push(make_pair(0, node));
    while (!pq.empty()) {
        node = pq.top().second;
        const int cst = -pq.top().first;
        pq.pop();
        if (vsts[node]) continue;
        for (const auto e : graph[node]) {
            if (dist[node] + e.second < dist[e.first]) {
                dist[e.first] = dist[node] + e.second;
                pq.push({-dist[e.first], e.first}); 
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        costs[init_node][i] = dist[i];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> p >> g;
    for (int i = 1; i <= p; ++i) {
        cin >> strt[i];
        need[strt[i]] = true;
    }
    for (int i = 1; i <= M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }
    need[1] = true;
    for (int i = 1; i <= N; ++i) {
        if (need[i] == true) {
            dijkstra(i);
        }
    }

    int sol = numeric_limits<int>::max();
    for (int node = 1; node <= N; ++node) {
        int val = 0;
        for (int i = 1; i <= p; ++i) {
            int aux = costs[1][strt[i]];
            if (costs[1][strt[i]] == costs[strt[i]][node] + costs[1][node]) {
                aux = min(aux, costs[strt[i]][node] + g);
            }
            val += aux;
        }
        sol = min(sol, val);
    }
    cout << sol << endl;
    return 0;
}