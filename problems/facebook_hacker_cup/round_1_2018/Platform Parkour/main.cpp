#include <bits/stdc++.h>

using namespace std;

int N, M, H1, H2, W, X, Y, Z;

int A[25], B[25];
int U[25], D[25];

const int NMAX = 200000 + 5;
int H[NMAX];

int maxUp[NMAX];
int maxDown[NMAX];

double solve() {
    H[1] = H1, H[2] = H2;
    for (int i = 3; i <= N; ++ i)
        H[i] = (1LL * W * H[i - 2] + 1LL * X * H[i - 1] + Y) % Z;

    for (int i = 1; i <= N; ++ i)
        maxUp[i] = maxDown[i] = 1E9;

    for (int i = 1; i <= M; ++ i) {
        if (A[i] < B[i]) {
            for (int j = A[i]; j < B[i]; ++ j) {
                maxUp[j] = min(maxUp[j], U[i]);
                maxDown[j] = min(maxDown[j], D[i]);
            }
        }
        else {
            for (int j = B[i]; j < A[i]; ++ j) {
                maxUp[j] = min(maxUp[j], D[i]);
                maxDown[j] = min(maxDown[j], U[i]);
            }
        }
    }

    double l = 0;
    double r = 1E9;
    for (int steps = 0; steps < 80; ++ steps) {
        double mid = (l + r) * 0.5;

        pair <double, double> p(H[1] - mid, H[1] + mid);
        bool ok = true;
        for (int i = 1; i < N && ok; ++ i) {
            p.first -= maxDown[i];
            p.second += maxUp[i];

            p.first = max(p.first, H[i + 1] - mid);
            p.second = min(p.second, H[i + 1] + mid);

            if (p.second < p.first)
                ok = false;
        }

        if (!ok)
            l = mid;
        else
            r = mid;
    }

    return l;
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    int T;
    cin >> T;
    for (int t = 1; t <= T; ++ t) {
        cin >> N >> M;
        cin >> H1 >> H2 >> W >> X >> Y >> Z;
        for (int i = 1; i <= M; ++ i)
            cin >> A[i] >> B[i] >> U[i] >> D[i];
        cout << "Case #" << t << ": " << fixed << setprecision(10) << solve() << endl;
    }
    return 0;
}
