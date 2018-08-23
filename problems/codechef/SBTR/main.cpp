#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#include <queue>
#include <set>

using namespace std;

typedef long long int lint;

struct Input {
    int N;
    vector <int> costs;
    vector <pair <int, int> > edges;

    friend istream& operator>>(istream &f, Input &input) {
        int M = 0;
        f >> input.N >> M;
        input.costs.resize(input.N);
        for (int i = 0; i < input.N; ++ i)
            f >> input.costs[i];
        input.edges.resize(M);
        for (int i = 0; i < M; ++ i) {
            f >> input.edges[i].first >> input.edges[i].second;
            input.edges[i].first --;
            input.edges[i].second --;
        }
        return f;
    }
};

struct Output {
    int cost;
    vector <int> nodes;

    Output() {
        cost = 0;
    }
    Output(int _cost, vector <int> _nodes):
        cost(_cost), nodes(_nodes) {}

    friend ostream& operator<<(ostream &g, const Output &output) {
        g << output.nodes.size() << '\n';
        for (int i = 0; i < static_cast <int>(output.nodes.size()); ++ i)
            g << (output.nodes[i] + 1) << " \n"[i + 1 == static_cast <int>(output.nodes.size())];
        return g;
    }

    friend bool operator<(const Output &o1, const Output &o2) {
        return o1.cost < o2.cost;
    }
};

Output solveBlank(const Input &input) {
    //Initialize
    const int &N = input.N;
    const vector <int> &costs = input.costs;

    //Solve
    Output output;
    for (int i = 0; i < N; ++ i) {
        output.cost += costs[i];
        output.nodes.push_back(i);
    }
    return output;
}

Output solveComplete(const Input &input) {
    //Initialize
    const int &N = input.N;
    const vector <int> &costs = input.costs;

    //Solve
    vector <pair <int, int> > costNodePairs(N);
    for (int i = 0; i < input.N; ++ i)
        costNodePairs[i] = {costs[i], i};
    sort(costNodePairs.begin(), costNodePairs.end());

    Output output;
    for (int i = 0; i + 2 < N; ++ i) {
        output.cost += costNodePairs[i].first;
        output.nodes.push_back(costNodePairs[i].second);
    }
    return output;
}

Output solveAlmostTree(const Input &input) {
    //Initialize
    const int &N = input.N;
    const vector <int> &costs = input.costs;
    const vector <pair <int, int> > &edges = input.edges;

    vector <vector <int> > graph(N);
    vector <int> degree(N);
    for (auto edg: edges) {
        graph[edg.first].push_back(edg.second);
        graph[edg.second].push_back(edg.first);
        ++ degree[edg.first];
        ++ degree[edg.second];
    }

    //Solve
    queue <int> leaves;
    vector <int> dp(N);
    vector <vector <int> > downwardsGraph(N);
    for (int i = 0; i < N; ++ i) {
        if (degree[i] == 1)
            leaves.push(i);
        dp[i] = costs[i];
    }

    vector <bool> erased(N);
    while (!leaves.empty()) {
        int leaf = leaves.front();
        erased[leaf] = true;
        leaves.pop();

        for (auto it: graph[leaf])
            if (!erased[it]) {
                -- degree[it];
                dp[it] += dp[leaf];
                downwardsGraph[it].push_back(leaf);

                if (degree[it] == 1)
                    leaves.push(it);
            }
    }

    int least = 2E9 + 15;
    int leastNode = -1;
    for (int i = 0; i < N; ++ i)
        if (!erased[i]) {
            if (dp[i] < least) {
                least = dp[i];
                leastNode = i;
            }
        }

    Output output(least, {leastNode});
    for (int i = 0; i < static_cast <int>(output.nodes.size()); ++ i)
        for (auto son: downwardsGraph[output.nodes[i]])
            output.nodes.push_back(son);
    return output;
}

Output solveCycle(const vector <int> &costs, const vector <int> &cycle) {
    const int N = cycle.size();

    vector <int> dp[2];
    vector <bool> take[2];
    dp[0].resize(N + 1);
    take[0].resize(N + 1);
    dp[1].resize(N + 1);
    take[1].resize(N + 1);

    dp[0][1] = 0;
    dp[1][1] = costs[cycle[1]];
    take[0][1] = false;
    take[1][1] = false;

    for (int i = 2; i <= N; ++ i) {
        dp[0][i] = dp[0][i - 1];
        take[0][i] = false;
        if (dp[1][i - 1] > dp[0][i]) {
            dp[0][i] = dp[1][i - 1];
            take[0][i] = true;
        }

        if (i < N) {
            dp[1][i] = costs[cycle[i]] + dp[0][i - 1];
            take[1][i] = false;
        }
    }

    Output output;
    int where = N;
    bool type = 0;

    while (where >= 0) {
        if (!type && where < N) {
            output.cost += costs[cycle[where]];
            output.nodes.push_back(cycle[where]);
        }
        type = take[type][where];
        where --;
    }

    return output;
}

pair <bool, Output> solveWheel(const Input &input) {
    //Initialize
    const int &N = input.N;
    const vector <int> &costs = input.costs;
    const vector <pair <int, int> > &edges = input.edges;

    if (N < 4)
        return make_pair(false, Output());
    if (static_cast <int>(edges.size()) != 2 * N - 2)
        return make_pair(false, Output());

    vector <vector <int> > graph(N);
    vector <int> degree(N);
    for (auto edg: edges) {
        graph[edg.first].push_back(edg.second);
        graph[edg.second].push_back(edg.first);
        ++ degree[edg.first];
        ++ degree[edg.second];
    }

    //Solve
    int center = -1;
    for (int i = 0; i < N; ++ i)
        if (degree[i] + 1 == N) {
            center = i;
            break;
        }

    if (center == -1)
        return make_pair(false, Output());
    for (int i = 0; i < N; ++ i)
        if (i != center && degree[i] != 3)
            return make_pair(false, Output());

    int node = -1;
    for (int i = 0; i < N; ++ i)
        if (i != center) {
            node = i;
            break;
        }

    vector <bool> vis(N);
    vis[center] = true;

    queue <int> q;
    q.push(node);
    vis[node] = true;
    vector <int> cycle;
    bool first = true;
    while (!q.empty()) {
        node = q.front();
        cycle.push_back(node);
        q.pop();

        int cnt = 0;
        for (auto it: graph[node])
            if (!vis[it]) {
                ++ cnt;
                if (!first || cnt != 2) {
                    q.push(it);
                    vis[it] = true;
                }
            }
        first = false;
    }

    for (int i = 0; i < N; ++ i)
        if (!vis[i])
            return make_pair(false, Output());

    //We finally know it's clearly a wheel graph
    int minimum = 2E9 + 15, minimumNode = -1;
    for (int i = 0; i < N; ++ i)
        if (i != center && costs[i] < minimum) {
            minimum = costs[i];
            minimumNode = i;
        }

    Output sol1(costs[center] + minimum, {center, minimumNode}); //Remove center
    Output sol2 = solveCycle(costs, cycle); //Keep center, but remove node 0
    rotate(cycle.begin(), cycle.begin() + 1, cycle.end());
    Output sol3 = solveCycle(costs, cycle); //Keep center, but remove node 1
    return make_pair(true, min(sol1, min(sol2, sol3)));
}

void backtrSmall(lint mask, int cost, const int &N, const vector <int> &costs, const vector <lint> &adj, int &best, lint &bestMask, set <lint> vis) {
    if (vis.count(mask))
        return ;
    vis.insert(mask);

    bool found = false;
    for (int i = 0; i < N; ++ i)
        if (!(mask & (1LL << i))) {
            lint aux = (adj[i] & mask);
            if (!mask || (aux && !(aux & (aux - 1)))) {
                found = true;
                backtrSmall(mask | (1LL << i), cost - costs[i], N, costs, adj, best, bestMask, vis);
            }
        }

    if (!found) {
        if (cost < best) {
            best = cost;
            bestMask = (~mask) & ((1LL << N) - 1);
        }
    }
}

Output solveSmall(const Input &input) {
    //Initialize
    const int &N = input.N;
    const vector <int> &costs = input.costs;
    const vector <pair <int, int> > &edges = input.edges;

    vector <lint> adj(N);
    for (auto edg: edges) {
        adj[edg.first] |= (1LL << edg.second);
        adj[edg.second] |= (1LL << edg.first);
    }

    //Solve
    int cost = 0;
    for (int i = 0; i < N; ++ i)
        cost += costs[i];
    int best = cost;
    lint bestMask = (1LL << N) - 1;

    set <lint> vis;
    backtrSmall(0, cost, N, costs, adj, best, bestMask, vis);

    Output output;
    output.cost = best;
    for (int i = 0; i < N; ++ i)
        if (bestMask & (1LL << i))
            output.nodes.push_back(i);
    return output;
}

Output solveGreedyPqDegree(const Input &input, int root) {
    //Initialize
    const int &N = input.N;
    const vector <int> &costs = input.costs;
    const vector <pair <int, int> > &edges = input.edges;

    vector <vector <int> > graph(N);
    for (auto edg: edges) {
        graph[edg.first].push_back(edg.second);
        graph[edg.second].push_back(edg.first);
    }

    //Solve
    vector <int> degree(N);
    vector <int> treeNodes = {root};

    priority_queue <pair <int, pair <int, int> > > pq;
    degree[root] = 1;
    pq.push({-graph[root].size(), {costs[root], root}});

    while (!pq.empty()) {
        int node = pq.top().second.second;
        pq.pop();

        if (degree[node] > 1)
            continue;
        treeNodes.push_back(node);

        for (auto it: graph[node]) {
            ++ degree[it];
            if (degree[it] == 1)
                pq.push({-graph[it].size(), {costs[it], it}});
        }
    }

    vector <bool> freq(N);
    for (auto it: treeNodes)
        freq[it] = true;

    Output output;
    for (int i = 0; i < N; ++ i)
        if (!freq[i]) {
            output.cost += costs[i];
            output.nodes.push_back(i);
        }

    return output;
}


Output solveGreedyPqCost(const Input &input, int root) {
    //Initialize
    const int &N = input.N;
    const vector <int> &costs = input.costs;
    const vector <pair <int, int> > &edges = input.edges;

    vector <vector <int> > graph(N);
    for (auto edg: edges) {
        graph[edg.first].push_back(edg.second);
        graph[edg.second].push_back(edg.first);
    }

    //Solve
    vector <int> degree(N);
    vector <int> treeNodes = {root};

    priority_queue <pair <int, pair <int, int> > > pq;
    degree[root] = 1;
    pq.push({costs[root], {-graph[root].size(), root}});

    while (!pq.empty()) {
        int node = pq.top().second.second;
        pq.pop();

        if (degree[node] > 1)
            continue;
        treeNodes.push_back(node);

        for (auto it: graph[node]) {
            ++ degree[it];
            if (degree[it] == 1)
                pq.push({costs[it], {-graph[it].size(), it}});
        }
    }

    vector <bool> freq(N);
    for (auto it: treeNodes)
        freq[it] = true;

    Output output;
    for (int i = 0; i < N; ++ i)
        if (!freq[i]) {
            output.cost += costs[i];
            output.nodes.push_back(i);
        }

    return output;
}

Output solveGreedy(const Input &input) {
    //Initialize
    const int &N = input.N;

    //Solve
    vector <pair <int, int> > nodes;
    for (int i = 1; i < N; ++ i)
        nodes.push_back(make_pair(-input.costs[i], i));

    //Largest 75 nodes
    sort(nodes.begin(), nodes.end());
    //Another 75 random nodes
    if (nodes.size() > 75)
        random_shuffle(nodes.begin() + 75, nodes.end());

    Output output = min(solveGreedyPqDegree(input, 0), solveGreedyPqCost(input, 0));
    for (int i = 0; i < static_cast <int>(nodes.size()) && i < 2 * 75; ++ i) {
        output = min(output, solveGreedyPqDegree(input, nodes[i].second));
        output = min(output, solveGreedyPqCost(input, nodes[i].second));
    }
    return output;
}

Output solve(const Input &input) {
    if (input.N <= 20) //Small network
        return solveSmall(input);
    else if (static_cast <int>(input.edges.size()) == input.N * (input.N - 1) / 2) //Complete graph
        return solveComplete(input);
    else if (static_cast <int>(input.edges.size()) == input.N) //Almost tree
        return solveAlmostTree(input);
    else {
        pair <bool, Output> solWheel = solveWheel(input);
        if (solWheel.first) //Wheel graph
            return solWheel.second;
        else if (static_cast <int>(input.edges.size()) <= input.N + 3) //Close-enough tree
            return solveGreedy(input);
        else
            return solveGreedy(input);
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    Input input;
    cin >> input;
    Output output = solve(input);
    cout << output;
    return 0;
}
