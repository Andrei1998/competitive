#include <bits/stdc++.h>

//14:53
using namespace std;

typedef long long int lint;
const int NMAX = 500000 + 5;

int N;

int start[NMAX];
int to[2 * NMAX];
int cost[2 * NMAX];
int nxt[2 * NMAX];

bool vis[NMAX];
int sz[NMAX];

static void dfsSz(const int node, const int father) {
    sz[node] = 1;
    for (int iter = start[node]; iter; iter = nxt[iter]) {
        const int v = to[iter];
        if (v == father || vis[v])
            continue;
        dfsSz(v, node);
        sz[node] += sz[v];
    }
}

int all;
static inline int getCent(int node) {
    int father = 0;
    go:
    for (int iter = start[node]; iter; iter = nxt[iter]) {
        const int v = to[iter];
        if (v == father || vis[v])
            continue;
        if (sz[v] > all / 2) {
            father = node;
            node = v;
            goto go;
        }
    }

    return node;
}

int centFather[NMAX];
lint best[NMAX];
int h[NMAX];

lint dists[NMAX][20];
queue <pair <int, int> > q;
static inline void bfsDists(int node, const int level) {
    q.push({node, 0});

    int father;
    while (!q.empty()) {
        node = q.front().first;
        father = q.front().second;
        q.pop();

        for (int iter = start[node]; iter; iter = nxt[iter]) {
            const int v = to[iter], c = cost[iter];

            if (v == father || vis[v])
                continue;

            dists[v][level] = dists[node][level] + c;
            q.push({v, node});
        }
    }
}

const void DEI(int node, const int f, const int level) {
    dfsSz(node, 0);
    all = sz[node];
    node = getCent(node);

    vis[node] = true;
    centFather[node] = f;
    h[node] = level;

    bfsDists(node, level);

    for (int iter = start[node]; iter; iter = nxt[iter]) {
        const int v = to[iter];
        if (vis[v])
            continue;
        DEI(v, node, level + 1);
    }
}

const lint INF = 1E18 + 7;
void Init(int _N, int _A[], int _B[], int _D[]) {
    N = _N;
    int pos = 0;
    for (int i = 0; i < N - 1; ++ i) {
        ++ _A[i];
        ++ _B[i];

        to[++ pos] = _B[i];
        cost[pos] = _D[i];
        nxt[pos] = start[_A[i]];
        start[_A[i]] = pos;

        to[++ pos] = _A[i];
        cost[pos] = _D[i];
        nxt[pos] = start[_B[i]];
        start[_B[i]] = pos;
    }

    fill(best + 1, best + N + 1, INF);
    for (int i = 1; i <= N; ++ i)
        best[i] = INF;

    DEI(1, 0, 0);
}

lint Query(int S, int X[], int T, int Y[]) {
    if (S < T) {
        swap(S, T);
        swap(X, Y);
    }

    for (int i = 0; i < S; ++ i) {
        const int v = ++ X[i];
        int p = v;
        while (p) {
            if (dists[v][h[p]] < best[p])
                best[p] = dists[v][h[p]];
            p = centFather[p];
        }
    }

    lint ans = INF;
    for (int i = 0; i < T; ++ i) {
        const int v = ++ Y[i];
        int p = v;
        lint aux;
        while (p) {
            aux = best[p] + dists[v][h[p]];
            if (aux < ans)
                ans = aux;
            p = centFather[p];
        }
    }

    for (int i = 0; i < S; ++ i) {
        int p = X[i];
        while (p && best[p] != INF) {
            best[p] = INF;
            p = centFather[p];
        }
    }

    return ans;
}

int main()
{
    freopen("data.in", "r", stdin);

    int N = 500000, Q = 100000;
    cin >> N >> Q;

    int *A = new int[N - 1];
    int *B = new int[N - 1];
    int *D = new int[N - 1];
    for (int i = 0; i + 1 < N; ++ i) {
        A[i] = i;//rand() % (i + 1);
        B[i] = i + 1;
        D[i] = 1E9;
        cin >> A[i] >> B[i] >> D[i];
    }
    Init(N, A, B, D);

    for (int i = 0; i < Q; ++ i) {
        int n = 1000, m = 1000;
        cin >> n >> m;

        int *X = new int[n];
        int *Y = new int[m];

        for (int j = 0; j < n; ++ j) {
            X[j] = rand() % N;
            cin >> X[j];
        }
        for (int j = 0; j < m; ++ j) {
            Y[j] = rand() % N;
            cin >> Y[j];
        }
        cout << Query(n, X, m, Y) << '\n';
        //Query(n, X, m, Y);
    }

    return 0;
}
