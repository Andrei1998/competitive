#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

int N, S, M, K;
const int NMAX = 1000000 + 100;

vector <int> A[200];

struct Point {
    int P, D;
    friend bool operator<(const Point &a, const Point &b) {
        return make_pair(a.P, a.D) < make_pair(b.P, b.D);
    }
} points[NMAX];

struct Node {
    int l, r;
    lint minimum, lazy;
} tree[4 * NMAX];
void propagate(int node) {
    if (tree[node].lazy) {
        tree[2 * node].minimum += tree[node].lazy;
        tree[2 * node].lazy += tree[node].lazy;
        tree[2 * node + 1].minimum += tree[node].lazy;
        tree[2 * node + 1].lazy += tree[node].lazy;
        tree[node].lazy = 0;
    }
}
void build(int node, int l, int r) {
    tree[node].l = l, tree[node].r = r;
    tree[node].lazy = tree[node].minimum = 0;
    if (l == r)
        return ;
    const int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
}
void update(int node, int l, int r, lint val) {
    if (tree[node].l == l && tree[node].r == r) {
        tree[node].minimum += val;
        tree[node].lazy += val;
        if (l == r)
            tree[node].lazy = 0;
        return ;
    }
    propagate(node);
    const int mid = (tree[node].l + tree[node].r) / 2;
    if (r <= mid)
        update(2 * node, l, r, val);
    else if (l > mid)
        update(2 * node + 1, l, r, val);
    else {
        update(2 * node, l, mid, val);
        update(2 * node + 1, mid + 1, r, val);
    }
    tree[node].minimum = min(tree[2 * node].minimum, tree[2 * node + 1].minimum);
}
lint query(int node, int l, int r) {
    if (tree[node].l == l && tree[node].r == r)
        return tree[node].minimum;
    propagate(node);
    const int mid = (tree[node].l + tree[node].r) / 2;
    if (r <= mid)
        return query(2 * node, l, r);
    else if (l > mid)
        return query(2 * node + 1, l, r);
    else
        return min(query(2 * node, l, mid),
                   query(2 * node + 1, mid + 1, r));
}

lint cost[NMAX];
void add(int l, int r, lint val) {
    //for (int i = l; i <= r; ++ i)
    //    cost[i] += val;
    update(1, l, r, val);
}

lint getBest(int l, int r) {
    //lint ans = cost[l];
    //for (int i = l + 1; i <= r; ++ i)
    //    ans = min(ans, cost[i]);
    //return ans;
    return query(1, l, r);
}

lint dp[NMAX];

int stk[NMAX];
int stkSz;

lint solve() {
    stkSz = 0;
    sort(points + 1, points + N + 1);
    for (int i = 0; i <= N; ++ i) {
        dp[i] = 0;
        cost[i] = 0;
        stk[i] = 0;
    }
    for (int i = 0; i <= 4 * N; ++ i)
        tree[i].l = tree[i].r = tree[i].minimum = tree[i].lazy = 0;
    build(1, 1, N + 1);

    int j = 1;
    for (int i = 1; i <= N; ++ i) {
        while (points[i].P - points[j].P > 2 * M)
            ++ j;

        // Pop
        while (stkSz > 0 && points[stk[stkSz]].D <= points[i].D) {
            add(stk[stkSz - 1] + 1, stk[stkSz], -points[stk[stkSz]].D);
            -- stkSz;
        }

        // Push
        stk[++ stkSz] = i;
        add(stk[stkSz - 1] + 1, stk[stkSz], points[stk[stkSz]].D);

        dp[i] = S + getBest(j, i);

        /*assert(i >= j);
        dp[i] = S + points[i].D + dp[i - 1];
        int mx = points[i].D;
        for (int k = i - 1; k >= j; -- k) {
            mx = max(mx, points[k].D);
            dp[i] = min(dp[i], S + mx + dp[k - 1]);
            //cout << "am " << mx + dp[k - 1] << " vs " << cost[k] << " pentru " << k << " si i = " << i << endl;
            assert(mx + dp[k - 1] == cost[k]);
        }*/

        add(i + 1, i + 1, dp[i]);
    }

    return dp[N];
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    int T = 0;
    cin >> T;
    for (int t = 1; t <= T; ++ t) {
        cerr << "t = " << t << endl;
        cin >> N >> S >> M >> K;
        int where = 0;
        for (int i = 1; i <= 2 * K; ++ i) {
            int L, Ai1, X, Y, Z;
            cin >> L >> Ai1 >> X >> Y >> Z;
            A[i].clear();
            A[i].push_back(0);
            A[i].push_back(Ai1);
            auto fct = [&]() {
                if (i <= K)
                    points[++ where].P = A[i].back();
                else
                    points[++ where].D = A[i].back();
            };
            fct();
            for (int j = 2; j <= L; ++ j) {
                A[i].push_back((1LL * X * A[i].back() + Y) % Z + 1);
                fct();
            }
            if (i == K)
                where = 0;
        }
        cout << "Case #" << t << ": " << solve() << endl;
    }
    return 0;
}
