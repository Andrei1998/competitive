#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

const int NMAX = 100000 + 5;

int N, M, K;
vector <pair <int, int> > graph[NMAX];

int father[NMAX][17];
int first[NMAX];
int last[NMAX];
int h[NMAX];
int cnt;

inline bool cmp(const int &a, const int &b) {
    return first[a] < first[b];
}

void dfs(int node) {
    first[node] = ++ cnt;
    for (int i = 1; i < 17; ++ i)
        father[node][i] = father[father[node][i - 1]][i - 1];

    for (auto it: graph[node])
        if (it.first != father[node][0]) {
            father[it.first][0] = node;
            h[it.first] = 1 + h[node];
            dfs(it.first);
        }
    last[node] = cnt;
}

int lca(int a, int b) {
    if (h[a] > h[b])
        swap(a, b);

    for (int i = 16; i >= 0; -- i)
        if (father[b][i] && h[father[b][i]] >= h[a])
            b = father[b][i];

    if (a == b)
        return a;

    for (int i = 16; i >= 0; -- i)
        if (father[a][i] && father[a][i] != father[b][i]) {
            a = father[a][i];
            b = father[b][i];
        }

    return father[a][0];
}

int sPart[NMAX];
bool sol[NMAX];

void dfsSum(int node) {
    for (auto it: graph[node])
        if (it.first != father[node][0]) {
            dfsSum(it.first);
            sPart[node] += sPart[it.first];

            if (sPart[it.first] >= K)
                sol[it.second] = true;
        }
}

int main()
{
    //freopen("railway.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> K;

    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(make_pair(b, i));
        graph[b].push_back(make_pair(a, i));
    }

    dfs(1);

    stack <int> stk;
    vector <int> nodes;
    while (M --) {
        int nr;
        cin >> nr;
        nodes.resize(nr);
        for (int i = 0; i < nr; ++ i)
            cin >> nodes[i];

        sort(nodes.begin(), nodes.end(), cmp);
        int b = nodes.size();
        for (int i = 0; i + 1 < b; ++ i)
            nodes.push_back(lca(nodes[i], nodes[i + 1]));
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.resize(unique(nodes.begin(), nodes.end()) - nodes.begin());

        while (!stk.empty())
            stk.pop();
        stk.push(nodes[0]);

        for (int i = 1; i < nodes.size(); ++ i) {
            int node = nodes[i];
            while (!stk.empty() && !(first[stk.top()] <= first[node] && first[node] <= last[stk.top()]))
                stk.pop();

            -- sPart[stk.top()];
            ++ sPart[node];
            stk.push(node);
        }
    }

    dfsSum(1);

    vector <int> ans;
    for (int i = 1; i < N; ++ i)
        if (sol[i])
            ans.push_back(i);
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++ i)
        cout << ans[i] << " \n"[i + 1 == ans.size()];
    return 0;
}
