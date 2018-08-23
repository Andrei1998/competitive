#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 100000 + 5;

int N;
int father[NMAX];
int h[NMAX];
int sz[NMAX];

inline void init() {
    for (int i = 1; i <= N; ++ i)
        father[i] = i, h[i] = 0, sz[i] = 1;
}

int find(int node) {
    if (father[node] != father[father[node]])
        father[node] = find(father[node]);
    return father[node];
}

inline void unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
        return ;

    if (h[a] < h[b]) {
        father[a] = b;
        sz[b] += sz[a];
    }
    else {
        if (h[a] == h[b])
            ++ h[a];
        father[b] = a;
        sz[a] += sz[b];
    }
}

inline int getSz(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
        return sz[a];
    else
        return sz[a] + sz[b];
}

struct Edge {
    int a, b;
} edges[NMAX];

struct Query {
    int a, b, z;
    int ans;
    int pos;

    friend bool operator<(const Query &a, const Query &b) {
        return a.ans < b.ans;
    }
};

vector <Query> queries;

int anss[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int M = 0;
    cin >> N >> M;

    for (int i = 1; i <= M; ++ i)
        cin >> edges[i].a >> edges[i].b;

    int Q = 0;
    cin >> Q;

    queries.resize(Q);
    for (int i = 0; i < Q; ++ i) {
        cin >> queries[i].a >> queries[i].b >> queries[i].z;
        queries[i].pos = i;
    }

    vector <Query> qr1;
    vector <Query> qr2;

    for (int step = 17; step >= 0; -- step) {
        for (auto &it: queries)
            it.ans += (1 << step);

        init();

        qr1.clear();
        qr2.clear();

        int i = 1;
        for (auto &it: queries) {
            while (i <= M && i <= it.ans) {
                unite(edges[i].a, edges[i].b);
                ++ i;
            }

            if (getSz(it.a, it.b) >= it.z) {
                it.ans -= (1 << step);
                qr1.push_back(it);
            }
            else
                qr2.push_back(it);
        }

        merge(qr1.begin(), qr1.end(),
              qr2.begin(), qr2.end(),
              queries.begin());
    }

    for (auto it: queries)
        anss[it.pos] = it.ans + 1;

    for (int i = 0; i < Q; ++ i)
        cout << anss[i] << '\n';
    return 0;
}
