#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long int lint;

const int MOD[] = {97 * 25 * 89 * 41 * 83,
                   13 * 67 * 71 * 73 * 79,
                   43 * 47 * 53 * 59 * 61,
                   64 * 81 * 49 * 31 * 17,
                   19 * 23 * 29 * 11 * 37 * 101};

int gcd(int a, int b) {
    if (!b)
        return a;
    int r = a % b;
    while (r) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int phi[102];

void computePhi() {
    for (int i = 1; i <= 101; ++ i)
        for (int j = 1; j <= i; ++ j)
            phi[i] += (gcd(i, j) == 1);
}

int raise(int a, int b, int MOD) {
    if (!b)
        return 1 % MOD;
    else if (b & 1)
        return (a * raise(a, b - 1, MOD)) % MOD;
    else {
        int aux = raise(a, b >> 1, MOD);
        return (aux * aux) % MOD;
    }
}

int inv(int nr, int MOD) {
    return raise(nr, phi[MOD] - 1, MOD);
}

class Nr {
public:
    Nr() {
        for (int i = 0; i < N; ++ i)
            v[i] = 0;
    }

    Nr(lint c) {
        for (int i = 0; i < N; ++ i)
            v[i] = c % MOD[i];
    }

    friend Nr operator+(const Nr &a, const Nr &b) {
        Nr ans;
        for (int i = 0; i < N; ++ i) {
            ans.v[i] = a.v[i] + b.v[i];
            if (ans.v[i] >= MOD[i])
                ans.v[i] -= MOD[i];
        }
        return ans;
    }

    friend Nr operator-(const Nr &a, const Nr &b) {
        Nr ans;
        for (int i = 0; i < N; ++ i) {
            ans.v[i] = a.v[i] - b.v[i];
            if (ans.v[i] < 0)
                ans.v[i] += MOD[i];
        }
        return ans;
    }

    friend Nr operator*(const Nr &a, const Nr &b) {
        Nr ans;
        for (int i = 0; i < N; ++ i)
            ans.v[i] = (1LL * a.v[i] * b.v[i]) % MOD[i];
        return ans;
    }

    Nr operator^(lint b) const {
        Nr ans(1), aux(*this);
        while (b) {
            if (b & 1)
                ans = ans * aux;
            aux = aux * aux;
            b >>= 1;
        }
        return ans;
    }

    bool operator!=(const Nr &arg) const {
        for (int i = 0; i < N; ++ i)
            if (v[i] != arg.v[i])
                return true;
        return false;
    }

    int convert(const int targetMod) {
        int mods[N];
        int r[N];
        for (int i = 0; i < N; ++ i) {
            mods[i] = gcd(targetMod, MOD[i]);
            r[i] = v[i] % mods[i];
        }

        int ans = 0;
        for (int i = 0; i < N; ++ i) {
            int prod = 1;
            for (int j = 0; j < N; ++ j)
                if (j != i)
                    prod *= mods[j];
            ans = (ans + prod * inv(prod, mods[i]) * r[i]) % targetMod;
        }

        return ans;
    }

    static const int N = sizeof(MOD) / sizeof(int);
    int v[N];
};

const int NMAX = 100000 + 5;

struct Node {
    int st, dr;

    Nr sum;
    Nr lazy;

    void makeLazy(const Nr &val) {
        sum = sum + val * (dr - st + 1);
        if (st < dr)
            lazy = lazy + val;
    }
} tree[4 * NMAX];

/*void propagate(int node) {
    if (tree[node].lazy != Nr(0)) {
        tree[node << 1].makeLazy(tree[node].lazy);
        tree[(node << 1) + 1].makeLazy(tree[node].lazy);
        tree[node].lazy = 0;
    }
}*/

void build(int node, int st, int dr) {
    tree[node].st = st, tree[node].dr = dr;
    if (st == dr)
        return ;

    int mid = (tree[node].st + tree[node].dr) >> 1;
    build(node << 1, st, mid);
    build((node << 1) + 1, mid + 1, dr);
}

void update(int node, int st, int dr, const Nr &val) {
    if (tree[node].st == st && tree[node].dr == dr) {
        tree[node].makeLazy(val);
        return ;
    }
    //propagate(node);

    int mid = (tree[node].st + tree[node].dr) >> 1;
    if (dr <= mid)
        update(node << 1, st, dr, val);
    else if (st > mid)
        update((node << 1) + 1, st, dr, val);
    else {
        update(node << 1, st, mid, val);
        update((node << 1) + 1, mid + 1, dr, val);
    }

    tree[node].sum = tree[node << 1].sum + tree[(node << 1) + 1].sum + (tree[node].dr - tree[node].st + 1) * tree[node].lazy;
}

Nr query(int node, int st, int dr) {
    if (tree[node].st == st && tree[node].dr == dr)
        return tree[node].sum;
    //propagate(node);

    int mid = (tree[node].st + tree[node].dr) >> 1;

    Nr ans;
    if (dr <= mid)
        ans = query(node << 1, st, dr);
    else if (st > mid)
        ans = query((node << 1) + 1, st, dr);
    else
        ans = query(node << 1, st, mid) +
              query((node << 1) + 1, mid + 1, dr);

    ans = ans + (dr - st + 1) * tree[node].lazy;
    return ans;
}

int N;
vector <int> graph[NMAX];

int father[NMAX][17];

int h[NMAX];
int first[NMAX];
int last[NMAX];
int sz;

void dfs(int node) {
    for (int i = 1; i < 17; ++ i)
        father[node][i] = father[father[node][i - 1]][i - 1];

    first[node] = ++ sz;
    for (auto it: graph[node])
        if (it != father[node][0]) {
            h[it] = 1 + h[node];
            father[it][0] = node;
            dfs(it);
        }
    last[node] = sz;
}

inline bool inSubtree(int t, int r) {
    return first[r] <= first[t] && first[t] <= last[r];
}

int ancestor(int node, int k) {
    for (int i = 16; i >= 0; -- i)
        if (father[node][i] && (1 << i) <= k) {
            node = father[node][i];
            k -= (1 << i);
        }
    return node;
}

void updateTree(int r, int t, const Nr &nr) {
    if (r == t)
        update(1, 1, sz, nr);
    else if (inSubtree(t, r) || !inSubtree(r, t))
        update(1, first[t], last[t], nr);
    else {
        int t2 = ancestor(r, h[r] - h[t] - 1);
        update(1, 1, sz, nr);
        update(1, first[t2], last[t2], Nr(0) - nr);
    }
}

int queryTree(int r, int t, int MOD) {
    Nr ans;
    if (r == t)
        ans = query(1, 1, sz);
    else if (inSubtree(t, r) || !inSubtree(r, t))
        ans = query(1, first[t], last[t]);
    else {
        int t2 = ancestor(r, h[r] - h[t] - 1);

        ans = query(1, 1, sz);
        ans = ans - query(1, first[t2], last[t2]);
    }

    return ans.convert(MOD);
}

int main()
{
    computePhi();

    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1);
    build(1, 1, N);

    int Q = 0;
    cin >> Q;

    while (Q --) {
        char type;
        int r, t;
        cin >> type >> r >> t;

        if (type == 'U') {
            lint a, b;
            cin >> a >> b;

            Nr nr = (Nr(a) ^ b) + (Nr(a + 1) ^ b) + (Nr(b + 1) ^ a);
            updateTree(r, t, nr);
        }
        else {
            int m;
            cin >> m;
            cout << queryTree(r, t, m) << '\n';
        }
    }

    return 0;
}
