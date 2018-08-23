#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000 + 5;

int N, M;
int mat[NMAX][NMAX];

int stSus[NMAX][NMAX];
int stJos[NMAX][NMAX];
int drSus[NMAX][NMAX];
int drJos[NMAX][NMAX];

int main() {
    ios_base :: sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= M; ++ j)
            cin >> mat[i][j];

    vector <pair <int, int> > v;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= M; ++ j)
            v.push_back(make_pair(i, j));

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= M; ++ j) {
            stSus[i][j] = -mat[i][j] + i + j;
            if (i >= 2)
                stSus[i][j] = max(stSus[i][j], stSus[i - 1][j]);
            if (j >= 2)
                stSus[i][j] = max(stSus[i][j], stSus[i][j - 1]);
        }


    for (int i = 1; i <= N; ++ i)
        for (int j = M; j; -- j) {
            drSus[i][j] = -mat[i][j] + i - j;
            if (i >= 2)
                drSus[i][j] = max(drSus[i][j], drSus[i - 1][j]);
            if (j < M)
                drSus[i][j] = max(drSus[i][j], drSus[i][j + 1]);
        }


    for (int i = N; i; -- i)
        for (int j = M; j; -- j) {
            drJos[i][j] = -mat[i][j] - i - j;
            if (i < N)
                drJos[i][j] = max(drJos[i][j], drJos[i + 1][j]);
            if (j < M)
                drJos[i][j] = max(drJos[i][j], drJos[i][j + 1]);
        }


    for (int i = N; i; -- i)
        for (int j = 1; j <= M; ++ j) {
            stJos[i][j] = -mat[i][j] - i + j;
            if (i < N)
                stJos[i][j] = max(stJos[i][j], stJos[i + 1][j]);
            if (j >= 2)
                stJos[i][j] = max(stJos[i][j], stJos[i][j - 1]);
        }

    int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        for (int j = 1; j <= M; ++ j) {
            ans = max(ans, mat[i][j] - i - j + stSus[i][j]);
            ans = max(ans, mat[i][j] - i + j + drSus[i][j]);
            ans = max(ans, mat[i][j] + i + j + drJos[i][j]);
            ans = max(ans, mat[i][j] + i - j + stJos[i][j]);
        }
    }
    cout << ans - 1 << '\n';
    return 0;
}
