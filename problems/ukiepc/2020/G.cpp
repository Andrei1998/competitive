#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100000 + 5;

int father[NMAX];
int h[NMAX];

int find(int node) {
    if (father[node] != node) {
        father[node] = find(father[node]);
    }
    return father[node];
}

bool uni(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
        return false;
    }
    if (h[a] > h[b]) {
        swap(a, b);
    }
    if (h[a] == h[b]) {
        ++h[b];
    }
    father[a] = b;
    return true;
}

struct Edge {
    int a, b, c;
    friend bool operator<(const Edge&a, const Edge&b) {
        return make_tuple(a.c, a.a, a.b) < make_tuple(b.c, b.a, b.b);
    }
};

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    assert(3 <= n && n <= 100000 && m <= n);
    vector<Edge> edges;
    for (int i = 1; i <= n + 1; ++i) {
        father[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        int where, cost;
        cin >> where >> cost;
        Edge e;
        e.a = n + 1;
        e.b = where;
        e.c = cost;
        edges.push_back(e);
    }
    for (int i = 1; i <= n; ++i) {
        int b;
        cin >> b;
        Edge e;
        e.a = i;
        e.b = i % n + 1;
        e.c = b;
        edges.push_back(e);    
    }
    sort(edges.begin(), edges.end());
    long long int ans = 0;
    for (int i = 0; i < edges.size(); ++i) {
        const int a = edges[i].a;
        const int b = edges[i].b;
        if (uni(a, b)) {
            ans += edges[i].c;
        }
    }
    cout << ans << endl;
    return 0;
}