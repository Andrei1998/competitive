#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500 + 5;

int N, M;
int mat[NMAX][NMAX];
bool marked[NMAX][NMAX];

int largest;
void dfs(int l, int c, const int vl) {
    if (l <= 0 || c <= 0 || l > N || c > M) return;
    largest = max(largest, mat[l][c]);
    if (marked[l][c]) return;
    if (mat[l][c] != vl) return;
    marked[l][c] = true;
    dfs(l - 1, c, vl);
    dfs(l + 1, c, vl);
    dfs(l, c - 1, vl);
    dfs(l, c + 1, vl);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    memset(mat, -1, sizeof mat);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> mat[i][j];
        }
    }

    int cnt = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (!marked[i][j] && mat[i][j] > 1) {
                largest = -1;
                dfs(i, j, mat[i][j]);
                if (largest <= mat[i][j]) {
                    ++cnt;
                }
            }
        }
    }
    cout << cnt << endl;
    return 0;
}