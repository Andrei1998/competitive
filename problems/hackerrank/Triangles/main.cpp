#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>

//17:28
using namespace std;

const int NMAX = 3000 + 5;

int N;
struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0):
        x(_x), y(_y) {}
} points[NMAX];

int ccw(const Point &A, const Point &rf, const Point &B) {
    return (A.x - rf.x) * (B.y - rf.y) - (A.y - rf.y) * (B.x - rf.x);
}

int dist(const Point &A, const Point &B) {
    return abs(A.x - B.x) + abs(A.y - B.y);
}

Point rf;
bool operator<(const Point &A, const Point &B) {
    int aux = ccw(A, rf, B);
    if (aux != 0)
        return aux > 0;
    else
        return dist(rf, A) > dist(rf, B);
}

typedef long long int lint;

Point leftPoints[NMAX];
int leftSz;
Point rightPoints[NMAX];
int rightSz;

lint ans;
void solve() {
    leftSz = rightSz = 0;
    for (int i = 1; i <= N; ++ i)
        if (points[i].x > rf.x)
            rightPoints[++ rightSz] = points[i];
        else if (points[i].x < rf.x)
            leftPoints[++ leftSz] = points[i];
        else if (points[i].y > rf.y)
            rightPoints[++ rightSz] = points[i];
        else if (points[i].y < rf.y)
            leftPoints[++ leftSz] = points[i];


    sort(leftPoints + 1, leftPoints + leftSz + 1);
    sort(rightPoints + 1, rightPoints + rightSz + 1);

    int j = 0;
    int above = rightSz - 1, under = leftSz;
    for (int i = 1; i <= rightSz; ++ i) {
        while (j + 1 <= leftSz && ccw(leftPoints[j + 1], rf, rightPoints[i]) < 0) {
            ++ j;
            ++ above;
            -- under;
        }

        ans += 1LL * (rf.y + rightPoints[i].y) * (rightPoints[i].x - rf.x) * (under - above);

        -- above;
        ++ under;
    }
}

/*lint ans2;
void solveBrute() {
    for (int i = 1; i <= N; ++ i)
        for (int j = i + 1; j <= N; ++ j)
            for (int k = j + 1; k <= N; ++ k)
                ans2 += llabs(ccw(points[i], points[j], points[k]));
}*/

int main()
{
    //freopen("data.in", "r", stdin);
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> points[i].x >> points[i].y;

    for (int i = 1; i <= N; ++ i) {
        rf = points[i];
        solve();
    }

    //solveBrute();
    //cout << ans << ' ' << ans2 << endl;

    if (ans % 2 == 0)
        cout << ans / 2 << ".0\n";
    else
        cout << ans / 2 << ".5\n";
    return 0;
}
