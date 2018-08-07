#include <iostream>
#include <iomanip>
#include <cmath>

#define double long double
using namespace std;

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0):
        x(_x), y(_y) {}

    friend double dist(const Point &a, const Point &b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    friend istream& operator>>(istream &f, Point &p) {
        f >> p.x >> p.y;
        return f;
    }

    friend ostream& operator<<(ostream &g, Point &p) {
        g << fixed << setprecision(10) << p.x << ' ' << p.y;
        return g;
    }
} A, B, C;

double cost(const Point &P) {
    return dist(P, A) + dist(P, B) + dist(P, C);
}

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int main()
{
    cin >> A >> B >> C;


    double step = 2000;

    Point P(0, 0);
    double cst = cost(P);
    for (int i = 0; i < 1000; ++ i, step *= 0.5) {
        while (1) {
            int i;
            for (i = 0; i < 4; ++ i) {
                Point newP(P.x + dx[i] * step, P.y + dy[i] * step);
                if (cost(newP) < cst) {
                    P = newP;
                    cst = cost(P);
                    break;
                }
            }

            if (i == 4)
                break;
        }
    }

    cout << P << '\n';
    return 0;
}
