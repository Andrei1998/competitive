#include <iostream>
#include <string>

#define lint long long int
using namespace std;

const int NMAX = 12;

int N, M;
string mat[NMAX];

lint dp[NMAX][NMAX + 1][1 << NMAX][2];

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; ++ i)
        cin >> mat[i];

    dp[0][0][0][0] = 1;
    for (int lin = 0; lin < N; ++ lin) {
        for (int col = 0; col < M; ++ col) {
            for (int mask = 0; mask < (1 << M); ++ mask) {
                if (dp[lin][col][mask][0]) {
                    if (mat[lin][col] == '*') {
                        if (!(mask & (1 << col)))
                            dp[lin][col + 1][mask][0] += dp[lin][col][mask][0];
                    }
                    else {
                        if (!(mask & (1 << col)))
                            dp[lin][col + 1][mask | (1 << col)][1] += dp[lin][col][mask][0];
                        else {
                            dp[lin][col + 1][mask ^ (1 << col)][1] += dp[lin][col][mask][0];
                            dp[lin][col + 1][mask][0] += dp[lin][col][mask][0];
                        }
                    }
                }

                if (dp[lin][col][mask][1] ){
                    if (mat[lin][col] != '*')
                        if (!(mask & (1 << col))) {
                            //2 Update-uri
                            dp[lin][col + 1][mask | (1 << col)][0] += dp[lin][col][mask][1];
                            dp[lin][col + 1][mask][1] += dp[lin][col][mask][1];
                        }
                        else
                            dp[lin][col + 1][mask ^ (1 << col)][0] += dp[lin][col][mask][1];
                    }
                }
            }

        if (lin == N - 1) {
            //Print
            cout << dp[N - 1][M][0][0] << '\n';
            return 0;
        }
        else {
            for (int mask = 0; mask < (1 << M); ++ mask)
                dp[lin + 1][0][mask][0] = dp[lin][M][mask][1];
        }
    }

    return 0;
}
