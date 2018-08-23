#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 100000 + 5;
typedef long long int lint;

int N, M;
vector <int> graph[NMAX];

bool vis[NMAX];
bool color[NMAX];

bool odd;
void dfs(int node) {
    vis[node] = true;
    for (auto it: graph[node])
        if (!vis[it]) {
            color[it] = color[node] ^ 1;
            dfs(it);
        }
        else if (color[it] != (color[node] ^ 1))
            odd = true;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int iz = 0, c[2] = {0};
    for (int i = 1; i <= N; ++ i)
        if (graph[i].empty())
            ++ iz;
        else if (!vis[i]) {
            odd = false;
            dfs(i);
            ++ c[odd];
        }

    lint ans = 2LL * c[0] * c[1] + 1LL * c[1] * c[1] + 2LL * c[0] * c[0];
    for (int i = 1; i <= iz; ++ i)
        ans += 2 * (N --) - 1;
    cout << ans << '\n';
    return 0;
}
