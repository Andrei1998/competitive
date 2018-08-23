/*
ID: andreip3
LANG: C++14
TASK: nuggets
*/

#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10 + 5;
const int VMAX = 256 + 6;

int N;
int v[NMAX];
int when[VMAX];
bool vis[VMAX];

int main() {
    freopen("nuggets.in", "r", stdin);
    freopen("nuggets.out", "w", stdout);
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    sort(v + 1, v + N + 1);

    when[0] = 0;
    for (int i = 1; i < v[1]; ++ i)
        when[i] = 2E9 + 15;

    priority_queue <int> pq;
    pq.push(0);

    int cnt = 0;
    int last;
    while (!pq.empty()) {
        int node = -pq.top();
        pq.pop();
        if (vis[node % v[1]])
            continue;
        vis[node % v[1]] = true;
        last = node;
        node %= v[1];

        ++ cnt;
        for (int i = 2; i <= N; ++ i)
            if (when[node] + v[i] < when[(node + v[i]) % v[1]]) {
                when[(node + v[i]) % v[1]] = when[node] + v[i];
                pq.push(-when[(node + v[i]) % v[1]]);
            }
    }
    if (last == 0)
        last = 1;
    if (cnt < v[1])
        cout << "0\n";
    else
        cout << last - v[1] << '\n';
    return 0;
}
