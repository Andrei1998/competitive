#include <iostream>

using namespace std;

const int INF = 1E9 + 15;
const int NMAX = 300 + 5;

int mat[NMAX][NMAX];
int dist[NMAX][NMAX];
int ans[NMAX];

int main()
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        ans[i] = INF;

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j) {
            cin >> mat[i][j];
            if (mat[i][j] == -1)
                mat[i][j] = INF;
            dist[i][j] = mat[i][j];
        }

    for (int k = 1; k <= N; ++ k)
        for (int i = 1; i <= N; ++ i)
            for (int j = 1; j <= N; ++ j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            cout << dist[i][j] << " \n"[j == N];

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= N; ++ j)
            if (i != j && dist[i][j] != mat[i][j])
                ans[i] = min(ans[i], dist[i][j] + mat[i][j]);

    for (int i = 1; i <= N; ++ i)
        if (ans[i] == INF)
            cout << "-1\n";
        else
            cout << ans[i] << '\n';
    return 0;
}
