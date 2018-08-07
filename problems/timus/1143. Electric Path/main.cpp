#include <iostream>
#include <iomanip>
#include <complex>

using namespace std;

typedef complex <double> Point;

const int NMAX = 200 + 5;
const double INF = 1e18;

int N;
Point p[NMAX];

inline void upd(double &dp, double val) {
    if (val < dp)
        dp = val;
}

double dp[NMAX][NMAX][2];

int nxt[NMAX];
int prv[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N;
    for (int i = 0; i < N; ++ i) {
        double x, y;
        cin >> x >> y;
        p[i] = Point(x, y);
    }

    for (int i = 0; i < N; ++ i) {
        nxt[i] = (i + 1) % N;
        prv[i] = (i + N - 1) % N;
    }

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            dp[i][j][0] = dp[i][j][1] = INF;

    for (int i = 0; i < N; ++ i)
        dp[i][i][0] = dp[i][i][1] = 0;

    for (int l = 0; l < N; ++ l)
        for (int i = 0; i < N; ++ i) {
            int j = (i + l) % N;

            upd(dp[prv[i]][j][0], dp[i][j][0] + abs(p[i] - p[prv[i]]));
            upd(dp[i][nxt[j]][1], dp[i][j][0] + abs(p[i] - p[nxt[j]]));

            upd(dp[prv[i]][j][0], dp[i][j][1] + abs(p[j] - p[prv[i]]));
            upd(dp[i][nxt[j]][1], dp[i][j][1] + abs(p[j] - p[nxt[j]]));
        }

    double ans = dp[0][N - 1][0];
    for (int i = 0; i < N; ++ i) {
        upd(ans, dp[i][prv[i]][0]);
        upd(ans, dp[i][prv[i]][1]);
    }

    cout << fixed << setprecision(3) << ans << '\n';
    return 0;
}
