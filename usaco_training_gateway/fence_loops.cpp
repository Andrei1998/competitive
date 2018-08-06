/*
ID: andreip3
LANG: C++14
TASK: fence6
*/
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100 + 5;

int N;
vector <pair <int, int> > graph[NMAX];
int dst[NMAX];
bool vis[NMAX];

int dijkstra(int s, int t) {
    for (int i = 1; i <= N; ++ i)
        dst[i] = 1E9, vis[i] = false;
    dst[s] = 0;
    for (int i = 2; i <= N; ++ i) {
        int best =  1E9, who = -1;
        for (int j = 1; j <= N; ++ j)
            if (!vis[j] && dst[j] < best)
                best = dst[j], who = j;
        if (who == -1)
            break;
        vis[who] = true;
        for (auto it: graph[who])
            if (dst[who] + it.second < dst[it.first])
                dst[it.first] = dst[who] + it.second;
    }
    return dst[t];
}

map <vector <int>, int> Map;

int main() {
    freopen("fence6.in", "r", stdin);
    freopen("fence6.out", "w", stdout);
    cin >> N;

    vector <tuple <int, int, int> > edges;
    for (int i = 1; i <= N; ++ i) {
        int id, l;
        cin >> id >> l;
        int a; cin >> a;
        int b; cin >> b;

        vector <int> A;
        while (a --) {
            int node;
            cin >> node;
            A.push_back(node);
        }
        vector <int> B;
        while (b --) {
            int node;
            cin >> node;
            B.push_back(node);
        }
        A.push_back(id);
        B.push_back(id);
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        if (!Map.count(A))
            Map[A] = Map.size();
        if (!Map.count(B))
            Map[B] = Map.size();

        a = Map[A], b = Map[B];
        graph[a].push_back(make_pair(b, l));
        graph[b].push_back(make_pair(a, l));
        edges.push_back(make_tuple(a, b, l));
    }

    int ans = 1E9;
    for (auto it: edges) {
        int a, b, l;
        tie(a, b, l) = it;
        graph[a].erase(find(graph[a].begin(), graph[a].end(), make_pair(b, l)));
        graph[b].erase(find(graph[b].begin(), graph[b].end(), make_pair(a, l)));
        ans = min(ans, l + dijkstra(a, b));
        graph[a].push_back(make_pair(b, l));
        graph[b].push_back(make_pair(a, l));
    }

    cout << ans << '\n';
    return 0;
}
