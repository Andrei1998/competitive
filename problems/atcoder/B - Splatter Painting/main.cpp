#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NMAX = 100000 + 5;

vector <int> graph[NMAX];

int queryD[NMAX];
int queryV[NMAX];
int queryC[NMAX];

int color[NMAX];
bool vis[NMAX][11];

queue <pair <int, int> > q;
void bfs(int node, int cl, int maxD) {
    q.push(make_pair(node, maxD));
    vis[node][maxD] = true;

    if (color[node] == 0)
        color[node] = cl;

    while (!q.empty()) {
        pair <int, int> aux = q.front();
        q.pop();

        if (aux.second == 0)
            continue;

        for (auto it: graph[aux.first])
            if (!vis[it][aux.second - 1]) {
                vis[it][aux.second - 1] = true;
                q.push(make_pair(it, aux.second - 1));

                if (color[it] == 0)
                    color[it] = cl;
            }
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int Q = 0;
    cin >> Q;
    for (int i = 1; i <= Q; ++ i)
        cin >> queryV[i] >> queryD[i] >> queryC[i];

    for (int i = Q; i; -- i)
        bfs(queryV[i], queryC[i], queryD[i]);

    for (int i = 1; i <= N; ++ i)
        cout << color[i] << '\n';
    return 0;
}
