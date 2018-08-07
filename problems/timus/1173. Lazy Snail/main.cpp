#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int NMAX = 1000 + 5;
const double PI = acos(-1);
const double EPS = 1e-10;

double X, Y;
int N;

struct Point {
    double X, Y;
    double ang;
    int id;

    friend bool operator<(const Point &A, const Point &B) {
        return A.ang < B.ang;
    }
} points[NMAX];

int main()
{
    cin >> X >> Y >> N;
    for (int i = 1; i <= N; ++ i) {
        cin >> points[i].X >> points[i].Y >> points[i].id;
        points[i].ang = atan2(points[i].Y - Y, points[i].X - X);
    }

    sort(points + 1, points + N + 1);

    for (int i = 2; i <= N; ++ i)
        if (points[i].ang - points[i - 1].ang >= PI - EPS) {
            reverse(points + 1, points + i);
            reverse(points + i, points + N + 1);
            break;
        }

    cout << "0\n";
    for (int i = 1; i <= N; ++ i)
        cout << points[i].id << '\n';
    cout << "0\n";
    return 0;
}
