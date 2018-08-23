#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdlib>

using namespace std;

const int NMAX = 1e6 + 5;

int N, M;
vector <pair <pair <int, int>, int> > freq[NMAX];

int father[NMAX];
int h[NMAX];
int l[NMAX];
int r[NMAX];
int edge[NMAX];

void init() {
    for (int i = 1; i <= N; ++ i)
        father[i] = l[i] = r[i] = i;
}

int find(int node) {
    if (father[node] != father[father[node]])
        father[node] = find(father[node]);
    return father[node];
}

void unite(int a, int b, int edg) {
    a = find(a), b = find(b);
    if (a == b)
        return ;

    if (h[a] < h[b]) {
        father[a] = b;
        l[b] = min(l[a], l[b]);
        r[b] = max(r[a], r[b]);
        edge[b] = edg;
    }
    else {
        if (h[a] == h[b])
            ++ h[a];
        father[b] = a;
        l[a] = min(l[a], l[b]);
        r[a] = max(r[a], r[b]);
        edge[a] = edg;
    }
}

void win(int a, int b) {
    cout << a << ' ' << b << '\n';
    exit(0);
}

void addEdge(int a, int b, int edg) {
    int la = l[find(a)];
    if (a != la)
        win(edg, edge[find(la)]);
    int lb = r[find(b - 1)];
    if (b - 1 != lb)
        win(edg, edge[find(lb)]);

    b = l[find(a)];
    while (find(la) != find(lb))
        unite(la, r[find(la)] + 1, edg);
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin >> N >> M;

    if (M > N + 1)
        M = N + 1;

    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;

        if (b < a)
            swap(a, b);

        freq[b - a + 1].push_back(make_pair(make_pair(a, b), i));
    }

    init();
    for (int i = 1; i <= N; ++ i)
        for (vector <pair <pair <int, int>, int> > :: iterator it = freq[i].begin(); it != freq[i].end(); ++ it)
            addEdge(it -> first.first, it -> first.second, it -> second);

    cout << "NIE\n";
    return 0;
}
