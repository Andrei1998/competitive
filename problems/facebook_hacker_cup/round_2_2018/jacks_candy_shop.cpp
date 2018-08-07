#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

int N, M, A, B;
lint ans;

const int NMAX = 2000000 + 5;
int C[NMAX];
int cnt[NMAX];
vector <int> graph[NMAX];

multiset <int> *ms[NMAX];

void transfer(multiset <int> &ms1, multiset <int> &ms2) {
    for (auto it: ms1)
        ms2.insert(it);
}

void dfs(int node) {
    pair <int, int> best(-1, -1);
    for (auto it: graph[node]) {
        dfs(it);
        best = max(best, make_pair((int)ms[it] -> size(), it));
    }

    if (best.first == -1)
        ms[node] = new multiset <int>();
    else
        ms[node] = ms[best.second];
    ms[node] -> insert(node - 1);

    for (auto it: graph[node])
        if (it != best.second)
            transfer(*ms[it], *ms[node]);

    while (cnt[node] > 0 && ms[node] -> size() > 0) {
        cnt[node] --;
        auto it = ms[node] -> end();
        it --;
        ans += *it;
        ms[node] -> erase(it);
    }
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;
    for (int t = 1; t <= T; ++ t) {
        ans = 0;
        cin >> N >> M >> A >> B;
        for (int i = 1; i <= N; ++ i)
            cnt[i] = 0, graph[i].clear(), ms[i] = NULL;
        for (int i = 2; i <= N; ++ i) {
            int father;
            cin >> father;
            ++ father;
            graph[father].push_back(i);
        }
        for (int i = 0; i < M; ++ i) {
            C[i] = (1LL * A * i + B) % N + 1;
            ++ cnt[C[i]];
        }
        dfs(1);
        delete ms[1];
        cout << "Case #" << t << ": " << ans << endl;
    }
    return 0;
}
