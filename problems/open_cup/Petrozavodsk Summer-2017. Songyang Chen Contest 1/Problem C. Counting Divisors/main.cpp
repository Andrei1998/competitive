#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int VALMAX = 1000000 + 5;
const int MOD = 998244353;

vector <int> primes;
int low[VALMAX];
lint _nr[VALMAX];

void erat() {
    for (int i = 2; i <= VALMAX - 4; ++ i) {
        if (!low[i]) {
            low[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && 1LL * primes[j] * i <= VALMAX - 4 && primes[j] <= low[i]; ++ j)
            low[primes[j] * i] = primes[j];
    }
}

lint prod[VALMAX];

void test() {
    lint l, r, K;
    cin >> l >> r >> K;
    for (int i = 1; i <= r - l + 1; ++ i)
        prod[i] = 1, _nr[i] = l + i - 1;

    for (const auto pr: primes) {
        const lint k = (l + pr - 1) / pr;
        const lint start = k * pr;
        for (lint i = start; i <= r; i += pr) {
            lint nr = i;
            lint expo = 0;
            while (nr % pr == 0) {
                _nr[i - l + 1] /= pr;
                nr /= pr, ++ expo;
            }
            expo = (1LL * expo * K + 1) % MOD;
            prod[i - l + 1] = (1LL * prod[i - l + 1] * expo) % MOD;
        }
    }

    lint ans = 0;
    for (int i = 1; i <= r - l + 1; ++ i) {
        if (_nr[i] > 1)
            prod[i] = (1LL * prod[i] * (K + 1)) % MOD;
        ans += prod[i];
        if (ans >= MOD)
            ans -= MOD;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    erat();
    int T = 0;
    cin >> T;
    while (T --)
        test();
    return 0;
}
