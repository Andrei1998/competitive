#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>

#define double long double
using namespace std;

const int NMAX = 2000 + 5;
const int MMAX = 50 + 5;
const int MOD = 1000000000 + 7;

int raise(int a, int b) {
    if (!b)
        return 1;
    else if (b & 1)
        return (1LL * a * raise(a, b - 1)) % MOD;
    else {
        int aux = raise(a, b >> 1);
        return (1LL * aux * aux) % MOD;
    }
}

int inv(int nr) {
    return raise(nr, MOD - 2);
}

int N, M;
int mat[NMAX][MMAX];
int cost[NMAX];

int ord[NMAX];

bool cmp(const int &a, const int &b) {
    if (cost[a] != cost[b])
        return cost[a] < cost[b];
    else
        return a < b;
}

void mult(int lin, int alpha) {
    for (int i = 1; i <= M; ++ i)
        mat[lin][i] = (1LL * mat[lin][i] * alpha) % MOD;
}

void subtract(int lin1, int alpha, int lin2) {
    for (int i = 1; i <= M; ++ i) {
        mat[lin1][i] = (mat[lin1][i] - 1LL * alpha * mat[lin2][i]) % MOD;
        if (mat[lin1][i] < 0)
            mat[lin1][i] += MOD;
    }
}

int main()
{
    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= M; ++ j)
            cin >> mat[i][j];
    for (int i = 1; i <= N; ++ i) {
        cin >> cost[i];
        ord[i] = i;
    }

    sort(ord + 1, ord + N + 1, cmp);

    int ans = 0;
    vector <int> vects;

    for (int i = 1; i <= N && vects.size() < M; ++ i) {
        int col;
        for (col = 1; col <= M; ++ col)
            if (mat[ord[i]][col])
                break;

        if (col > M)
            continue;

        ans += cost[ord[i]];
        vects.push_back(ord[i]);

        mult(ord[i], inv(mat[ord[i]][col]));
        for (int k = i + 1; k <= N; ++ k)
            subtract(ord[k], mat[ord[k]][col], ord[i]);
    }

    if (vects.size() < M) {
        cout << "0\n";
        return 0;
    }

    sort(vects.begin(), vects.end());

    cout << ans << '\n';
    for (auto it: vects)
        cout << it << '\n';
    return 0;
}
