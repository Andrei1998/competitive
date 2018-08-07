/*
ID: andreip3
LANG: C++14
TASK: ditch
*/

#include <bits/stdc++.h>

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

const int NMAX = 200 + 5;
const int MMAX = 200 + 5;
MaxFLow <NMAX, MMAX> f;

int main() {
    ifstream cin("ditch.in");
    ofstream cout("ditch.out");

    int n, m;
    cin >> m >> n;

    f.setN(n);
    f.setS(1);
    f.setT(n);

    int a, b, c;
    while (m --) {
        cin >> a >> b >> c;
        f.addEdge(a, b, c);
    }

    cout << f.computeFlow() << '\n';
    return 0;
}
