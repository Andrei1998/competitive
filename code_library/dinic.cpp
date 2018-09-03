#include <bits/stdc++.h>

using namespace std;

template <class T>
class MaxFlow {
  public:
    MaxFlow(int _N, int _src, int _dest): src(_src), dest(_dest) { setN(_N); }
    void setN(int _N) { N = _N, graph.resize(N), index.resize(N); }
    void setSrc(int _src) { src = _src; }
    void setDest(int _dest) {dest = _dest; }
    int getN() { return N; }
    int getSrc() { return src; }
    int getDest() { return dest; }

    void addEdge(int from, int to, T forwardCap, T backwardCap = 0) {
        //assert(0 <= from && from < N && 0 <= to && to < N);
        edges.emplace_back(from, to, 0, forwardCap);
        edges.emplace_back(to, from, 0, backwardCap);
        graph[from].push_back(edges.size() - 2);
        graph[to].push_back(edges.size() - 1);
    }
    void clear() { edges.clear(), graph.clear(); }
    void reset() { for (auto &edg: edges) edg.flow = 0; }

    T maxflow() {
        return dinic();
    }
    vector <int> minCut() {
        vector <int> cut;
        for (int i = 0; i < N; ++i)
            if (dist[i] > 0)
                cut.push_back(i);
        return cut;
    }

  private:
    static const T EPS = (T) 1E-9;

    struct Edge {
        int from, to;
        T flow, cap;
        Edge(int _from = 0, int _to = 0, T _flow = 0, T _cap = 0):
            from(_from), to(_to), flow(_flow), cap(_cap) {}
        int other(int node) { return from ^ to ^ node; }
    };
    int N, src, dest;
    vector <Edge> edges;
    vector <vector <int> > graph;
    vector <int> index, dist;

    bool bfs() {
        dist.clear(), dist.resize(N, 0);
        dist[src] = 1;
        queue <int> q;
        q.push(src);
        while (!q.empty()) {
            const int node = q.front(); q.pop();
            for (const auto edg: graph[node]) {
                const int son = edges[edg].other(node);
                if (!dist[son] && edges[edg].cap - edges[edg].flow > EPS) {
                    dist[son] = 1 + dist[node];
                    q.push(son);
                }
            }
        }
        return dist[dest] > 0;
    }
    T dfs(int node, T flowToPush) {
        if (node == dest)
            return flowToPush;
        T res = 0;
        while (index[node] < (int)graph[node].size()) {
            const int edg = graph[node][index[node]];
            const int son = edges[edg].other(node);
            if (dist[son] == 1 + dist[node] && edges[edg].cap - edges[edg].flow > 0) {
                T pushed = dfs(son, min(flowToPush - res, edges[edg].cap - edges[edg].flow));
                if (pushed > EPS) {
                    edges[edg].flow += pushed;
                    edges[edg ^ 1].flow -= pushed;
                    res += pushed;
                    if (flowToPush - res <= EPS)
                        break;
                }
            }
            ++index[node];
        }
        return res;
    }
    T dinic() {
        T flow = 0;
        while (bfs()) {
            for (int i = 0; i < N; ++i)
                index[i] = 0;
            while (1) {
                T pushed = dfs(src, numeric_limits <T> :: max());
                if (pushed > EPS)
                    flow += pushed;
                else
                    break;
            }
        }
        return flow;
    }
};

int main() {
    int N = 0, M = 0;
    cin >> N >> M;
    MaxFlow <int> mf(N, 0, N - 1); // mf(N, src, dest)
    while (M--) {
        int a, b, c;
        cin >> a >> b >> c; --a, --b;
        mf.addEdge(a, b, c);
    }
    cout << mf.maxflow() << endl;
    return 0;
}
