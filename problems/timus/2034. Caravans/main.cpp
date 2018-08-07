#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 100000 + 5;

int N, M;
vector <int> graph[NMAX];
bool blocked[NMAX];

int S, F, R;

queue <int> q;
int bfs(int node, int dist[]) {
    for (int i = 1; i <= N; ++ i)
        dist[i] = 0;

    if (!blocked[node]) {
        dist[node] = 1;
        q.push(node);
    }

    while (!q.empty()) {
        node = q.front();
        q.pop();

        for (auto it: graph[node])
            if (!blocked[it] && !dist[it]) {
                dist[it] = 1 + dist[node];
                q.push(it);
            }
    }

    for (int i = 1; i <= N; ++ i)
        -- dist[i];
    return dist[F];
}

int distS[NMAX];
int distR[NMAX];

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

    cin >> S >> F >> R;

    int sf = bfs(S, distS);
    bfs(R, distR);

    int st = 0;
    int dr = N - 1;
    int ans = N;

    while (st <= dr) {
        int mid = (st + dr) >> 1;
        for (int i = 1; i <= N; ++ i)
            if (distR[i] <= mid)
                blocked[i] = true;
            else
                blocked[i] = false;

        int aux = bfs(S, distS);
        if (aux > sf || aux == -1) {
            ans = mid;
            dr = mid - 1;
        }
        else
            st = mid + 1;
    }

    cout << ans << '\n';
    return 0;
}
