#include <bits/stdc++.h>

using namespace std;

const int INF = 1e8;

int test() {
    int N, M, K;
    cin >> N >> M >> K;

    if (M < N)
        swap(N, M);
    if (K >= N)
        return -1;

    if (K == 1) {
        if (N == 1)
            return -1;
        else if (N == 2) {
            if (M <= 4)
                return -1;
            else
                return 2;
        }
    }

    if (M < 2 * K + 3)
        return -1;

    int ans = INF;
    if (N >= 2 * K + 1)
        ans = 4 + (K == 1);

    int _N = N % K;
    int curr = N / K;
    while (_N > 0) {
        _N -= K;
        ++ curr;
    }

    ans = min(ans, curr);
    if (ans == INF)
        return -1;
    else
        return ans;
}

int main()
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    int T = 0;
    cin >> T;

    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << test() << '\n';
    return 0;
}
