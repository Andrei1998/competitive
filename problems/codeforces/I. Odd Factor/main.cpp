#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int NMAX = 100000 + 5;

int N, M;
vector <int> graph[NMAX];
bool vis[NMAX];

vector <pair <int, int> > sol;
bool fail;

bool dfs(int node, int father) {
    vis[node] = true;

    int cnt = 0;
    for (auto it: graph[node])
        if (!vis[it])
            cnt += dfs(it, node);
    cnt %= 2;

    if (cnt == 0) {
        if (!father)
            fail = true;
        sol.push_back(make_pair(node, father));
    }
    return cnt ^ 1;
}

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= N; ++ i)
        if (!vis[i])
            dfs(i, 0);

    if (fail)
        cout << "-1\n";
    else {
        cout << sol.size() << '\n';
        for (auto it: sol)
            cout << it.first << ' ' << it.second << '\n';
    }
    return 0;
}
