#include <bits/stdc++.h>

using namespace std;


template <const int NMAX, const int MMAX>
class MaxFlow {
public:
    MaxFlow() { m = 0; }

    inline void setN(int _n) { n = _n; }
    inline void setS(int _s) { s = _s; }
    inline void setT(int _t) { t = _t; }

	inline int getN() { return n; }
    inline int getS() { return s; }
    inline int getT() { return t; }

    void clear() {
        m = 0;
        for (int i = 1; i <= n; ++ i)
            graph[i].clear();
    }

    void reset() {
        for (int i = 0; i < m; ++ i)
            edges[i].flow = 0;
    }

    void addEdge(int from, int to, int cap) {
        edges[m ++] = Edge(from, to, 0, cap);
        edges[m ++] = Edge(to, from, 0, 0);

        graph[from].push_back(m - 2);
        graph[to].push_back(m - 1);
    }

    inline int computeFlow() {
        return Dinic();
    }

private:
    struct Edge {
        int from, to;
        int flow, cap;

        Edge(int _from = 0, int _to = 0, int _flow = 0, int _cap = 0):
            from(_from), to(_to), flow(_flow), cap(_cap) {}
        inline int other(int node) {
            return from ^ to ^ node;
        }
    };

    int n, m, s, t;

    vector <int> graph[NMAX];
    Edge edges[2 * MMAX];

    int father[NMAX];
    bool vis[NMAX];
    queue <int> _queue;

    bool bfs() {
        memset(vis, 0, (n + 1) * sizeof(bool));

        vis[s] = true;
        _queue.push(s);

        int node;
        while (!_queue.empty()) {
            node = _queue.front();
            _queue.pop();

			if (node == t)
				continue;

            for (auto it: graph[node])
                if (!vis[edges[it].other(node)] && edges[it].flow < edges[it].cap) {
                    father[edges[it].other(node)] = it;
                    vis[edges[it].other(node)] = true;
                    _queue.push(edges[it].other(node));
                }
        }

        return vis[t];
    }

    int Dinic() {
        int flow = 0;
        while (bfs()) {
            for (auto it: graph[t])
                if (vis[edges[it ^ 1].other(t)] && edges[it ^ 1].flow < edges[it ^ 1].cap) {
                    int node = edges[it ^ 1].other(t);
                    int minimum = edges[it ^ 1].cap - edges[it ^ 1].flow;

                    while (node != s) {
                        minimum = min(minimum, edges[father[node]].cap - edges[father[node]].flow);
                        node = edges[father[node]].other(node);
                    }

                    node = edges[it ^ 1].other(t);
                    edges[it ^ 1].flow += minimum;
                    edges[it].flow -= minimum;
                    flow += minimum;

                    while (node != s) {
                        edges[father[node]].flow += minimum;
                        edges[father[node] ^ 1].flow -= minimum;

                        node = edges[father[node]].other(node);
                    }
                }
        }

        return flow;
    }
};

const int NMAX = 500 + 5;
const int KMAX = 7;

MaxFlow <NMAX + KMAX + 2, NMAX * KMAX> mf;

int N, K;
vector <int> tree[NMAX];
int colors[NMAX][KMAX];
int ans[NMAX];

bool dp[NMAX][KMAX][KMAX];
void dfs(int node, int father) {
    auto it = find(tree[node].begin(), tree[node].end(), father);
    if (it != tree[node].end())
        tree[node].erase(it);
    for (auto it: tree[node])
        dfs(it, node);

    for (int nodeCol = 1; nodeCol <= K; ++ nodeCol) {
        if (ans[node] != -1 && ans[node] != nodeCol)
            continue;
        for (int fatCol = 0; fatCol <= K; ++ fatCol) {
            if (fatCol == 0) {
                if (father != 0)
                    continue;
            }
            else if (ans[father] != -1 && ans[father] != fatCol)
                continue;

            -- colors[node][fatCol];
            if (colors[node][fatCol] >= 0 || father == 0) {
                int NODES = tree[node].size();

                // Build flow graph
                mf.clear();
                mf.setN(NODES + K + 2);
                mf.setS(NODES + K + 1);
                mf.setT(NODES + K + 2);
                for (int col = 1; col <= K; ++ col) {
                    mf.addEdge(mf.getS(), col, colors[node][col]);
                    for (int i = 0; i < NODES; ++ i) {
                        const int it = tree[node][i];
                        if (dp[it][col][nodeCol])
                            mf.addEdge(col, K + i + 1, 1);
                    }
                }
                for (int i = 0; i < NODES; ++ i)
                    mf.addEdge(K + i + 1, mf.getT(), 1);

                if (mf.computeFlow() == static_cast <int>(tree[node].size()))
                    dp[node][nodeCol][fatCol] = true;
            }
            ++ colors[node][fatCol];
        }
    }
}

bool works() {
    memset(dp, false, sizeof dp);
    dfs(1, 0);
    for (int i = 1; i <= K; ++ i)
        if (dp[1][i][0])
            return true;
    return false;
}

int main() {
    ifstream cin("design.in");
    ofstream cout("design.out");

    cin >> N >> K;
    for (int i = 1; i <= N; ++ i) {
        int X;
        cin >> X;
        tree[i].resize(X);
        for (int j = 0; j < X; ++ j) {
            int col;
            cin >> col;
            ++ colors[i][col];
        }
        for (int j = 0; j < X; ++ j)
            cin >> tree[i][j];
    }
    memset(ans, -1, sizeof ans);
    ans[0] = 1;
    for (int i = 1; i <= N; ++ i) {
        ans[i] = 1;
        while (!works())
            ++ ans[i];
    }
    for (int i = 1; i <= N; ++ i)
        cout << ans[i] << " \n"[i == N];
    return 0;
}
