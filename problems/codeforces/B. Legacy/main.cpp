#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const int NMAX = 100000 + 5;

int dist[NMAX];
queue <int> q;

set <int> Set;

void tryAdd(int st, int dr, int dst) {
    while (1) {
        auto it = Set.lower_bound(st);
        if (it == Set.end())
            break;
        else if (*it > dr)
            break;

        dist[*it] = 1 + dst;
        q.push(*it);
        Set.erase(*it);
    }
}

vector <pair <int, int> > graph[NMAX];

struct ToNode {
    int st, dr;
    int to;
    bool used;
} toNodes[NMAX];

struct Node {
    int st, dr;
    vector <int> ToNodes;
} tree[4 * NMAX];

void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    if (st == dr)
        return ;

    int mid = (tree[node].st + tree[node].dr) >> 1;
    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);
}

int main()
{
    ios_base :: sync_with_stdio(false);
    //cin.tie(0);

    int N, Q, S;
    cin >> N >> Q >> S;

    for (int i = 1; i <= Q; ++ i) {
        int type;
        cin >> type;

        if (type == 1) {
            int
        }
    }

    q.push(S);
    dist[S] = 1;
    for (int i = 1; i <= N; ++ i)
        if (i != S)
            Set.insert(i);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto it: graph[node])
            tryAdd(it.first, it.second, dist[node]);
    }

    for (int i = 1; i <= N; ++ i)
        cout << dist[i] - 1 << " \n"[i == N];
    return 0;
}
