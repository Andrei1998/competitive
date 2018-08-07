#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 100000 + 5;

int N, K;
int a[NMAX];

vector <int> graph[NMAX];

int h[NMAX];

int ans;
void dfs(int node) {
    for (auto it: graph[node]) {
        dfs(it);
        if (h[it] == K - 1)
            ans += (node > 1);
        else
            h[node] = max(h[node], 1 + h[it]);
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; ++ i)
        cin >> a[i];

    ans = (a[1] > 1);
    for (int i = 2; i <= N; ++ i)
        graph[a[i]].push_back(i);
    dfs(1);

    cout << ans << '\n';
    return 0;
}
