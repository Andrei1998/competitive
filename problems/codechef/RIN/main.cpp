#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

template <const int NMAX, const int MMAX>
class MaxFLow {
public:
    MaxFLow() { m = 0; }

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

const int NMAX = 100 + 5;
const int MMAX = NMAX * NMAX;
const int INF = NMAX * MMAX;

int N, M, K;
int mat[NMAX][NMAX];

vector <int> graph[NMAX];
int inDeg[NMAX];

int label[NMAX][NMAX];

MaxFLow <NMAX * NMAX, 2 * MMAX> flow;

int main()
{
    cin >> N >> M >> K;

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= M; ++ j)
            cin >> mat[i][j];

    while (K --) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        ++ inDeg[b];
    }

    int sz = 0;
    for (int j = 1; j <= M; ++ j)
        for (int i = 1; i <= N; ++ i)
            label[i][j] = ++ sz;

    int S = ++ sz;
    int T = ++ sz;
    flow.setS(S);
    flow.setT(T);
    flow.setN(sz);

    //Internal edges
    for (int j = 1; j < M; ++ j) {
        for (int i = 1; i <= N; ++ i) {
            for (auto it: graph[i])
                flow.addEdge(label[i][j], label[it][j + 1], INF);

            if (mat[i][j + 1] != -1)
                flow.addEdge(label[i][j], label[i][j + 1], 100 - mat[i][j + 1]);
            else
                flow.addEdge(label[i][j], label[i][j + 1], INF);
        }
    }

    //Initial edges
    for (int i = 1; i <= N; ++ i)
        if (inDeg[i] || mat[i][1] == -1)
            flow.addEdge(S, label[i][1], INF);
        else
            flow.addEdge(S, label[i][1], 100 - mat[i][1]);

    //Final edges
    for (int i = 1; i <= N; ++ i)
        flow.addEdge(label[i][M], T, INF);

    cout << fixed << setprecision(2) << 100 - 1.0 * flow.computeFlow() / N << '\n';
    return 0;
}
