#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2000 + 5;

pair <double, int> dp[NMAX][NMAX]; //dp[where][b]

int N, A, B;
double a[NMAX];
double b[NMAX];

pair <double, int> solve(double lambda) {
    for (int i = 0; i <= N; ++ i)
        for (int j = 0; j <= i + 1 && j <= B + 1; ++ j)
            dp[i][j] = {-1E9 - 215, -NMAX};

    dp[0][0] = {0, 0};
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j <= i && j <= B; ++ j) {
            //Place single b
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], {dp[i][j].first + b[j + 1], dp[i][j].second});

            //Place single a
            dp[i + 1][j] = max(dp[i + 1][j], {dp[i][j].first + a[i + 1] - lambda, dp[i][j].second + 1});

            //Place both
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], {dp[i][j].first + a[i + 1] + b[i + 1] - a[i + 1] * b[i + 1] - lambda, dp[i][j].second + 1});

            //Don't do anything
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
        }

    pair <double, int> best = {-1E9 - 215, -1};
    for (int i = 0; i <= B; ++ i)
        best = max(best, dp[N][i]);
    return best;
}

int main()
{
    cin >> N >> A >> B;
    for (int i = 1; i <= N; ++ i)
        cin >> a[i];
    for (int i = 1; i <= N; ++ i)
        cin >> b[i];

    for (double l = 0.98; l <= 1.05; l += 0.001)
        cout << l << ' ' << solve(l).second << endl;


    double st = 0;
    double dr = 2 * N;

    for (int steps = 0; steps < 40; ++ steps) {
        double mid = (st + dr) * 0.5;
        auto ans = solve(mid);

        cout << "eu am " << st << ' ' << dr << ' ' << mid << endl;
        cout << ans.first << ' ' << ans.second << endl;

        if (ans.second < A)
            dr = mid;
        else
            st = mid;
    }

    auto ans = solve(st - 1E-4);
    cout << fixed << setprecision(6) << ans.first + ans.second * st << '\n';
    return 0;
}
