#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

const int NMAX = 50 + 5;

int N, M;
string mat[NMAX];

const int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[8] = {1, -1, 1, 0, -1, 1, 0, -1};

int dp[NMAX][NMAX];
bool vis[NMAX][NMAX];

void memo(int lin, int col) {
    if (vis[lin][col])
        return ;
    vis[lin][col] = true;

    dp[lin][col] = 1;
    for (int i = 0; i < 8; ++ i) {
        int nlin = lin + dx[i];
        int ncol = col + dy[i];

        if (nlin >= 1 && ncol >= 1 && nlin <= N && ncol <= M && mat[lin][col] + 1 == mat[nlin][ncol]) {
            memo(nlin, ncol);
            dp[lin][col] = max(dp[lin][col], 1 + dp[nlin][ncol]);
        }
    }
}

bool test(int t) {
    cin >> N >> M;
    if (!N)
        return false;

    for (int i = 1; i <= N; ++ i) {
        cin >> mat[i];
        mat[i] = " " + mat[i];
    }

    memset(vis, 0, sizeof vis);

    int ans = 0;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= M; ++ j)
            if (mat[i][j] == 'A') {
                memo(i, j);
                if (dp[i][j] > ans)
                    ans = dp[i][j];
            }

    cout << "Case " << t << ": " << ans << '\n';
    return true;
}

int main()
{
    int t = 0;
    while (test(++ t));
    return 0;
}
