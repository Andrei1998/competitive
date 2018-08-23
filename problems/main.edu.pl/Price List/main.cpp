#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
#include <utility>

//14:33
using namespace std;

const int NMAX = 100000 + 5;

vector <int> normGraph[NMAX];
set <int> graph[NMAX];

int ans[NMAX];
int minNodes[NMAX];

int main()
{
    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int N, M, start, A, B;
    cin >> N >> M >> start >> A >> B;

    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;

        graph[a].insert(b);
        graph[b].insert(a);
        normGraph[a].push_back(b);
        normGraph[b].push_back(a);
    }

    queue <int> q;
    q.push(start);
    minNodes[start] = 1;

    //Allow A
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (vector <int> :: iterator it = normGraph[node].begin(); it != normGraph[node].end(); ++ it)
            if (!minNodes[*it]) {
                q.push(*it);
                minNodes[*it] = 1 + minNodes[node];
            }
    }

    for (int i = 1; i <= N; ++ i) {
        ans[i] = (minNodes[i] - 1) / 2 * B + ((minNodes[i] - 1) % 2) * A;
        ans[i] = min(ans[i], (minNodes[i] - 1) * A);
        minNodes[i] = 0;
    }

    //Disallow A
    q.push(start);
    minNodes[start] = 1;

    for (vector <int> :: iterator it = normGraph[start].begin(); it != normGraph[start].end(); ++ it)
        graph[*it].erase(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (vector <int> :: iterator it = normGraph[node].begin(); it != normGraph[node].end(); ++ it)
            for (set <int> :: iterator it2 = graph[*it].begin(); it2 != graph[*it].end(); )
                if (!graph[node].count(*it2)) {
                    minNodes[*it2] = 1 + minNodes[node];
                    q.push(*it2);

                    for (vector <int> :: iterator it3 = normGraph[*it2].begin(); it3 != normGraph[*it2].end(); ++ it3)
                        if (*it3 != *it)
                            graph[*it3].erase(*it2);

                    graph[*it].erase(it2 ++);
                }
                else
                    ++ it2;
    }
    for (int i = 1; i <= N; ++ i)
        if (minNodes[i])
            ans[i] = min(ans[i], B * (minNodes[i] - 1));

    for (int i = 1; i <= N; ++ i)
        cout << ans[i] << '\n';
    return 0;
}
