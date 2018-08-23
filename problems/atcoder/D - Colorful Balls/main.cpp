#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int MOD = 1000000000 + 7;

int ridica(int a, int b) {
    if (!b)
        return 1;
    else if (b & 1)
        return (1LL * a * ridica(a, b - 1)) % MOD;
    else {
        int aux = ridica(a, b >> 1);
        return (1LL * aux * aux) % MOD;
    }
}

const int NMAX = 200000 + 5;

int facts[2 * NMAX + 5];
int inv_facts[2 * NMAX + 5];

void precompute() {
    facts[0] = 1;
    for (int i = 1; i < 2 * NMAX; ++ i)
        facts[i] = (1LL * i * facts[i - 1]) % MOD;

    inv_facts[2 * NMAX - 1] = ridica(facts[2 * NMAX - 1], MOD - 2);
    for (int i = 2 * NMAX - 2; i >= 0; -- i)
        inv_facts[i] = ((i + 1LL) * inv_facts[i + 1]) % MOD;
}

int comb(int a, int b) {
    return ((1LL * facts[a] * inv_facts[b]) % MOD * inv_facts[a - b]) % MOD;
}

vector <int> graph[NMAX];
vector <int> freq[NMAX];

map <int, int> colCnt;

int N, X, Y;
int w[NMAX];
int c[NMAX];

bool tryAddEdge(int a, int b) {
    if (c[a] == c[b]) {
        if (w[a] + w[b] <= X) {
            graph[a].push_back(b);
            graph[b].push_back(a);
            return true;
        }
    }
    else {
        if (w[a] + w[b] <= Y) {
            graph[a].push_back(b);
            graph[b].push_back(a);
            return true;
        }
    }
    return false;
}

struct MyCmp {
public:
    inline bool operator()(int a, int b) {
        return w[a] < w[b];
    }
};

bool vis[NMAX];
int all;
void dfs(int node) {
    vis[node] = true;
    colCnt[c[node]] ++;
    ++ all;
    for (auto it: graph[node])
        if (!vis[it])
            dfs(it);
}

int main()
{
    precompute();
    cin >> N >> X >> Y;

    for (int i = 1; i <= N; ++ i) {
        cin >> c[i] >> w[i];
        freq[c[i]].push_back(i);
    }

    int lowest = 2E9;
    int who = -1;
    int glob = -1;
    for (int c = 1; c <= N; ++ c)
        if (!freq[c].empty()) {
            sort(freq[c].begin(), freq[c].end(), MyCmp());
            for (int j = 1; j < freq[c].size(); ++ j) {
                !tryAddEdge(freq[c][0], freq[c][j]))
            }

            if (w[freq[c][0]] < lowest) {
                lowest = w[freq[c][0]];
                who = freq[c][0];
                glob = nope;
            }
        }

    for (int i = 1; i <= N; ++ i) {
        if (i != who)
            tryAddEdge(i, who);
        if (glob != -1) {
            tryAddEdge(i, glob);
        }
    }

    int ans = 1;
    for (int i = 1; i <= N; ++ i)
        if (!vis[i]) {
            all = 0;
            colCnt.clear();
            dfs(i);

            for (auto it: colCnt) {
                ans = (1LL * ans * comb(all, it.second)) % MOD;
                all -= it.second;
            }
        }

    cout << ans << '\n';
    return 0;
}
