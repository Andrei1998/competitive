#include "mountains.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;
typedef complex <lint> Point;

//A views B over C
bool views(Point A, Point C, Point B) {
    return (conj(A - C) * (B - C)).imag() <= 0;
}

const int NMAX = 2000 + 5;

int N;
Point p[NMAX];

int dp[NMAX][NMAX];

int maximum_deevs(vector <int> _y) {
    N = _y.size();
    for (int i = 1; i <= N; ++ i)
        p[i] = {i, _y[i - 1]};

    for (int i = 1; i <= N; ++ i) {
        dp[i][i] = 1;

        int sum = 0;
        int last = i;
        for (int j = i - 1; j; -- j) {
            dp[i][j] = dp[i - 1][j];

            if (j == i - 1 || views(p[j], p[last], p[i])) {
                sum += dp[last - 1][j + 1];
                last = j;
            }

            dp[i][j] = max(dp[i][j], 1 + sum + dp[last - 1][j]);
        }
    }

	return dp[N][1];
}
