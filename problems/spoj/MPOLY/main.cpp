#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int NMAX = 100 + 5;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}

    friend bool operator<(const Point &a, const Point &b) {
        if (a.x * b.y - a.y * b.x != 0)
            return a.x * b.y - a.y * b.x > 0;
        else
            return a.x < b.x;
    }
} points[NMAX];

int collin(const Point &A, const Point &B, const Point &C) {
    return (A.x - B.x) * (C.y - B.y) - (A.y - B.y) * (C.x - B.x);
}

int dp[NMAX][NMAX];

int main()
{
    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        int x, y;
        cin >> x >> y;
        points[i] = Point(x, y);
    }

    sort(points + 1, points + N + 1);

    for (int i = 0; i <= N; ++ i)
        for (int j = 0; j <= N; ++ j)
            dp[i][j] = -1;

    for (int i = 1; i <= N; ++ i)
        dp[0][i] = 2;

    int ans = 3;
    for (int i = 0; i <= N; ++ i)
        for (int j = i + 1; j <= N; ++ j)
            if (dp[i][j] != -1)
                for (int k = j + 1; k <= N; ++ k)
                    if (collin(points[i], points[j], points[k]) < 0) {
                        dp[j][k] = max(dp[j][k], 1 + dp[i][j]);
                        if (dp[j][k] > ans)
                            ans = dp[j][k];
                    }

    cout << ans << '\n';
    return 0;
}
