#include <iostream>
#include <cstdio>

using namespace std;

const int NMAX = 50000 + 5;
const int INF = 1E9 + 15;

int K, N, M, Q;
struct Node {
    int st, dr;
    int cost[5][5];
} tree[4 * NMAX];

int cost[NMAX][5][5];

void unite(Node &res, const Node a, const Node &b) {
    if (res.st == -1) {
        res = b;
        return ;
    }

    for (int i = 0; i < K; ++ i)
        for (int j = 0; j < K; ++ j) {
            res.cost[i][j] = INF;
            for (int k = 0; k < K; ++ k)
                res.cost[i][j] = min(res.cost[i][j], a.cost[i][k] + b.cost[k][j]);
        }
}

void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    if (st == dr) {
        for (int i = 0; i < K; ++ i)
            for (int j = i + 1; j < K; ++ j)
                tree[node].cost[i][j] = tree[node].cost[j][i] = INF;
    }
    else if (st + 1 == dr) {
        for (int i = 0; i < K; ++ i)
            for (int j = 0; j < K; ++ j)
                tree[node].cost[i][j] = cost[st][i][j];
    }
    else {
        int mid = (st + dr) >> 1;
        build(node << 1, st, mid);
        build((node << 1) + 1, mid, dr);
        unite(tree[node], tree[node << 1], tree[(node << 1) + 1]);
    }
}

Node ans;
void query(int node, int st, int dr) {
    if (st >= dr)
        return ;
    if (tree[node].st == st && tree[node].dr == dr) {
        unite(ans, ans, tree[node]);
        return ;
    }

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr < mid)
        query(node << 1, st, dr);
    else if (st > mid)
        query((node << 1) + 1, st, dr);
    else {
        query(node << 1, st, mid);
        query((node << 1) + 1, mid, dr);
    }
}

int main() {
    //freopen("toll.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> K >> N >> M >> Q;
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < K; ++ j)
            for (int k = 0; k < K; ++ k)
                cost[i][j][k] = INF;

    while (M --) {
        int a, b, t;
        cin >> a >> b >> t;
        cost[a / K][a % K][b % K] = t;
    }

    build(1, 0, (N - 1) / K);

    while (Q --) {
        int a, b;
        cin >> a >> b;

        ans.st = -1;
        query(1, a / K, b / K);
        int res = INF;
        if (ans.st != -1)
            res = ans.cost[a % K][b % K];
        if (res == INF)
            cout << "-1\n";
        else
            cout << res << '\n';
    }
    return 0;
}
