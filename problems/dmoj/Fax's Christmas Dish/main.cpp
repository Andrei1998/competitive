#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300000 + 5;
int N, M, D;

vector <int> graph[NMAX];
int d[NMAX];
bool haveIt[NMAX];

bool works(int D) {
    for (int i = 1; i <= N; ++ i)
        haveIt[i] = false;
    for (int i = 1; i <= D; ++ i)
        haveIt[d[i]] = true;
    for (int node = N; node; -- node)
        if (!haveIt[node]) {
            int cnt = 0;
            for (auto it: graph[node])
                cnt += haveIt[it];
            if (!graph[node].empty() && cnt == graph[node].size())
                haveIt[node] = true;
        }
    return haveIt[1];
}

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N >> M >> D;
    for (int i = 1; i <= M; ++ i) {
        int who;
        cin >> who;
        int cnt;
        cin >> cnt;
        while (cnt --) {
            int son;
            cin >> son;
            graph[who].push_back(son);
        }
    }
    for (int i = 1; i <= D; ++ i)
        cin >> d[i];

    int st = 1, dr = D, ans = D + 1;
    while (st <= dr) {
        int mid = (st + dr) / 2;
        if (works(mid)) {
            ans = mid;
            dr = mid - 1;
        }
        else
            st = mid + 1;
    }

    if (ans == D + 1)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}
