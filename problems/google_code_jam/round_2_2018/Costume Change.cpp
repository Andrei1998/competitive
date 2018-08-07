#include <bits/stdc++.h>

// 3:19
using namespace std;

const int NMAX = 100 + 5;

int N;
int mat[NMAX][NMAX];

int lft[NMAX], rgt[NMAX];
bool vis[NMAX];

bool pairUp(int node, int label) {
    if (vis[node])
        return false;
    vis[node] = true;
    for (int i = 1; i <= N; ++ i)
        if (mat[node][i] == label && !rgt[i]) {
            lft[node] = i;
            rgt[i] = node;
            return true;
        }
    for (int i = 1; i <= N; ++ i)
        if (mat[node][i] == label && pairUp(rgt[i], label)) {
            lft[node] = i;
            rgt[i] = node;
            return true;
        }
    return false;
}

int solve(int label) {
    for (int i = 1; i <= N; ++ i)
        lft[i] = rgt[i] = vis[i] = 0;
    int ans = 0;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            ans += (mat[i][j] == label);

    bool ok = true;
    while (ok) {
        ok = false;
        for (int i = 1; i <= N; ++ i)
            vis[i] = false;
        for (int i = 1; i <= N; ++ i)
            if (!lft[i] && pairUp(i, label))
                ok = true;
    }

    for (int i = 1; i <= N; ++ i)
        if (lft[i])
            -- ans;

    return ans;
}

int test() {
    memset(mat, 0, sizeof mat);
    memset(lft, 0, sizeof lft);
    memset(rgt, 0, sizeof rgt);
    memset(vis, 0, sizeof vis);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            cin >> mat[i][j];

    int ans = 0;
    for (int i = -N; i <= N; ++ i)
        if (i != 0)
            ans += solve(i);
    return ans;
}

int main() {
    //freopen("data.in", "r", stdin);
    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << test() << '\n';
    return 0;
}
