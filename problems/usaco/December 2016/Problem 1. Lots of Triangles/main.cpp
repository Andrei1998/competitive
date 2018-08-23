#include <iostream>
#include <cstdio>
#include <algorithm>

#define lint long long int
using namespace std;

const int NMAX = 300 + 5;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}
} points[NMAX];

lint ccw(const Point &a, const Point &refer, const Point &b) {
    return 1LL * (a.x - refer.x) * (b.y - refer.y) - 1LL * (a.y - refer.y) * (b.x - refer.x);
}

Point refer;
bool operator<(const Point &a, const Point &b) {
    return ccw(a, refer, b) > 0;
}

bool cmp(const Point &a, const Point &b) {
    if (a.x != b.x)
        return a.x < b.x;
    else
        return a.y < b.y;
}

bool inside(const Point &a, const Point &b, const Point &c, const Point &p) {
    int minX = min(a.x, min(b.x, c.x));
    int minY = min(a.y, min(b.y, c.y));
    int maxX = max(a.x, max(b.x, c.x));
    int maxY = max(a.y, max(b.y, c.y));

    if (p.x < minX || p.x > maxX)
        return false;
    if (p.y < minY || p.y > maxY)
        return false;

    return llabs(ccw(a, p, b)) + llabs(ccw(b, p, c)) + llabs(ccw(c, p, a)) == llabs(ccw(a, b, c));
}

int dp[NMAX][NMAX];
int ans[NMAX];

int main()
{
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    int N;
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        int x, y;
        cin >> x >> y;
        points[i] = Point(x, y);
    }

    int best = 1;
    for (int i = 2; i <= N; ++ i)
        if (cmp(points[i], points[best]))
            best = i;

    swap(points[1], points[best]);
    refer = points[1];
    sort(points + 2, points + N + 1);

    //Precompute
    for (int i = 2; i <= N; ++ i)
        for (int j = i + 1; j <= N; ++ j) {
            for (int k = 2; k <= N; ++ k)
                if (k != i && k != j)
                    dp[i][j] += inside(points[1], points[i], points[j], points[k]);

            //Origin triangles
            ++ ans[dp[i][j]];
        }

    //Other triangles
    for (int i = 2; i <= N; ++ i)
        for (int j = i + 1; j <= N; ++ j)
            for (int k = j + 1; k <= N; ++ k) {
                int cnt = dp[i][j] + dp[j][k] - dp[i][k];
                if (cnt < 0)
                    cnt = -cnt - 1;
                ++ ans[cnt];
            }

    for (int i = 0; i <= N - 3; ++ i)
        cout << ans[i] << '\n';
    return 0;
}
