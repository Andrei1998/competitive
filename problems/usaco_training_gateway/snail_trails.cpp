/*
ID: andreip3
LANG: C++14
TASK: snail
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int NMAX = 120 + 5;

int N;
char mat[NMAX][NMAX];

int dL[4] = {0, 1, 0, -1};
int dC[4] = {1, 0, -1, 0};

int ans;
void dfs(int l, int c, int dir, int cnt) {
    mat[l][c] = 'M';
    if (cnt > ans)
        ans = cnt;

    int newL = l + dL[dir], newC = c + dC[dir];
    if (mat[newL][newC] != 'M') {
        if (mat[newL][newC] == '#') {
            int l1 = l + dL[(dir + 3) % 4], c1 = c + dC[(dir + 3) % 4];
            int l2 = l + dL[(dir + 1) % 4], c2 = c + dC[(dir + 1) % 4];

            if (mat[l1][c1] == '.')
                dfs(l1, c1, (dir + 3) % 4, cnt + 1);
            if (mat[l2][c2] == '.')
                dfs(l2, c2, (dir + 1) % 4, cnt + 1);
        }
        else
            dfs(newL, newC, dir, cnt + 1);
    }
    mat[l][c] = '.';
}

int main() {
    freopen("snail.in", "r", stdin);
    freopen("snail.out", "w", stdout);

    int B;
    cin >> N >> B;
    for (int i = 0; i <= N + 1; ++ i)
        for (int j = 0; j <= N + 1; ++ j)
            mat[i][j] = '#';
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            mat[i][j] = '.';

    for (int i = 0; i < B; ++ i) {
        int l;
        char c;
        cin >> c >> l;
        mat[l][c - 'A' + 1] = '#';
    }

    dfs(1, 1, 0, 1);
    dfs(1, 1, 1, 1);
    cout << ans << '\n';
    return 0;
}
