#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

const double PI = acos(-1);
const double EPS = 1e-8;

string test() {
    int P, X, Y;
    cin >> P >> X >> Y;

    //Edge case for center
    if (X == 50 && Y == 50) {
        if (P > 0)
            return "black";
        else
            return "white";
    }

    int dst = (X - 50) * (X - 50) + (Y - 50) * (Y - 50);
    if (dst > 2500)
        return "white";

    double ang = atan2(Y - 50, X - 50) * 50 / PI;

    ang = 25 - ang;
    if (ang < 0)
        ang += 100;

    if (ang <= P + EPS)
        return "black";
    else
        return "white";
}

int main()
{
    //freopen("data.in", "r", stdin);
    //freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;

    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << test() << '\n';
    return 0;
}
