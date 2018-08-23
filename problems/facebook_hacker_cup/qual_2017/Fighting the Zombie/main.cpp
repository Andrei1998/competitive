#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>

using namespace std;

double pb[21][21][20 * 20 + 1];

double getWinProb(const string &event, int hp) {
    stringstream ss(event);

    int x;
    ss >> x;

    char ch;
    ss >> ch;

    int y;
    ss >> y;

    char sign;
    ss >> sign;

    int z = 0;
    if (!ss.eof()) {
        ss >> z;
        if (sign == '+')
            z *= (-1);
    }

    double ans = 0;
    for (int val = max(0, hp + z); val <= y * x; ++ val)
        ans += pb[y][x][val];
    return ans;
}

double test() {
    int hp, n;
    cin >> hp >> n;

    double best = 0;
    for (int i = 1; i <= n; ++ i) {
        string event;
        cin >> event;

        double win = getWinProb(event, hp);
        if (win > best)
            best = win;
    }

    return best;
}

int main()
{
    for (auto sides: {4, 6, 8, 10, 12, 20}) {
        pb[sides][0][0] = 1;
        for (int rolls = 1; rolls <= 20; ++ rolls)
            for (int sum = rolls; sum <= sides * rolls; ++ sum) {
                for (int roll = 1; roll <= sides && roll <= sum; ++ roll)
                    pb[sides][rolls][sum] += pb[sides][rolls - 1][sum - roll] / sides;
                pb[sides][rolls][sum] /= sides;
            }
    }

    //freopen("data.in", "r", stdin);
    //freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;

    for (int i = 1; i <= T; ++ i)
        cout << fixed << setprecision(10) << "Case #" << i << ": " << test() << '\n';
    return 0;
}
