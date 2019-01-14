#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;
const lint INF = 1000000000;

inline bool frc_less_than(lint a, lint b, lint c, lint d) {
    while (1) {
        if (a / b != c / d)
            return a / b < c / d;
        else {
            const lint r1 = c % d;
            const lint r2 = a % b;
            if (r1 == 0) {
                return false;
            }
            else if (r2 == 0) {
                return true;
            }
            else {
                a = d;
                c = b;
                b = r1;
                d = r2;
            }
        }
    }
}

inline bool frc_less_than_equals(lint a, lint b, lint c, lint d) {
    while (1) {
        if (a / b != c / d)
            return a / b < c / d;
        else {
            const lint r1 = c % d;
            const lint r2 = a % b;
            if (r2 == 0) {
                return true;
            }
            else  if (r1 == 0) {
                return false;
            }
            else {
                a = d;
                c = b;
                b = r1;
                d = r2;
            }
        }
    }
}

void solve() {
    char ch;
    cin >> ch;
    assert(ch == '0');
    cin >> ch;
    assert(ch == '.');

    lint p1;
    p1 = 381679387165374971;
    cin >> p1;
    lint p2 = 1LL * INF * INF;

    lint a = 0, b = 1, c = 1, d = 1;
    auto move_left  = [&]() {
        if (a + c > INF || b + d > INF || !frc_less_than(p1, p2, a + c, b + d))
            return false;

        lint ans = 0;
        lint l = 1;
        lint r = (INF - d) / b;
        while (l <= r) {
            const lint k = (l + r) / 2;
            if (1LL * k * a + c > INF)
                r = k - 1;
            else if (frc_less_than(p1, p2, k * a + c, k * b + d)) {
                ans = k;
                l = k + 1;
            }
            else {
                r = k - 1;
            }
        }
        c = ans * a + c, d = ans * b + d;
        return ans > 0;
    };
    auto move_right = [&]() {
        if (a + c > INF || b + d > INF || !frc_less_than_equals(c + a, d + b, p1, p2))
            return false;

        lint ans = 0;
        lint l = 1;
        lint r = min((INF - a) / c, (INF - b) / d);
        while (l <= r) {
            const lint k = (l + r) / 2;
            /*if (1LL * k * c + a > INF ||
                1LL * k * d + b > INF)
                r = k - 1;
            else */if (frc_less_than_equals(k * c + a, k * d + b, p1, p2)) {
                ans = k;
                l = k + 1;
            }
            else {
                r = k - 1;
            }
        }
        a = ans * c + a, b = ans * d + b;
        return ans > 0;
    };


    while (move_left() || move_right());

    const long double q1 = 1.0L * p1 / p2 - 1.0L * a / b;
    const long double q2 = 1.0L * c / d - 1.0L * p1 / p2;

    if (q1 < q2)
        cout << a << ' ' << b << '\n';
    else
        cout << c << ' ' << d << '\n';
}

int main() {
    //freopen("data.in", "r", stdin);
    int Q = 10000;
    cin >> Q;
    while (Q--) {
        solve();
    }
    return 0;
}
