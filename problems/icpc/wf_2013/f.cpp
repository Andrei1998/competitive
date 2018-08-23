#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000000 + 5;

int N, K;
int v[NMAX];

bool works(int b) {
    int c = 0;
    bool canDo = true;
    for (int i = 2 * N * K; i; -- i) {
        ++ c;
        if (!canDo) {
            canDo = true;
            continue;
        }
        if (c >= 2 * K) {
            if (v[i + 1] - v[i] <= b) {
                c -= 2 * K;
                canDo = false;
            }
        }
    }
    return c == 0;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin >> N >> K;
    for (int i = 1; i <= 2 * N * K; ++ i) cin >> v[i];
    sort(v + 1, v + 2 * N * K + 1);

    int l = 0, r = 1000000000;
    int ans = r + 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (works(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }

    cout << ans << '\n';
    return 0;
}
