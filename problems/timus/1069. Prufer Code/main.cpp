#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int NMAX = 7500 + 5;

int N;
int v[NMAX];
int deg[NMAX];
vector <int> graph[NMAX];

priority_queue <int> pq;

int main()
{
    N = 0;
    while (1) {
        cin >> v[++N];
        if (cin.eof())
            break;
    }

    for (int i = 1; i <= N - 2; ++ i)
        ++deg[v[i]];

    for (int i = 1; i <= N; ++i)
        if (!deg[i])
            pq.push(-i);

    for (int i = 1; i <= N - 2; ++i) {
        int node = -pq.top();
        pq.pop();

        graph[node].push_back(v[i]);
        graph[v[i]].push_back(node);

        --deg[v[i]];
        if (!deg[v[i]])
            pq.push(-v[i]);
    }

    int n1 = -pq.top(); pq.pop();
    int n2 = -pq.top(); pq.pop();

    graph[n1].push_back(n2);
    graph[n2].push_back(n1);

    for (int i = 1; i <= N; ++i) {
        sort(graph[i].begin(), graph[i].end());

        cout << i << ':';
        for (auto it: graph[i])
            cout << ' ' << it;
        cout << '\n';
    }
    return 0;
}
