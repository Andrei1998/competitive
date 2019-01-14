#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    if (N == 1) {
        cout << "0\n";
        return 0;
    }

    long long int xr = 0;
    for (int i = 1; i <= N; ++i) {
        long long int vl;
        cin >> vl;
        xr ^= vl;
    }

    if (xr != 0) {
        cout << "0\n";
        return 0;
    }

    long long int ans = (1LL << N) - 2;
    cout << ans << endl;
    return 0;
}
