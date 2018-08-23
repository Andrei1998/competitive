#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 3000 + 5;

vector <int> tree[NMAX];
int sz[NMAX];

unsigned short dp[NMAX][NMAX]; //dp[node][k]
unsigned char dp2[NMAX][NMAX]; //dp[son][k]

int getDp(int i, int j) {
    int val = (((int)dp[i][j]) + (((int)dp2[i][j]) << 16));
    return val & (((1 << 12)) - 1);
}

int getDp2(int i, int j) {
    int val = (((int)dp[i][j]) + (((int)dp2[i][j]) << 16));
    return val >> 12;
}

inline void setDp(int i, int j, int val) {
    dp[i][j] = (dp[i][j] & (~((1U << 12) - 1))) + val;
}

inline void setDp2(int i, int j, int val) {
    dp[i][j] = (dp[i][j] & (~(15U << 12))) + ((val & 15) << 12);
    dp2[i][j] = (unsigned char)(val >> 4);
}

void dfs(int node, int father) {
    if (father)
        tree[node].erase(find(tree[node].begin(), tree[node].end(), father));

    sz[node] = 1;
    for (vector <int> :: iterator it = tree[node].begin(); it != tree[node].end(); ++ it) {
        dfs(*it, node);
        sz[node] += sz[*it];
    }

    int otherSons = 0;
    for (int son = 0; son < tree[node].size(); ++ son) {
        for (int cnt = 0; cnt <= otherSons + sz[tree[node][son]]; ++ cnt)
            setDp2(son + 1, cnt, NMAX);

        for (int until = 0; until <= otherSons; ++ until)
            for (int cnt = 0; cnt <= sz[tree[node][son]]; ++ cnt) {
                int aux = getDp(tree[node][son], cnt) + getDp2(son, until);

                if (aux < getDp2(son + 1, cnt + until))
                    setDp2(son + 1, cnt + until, aux);
            }
        otherSons += sz[tree[node][son]];
    }

    setDp(node, 0, 1);
    for (int cnt = 1; cnt <= sz[node]; ++ cnt)
        setDp(node, cnt, getDp2(tree[node].size(), cnt - 1));
}

int main()
{
    //freopen("data.in", "r", stdin);
    //freopen("data.out", "w", stdout);

    int N;
    cin >> N;

    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0);

    int Q = 0;
    cin >> Q;

    while (Q --) {
        int k;
        cin >> k;

        int ans = getDp(1, k);
        for (int i = 2; i <= N; ++ i)
            if (sz[i] >= k)
                ans = min(ans, 1 + getDp(i, k));
        cout << ans << '\n';
    }
    return 0;
}
