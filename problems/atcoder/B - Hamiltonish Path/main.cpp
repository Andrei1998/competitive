#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int NMAX = 100000 + 5;
vector <int> graph[NMAX];

deque <int> sol;
bool vis[NMAX];

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

    sol.push_back(1);
    vis[1] = 1;

    int node = 1;
    while (1) {
        bool found = false;
        for (auto it: graph[node])
            if (!vis[it]) {
                node = it;
                vis[node] = true;
                sol.push_back(node);
                found = true;
                break;
            }
        if (!found)
            break;
    }

    node = 1;
    while (1) {
        bool found = false;
        for (auto it: graph[node])
            if (!vis[it]) {
                node = it;
                vis[node] = true;
                sol.push_front(node);
                found = true;
                break;
            }
        if (!found)
            break;
    }

    cout << sol.size() << '\n';
    for (int i = 0; i < sol.size(); ++ i)
        cout << sol[i] << " \n"[i + 1 == sol.size()];
    return 0;
}
