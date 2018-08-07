#include <iostream>
#include <vector>

//23:10
using namespace std;

const int NMAX = 300000 + 5;
const int INF = 1E9 + 15;

int N;
int w[NMAX];
vector <int> graph[NMAX];

//Max
int dpMax[NMAX];
int bestMax[NMAX];

//Min
int dpMin[NMAX];
int bestMin[NMAX];

void dfs1(int node, int father) {
    dpMax[node] = w[node];
    dpMin[node] = w[node];
    bestMax[node] = -INF;
    bestMin[node] = INF;
    for (auto it: graph[node])
        if (it != father) {
            dfs1(it, node);
            dpMax[node] += max(0, dpMax[it]);
            dpMin[node] += min(0, dpMin[it]);
            bestMax[node] = max(bestMax[node], bestMax[it]);
            bestMin[node] = min(bestMin[node], bestMin[it]);
        }
    bestMax[node] = max(bestMax[node], dpMax[node]);
    bestMin[node] = min(bestMin[node], dpMin[node]);
}

long long int ans;
void dfs2(int node, int father) {
    int sumMax = w[node];
    int sumMin = w[node];
    for (auto it: graph[node]) {
        sumMax += max(0, dpMax[it]);
        sumMin += min(0, dpMin[it]);
    }

    for (auto son: graph[node])
        if (son != father) {
            int oldDpMaxNode = dpMax[node];
            int oldDpMinNode = dpMin[node];
            dpMax[node] = sumMax - max(0, dpMax[son]);
            dpMin[node] = sumMin - min(0, dpMin[son]);

            int oldDpMaxSon = dpMax[son];
            int oldDpMinSon = dpMin[son];
            dpMax[son] += max(0, dpMax[node]);
            dpMin[son] += min(0, dpMin[node]);

            dfs2(son, node);

            ans = max(ans, 1LL * bestMin[son] * dpMin[node]);
            ans = max(ans, 1LL * bestMax[son] * dpMax[node]);

            dpMax[son] = oldDpMaxSon;
            dpMax[node] = oldDpMaxNode;
            dpMin[son] = oldDpMinSon;
            dpMin[node] = oldDpMinNode;
        }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> w[i];

    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs1(1, 0);

    ans = 1LL * w[1] * w[2];
    dfs2(1, 0);

    cout << ans << '\n';
    return 0;
}
