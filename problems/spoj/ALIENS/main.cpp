#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

const int NMAX = 100000 + 5;

int N;
struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0):
        x(_x), y(_y) {}
    double dist(const Point &arg) const {
        return sqrt((x - arg.x) * (x - arg.x) + (y - arg.y) * (y - arg.y));
    }
    double quad(const Point &arg) const {
        return (x - arg.x) * (x - arg.x) + (y - arg.y) * (y - arg.y);
    }
} points[NMAX];

pair <Point, double> getCenter(const vector <Point> &v) {
    if (v.empty())
        return make_pair(Point(-NMAX, -NMAX), 0);
    else if (v.size() == 1)
        return make_pair(v[0], 0);
    else if (v.size() == 2)
        return make_pair(Point((v[0].x + v[1].x) * 0.5, (v[0].y + v[1].y) * 0.5), v[0].dist(v[1]) / 2);
    else {
        double a = v[0].quad(v[1]);
        double b = v[1].quad(v[2]);
        double c = v[2].quad(v[0]);

        double C0 = b * (a + c - b);
        double C1 = c * (a + b - c);
        double C2 = a * (b + c - a);
        double norm = C0 + C1 + C2;

        C0 /= norm;
        C1 /= norm;
        C2 /= norm;

        Point P(v[0].x * C0 + v[1].x * C1 + v[2].x * C2,
                v[0].y * C0 + v[1].y * C1 + v[2].y * C2);

        return make_pair(P, P.dist(v[0]));
    }
}

const double EPS = 1E-8;

bool inside(const pair <Point, double> &circle, const Point &P) {
    return circle.first.quad(P) <= circle.second * circle.second + EPS;
}

pair <Point, double> MEC(int lim, vector <Point> &fixed) {
    assert(fixed.size() < 4);

    auto mec = getCenter(fixed);
    for (int i = 1; i <= lim; ++ i) {
        if (!inside(mec, points[i])) {
            fixed.push_back(points[i]);
            mec = MEC(i - 1, fixed);
            fixed.pop_back();
        }
    }

    return mec;
}

void test() {
    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        double x, y;
        cin >> x >> y;
        points[i] = Point(x, y);
    }
    random_shuffle(points + 1, points + N + 1);

    vector <Point> f;
    auto mec = MEC(N, f);

    cout << fixed << setprecision(2) << mec.second << '\n';
    cout << mec.first.x << ' ' << mec.first.y << '\n';
}

int main()
{
    auto now = system_clock :: now();
    auto d = now.time_since_epoch();
    srand(duration_cast <milliseconds>(d).count());

    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int T = 0;
    cin >> T;
    while (T --)
        test();
    return 0;
}
