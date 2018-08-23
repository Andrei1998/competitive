/*
ID: andreip3
LANG: C++14
TASK: fence9
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

struct Point {
    int x, y;
    Point(const int _x = 0, const int _y = 0):
        x(_x), y(_y) {}
};

lint ccw(const Point &A, const Point &B, const Point &C) {
    return 1LL * (A.x - B.x) * (C.y - B.y) - 1LL * (A.y - B.y) * (C.x - B.x);
}

int getCnt(const Point &A, const Point &B) {
    Point C(A.x - B.x, A.y - B.y);
    C.x = abs(C.x), C.y = abs(C.y);
    return __gcd(C.x, C.y);
}

int main() {
    freopen("fence9.in", "r", stdin);
    freopen("fence9.out", "w", stdout);

    int n, m, p;
    cin >> n >> m >> p;

    const Point A(0, 0);
    const Point B(n, m);
    const Point C(p, 0);

    lint area = ccw(A, B, C);
    lint ans = area + 2 - getCnt(A, B) - getCnt(A, C) - getCnt(B, C);
    ans /= 2;

    cout << ans << '\n';
    return 0;
}
