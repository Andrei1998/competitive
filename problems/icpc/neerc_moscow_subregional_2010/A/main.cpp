#include <bits/stdc++.h>

// 2:27
using namespace std;

typedef long long int lint;
const double PI = acos(-1);

int main() {
    int n, R;
    cin >> n >> R;
    vector <int> a(n);
    for (int i = 0; i < n; ++ i)
        cin >> a[i];
    sort(a.begin(), a.end());

    long double ans = PI * n * R * R;
    for (int i = 0; i + 1 < n; ++ i) {
        const int d = a[i + 1] - a[i];
        if (d < 2 * R) {
            const long double y = sqrtl(R * R - (d / 2.0) * (d / 2.0));
            ans += d * y;
            const long double angle = asinl(y / R);
            ans -= 2 * angle * R * R;
        }
    }
    cout << fixed << setprecision(12) << ans << endl;
    return 0;
}
