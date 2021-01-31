#include <bits/stdc++.h>

using namespace std;

#define int long long int

signed main() {
    int c, e, m;
    cin >> c >> e >> m;

    int area = m + c + e;
    int sum = (e + 8) / 2;

    if (c != 4 || e % 2 == 1) {
        cout << "impossible" << endl;
        return 0;
    }

    for (int h = 2; h <= area && h <= sum && h <= area / h; ++h) {
        if (area % h == 0) {
            const int w = area / h;
            if (w <= 1) {
                break;
            }
            if (h * w == area && h + w == sum) {
                cout << w << ' ' << h << endl;
                return 0;
            }
        }
    }

    cout << "impossible" << endl;
    return 0;
}