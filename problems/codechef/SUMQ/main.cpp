#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
const int NMAX = 100000 + 5;

int A[NMAX];
int B[NMAX];
int C[NMAX];

void test() {
    int P, Q, R;
    cin >> P >> Q >> R;

    for (int i = 1; i <= P; ++ i)
        cin >> A[i];
    sort(A + 1, A + P + 1);
    for (int i = 1; i <= Q; ++ i)
        cin >> B[i];
    sort(B + 1, B + Q + 1);
    for (int i = 1; i <= R; ++ i)
        cin >> C[i];
    sort(C + 1, C + R + 1);

    int ans = 0;
    for (int i = 1, j = 0, k = 0, sumA = 0, sumC = 0; i <= Q; ++ i) {
        while (j + 1 <= P && A[j + 1] <= B[i]) {
            sumA += A[++ j];
            if (sumA >= MOD)
                sumA -= MOD;
        }
        while (k + 1 <= R && C[k + 1] <= B[i]) {
            sumC += C[++ k];
            if (sumC >= MOD)
                sumC -= MOD;
        }

        ans = (ans + (((1LL * B[i] * B[i]) % MOD * j) % MOD * k) % MOD + (1LL * sumA * sumC) % MOD + (B[i] * ((1LL * sumA * k + 1LL * sumC * j) % MOD)) % MOD) % MOD;
    }

    cout << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int T = 0;
    cin >> T;
    while (T --)
        test();
    return 0;
}
