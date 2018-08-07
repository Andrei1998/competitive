/*
ID: andreip3
LANG: C++14
TASK: race3
*/
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100 + 5;
int N;
vector <int> graph[NMAX];
vector <int> graphInv[NMAX];

bitset <NMAX> dominates[NMAX];
bool inQueue[NMAX];

vector <int> tree[NMAX];

int tmp;
int mark[NMAX];

void dfs(int node) {
    mark[node] = tmp;
    for (auto it: tree[node])
        dfs(it);
}

bool dfs2(int node) {
    for (auto it: graph[node])
        if (mark[it] != tmp)
            return false;
    for (auto it: tree[node])
        if (!dfs2(it))
            return false;
    return true;
}

bool works(int node) {
    ++ tmp;
    dfs(node);
    return dfs2(node);
}

int main() {
    freopen("race3.in", "r", stdin);
    freopen("race3.out", "w", stdout);

    while (1) {
        int val;
        cin >> val;
        if (val == -1)
            break;
        while (val != -2) {
            graph[N].push_back(val);
            graphInv[val].push_back(N);
            cin >> val;
        }
        ++ N;
    }

    // Dominator tree
    dominates[0][0] = 1;
    for (int i = 1; i < N; ++ i)
        dominates[i].set();

    queue <int> q;
    for (auto it: graph[0])
        q.push(it), inQueue[it] = true;
    while (!q.empty()) {
        const int node = q.front();
        inQueue[node] = false;
        q.pop();
        int cnt = dominates[node].count();
        for (auto it: graphInv[node])
            dominates[node] &= dominates[it];
        dominates[node][node] = true;
        if (dominates[node].count() < cnt)
            for (auto it: graph[node])
                if (it && !inQueue[it])
                    q.push(it), inQueue[it] = true;
    }

    vector <int> ans;
    for (int i = 1; i + 1 < N; ++ i)
        if (dominates[N - 1][i])
            ans.push_back(i);
    cout << ans.size();
    for (int i = 0; i < ans.size(); ++ i)
        cout << ' ' << ans[i];
    cout << '\n';

    // Find the dominator tree explicitly
    for (int i = 1; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if (i != j && dominates[i][j] && (dominates[i] ^ dominates[j]).count() == 1)
                tree[j].push_back(i);

    vector <int> ans2;
    for (auto node: ans)
        if (works(node))
            ans2.push_back(node);
    cout << ans2.size();
    for (int i = 0; i < ans2.size(); ++ i)
        cout << ' ' << ans2[i];
    cout << '\n';
    return 0;
}
