#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 5000 + 5;

int N, K;
int a[NMAX];
vector <int> graph[NMAX];

int ans;
void dfs(int node, int father, int maxi, int mini) {
    if (father && maxi - mini >= K)
        ++ ans;

    for (auto it: graph[node])
        if (it != father)
            dfs(it, node, max(maxi, a[it]), min(mini, a[it]));
}

int main()
{
    cin >> N >> K;
    for (int i = 1; i <= N; ++ i)
        cin >> a[i];

    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= N; ++ i)
        dfs(i, 0, a[i], a[i]);
    cout << ans / 2 << '\n';
    return 0;
}
