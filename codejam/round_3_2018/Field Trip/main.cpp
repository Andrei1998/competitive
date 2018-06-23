#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int NMAX = 10000 + 5;
const lint INF = 1E11;

int N;
int x[NMAX], y[NMAX];

lint solve() {
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> x[i] >> y[i];

    lint st = 0, dr = INF, ans = dr + 1;
    while (st <= dr) {
        lint mid = (st + dr) / 2;
        lint xMin = INF;
        lint xMax = -INF;
        lint yMin = INF;
        lint yMax = -INF;

        for (int i = 1; i <= N; ++ i) {
            xMin = min(xMin, x[i] + mid);
            yMin = min(yMin, y[i] + mid);
            xMax = max(xMax, x[i] - mid);
            yMax = max(yMax, y[i] - mid);
        }

        if (xMax <= xMin && yMax <= yMin) {
            ans = mid;
            dr = mid - 1;
        }
        else
            st = mid + 1;
    }
    return ans;
}

int main() {
    //freopen("data.in", "r", stdin);
    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << solve() << '\n';
    return 0;
}
