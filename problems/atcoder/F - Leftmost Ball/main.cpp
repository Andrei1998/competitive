#include <iostream>

using namespace std;

const int NMAX = 2000 + 5;
const int MOD = 1000000000 + 7;

int raise(int a, int b) {
    if (!b)
        return 1;
    else if (b & 1)
        return (1LL * a * raise(a, b - 1)) % MOD;
    else {
        int aux = raise(a, b >> 1);
        return (1LL * aux * aux) % MOD;
    }
}

int inv(int nr) {
    return raise(nr, MOD - 2);
}

int facts[NMAX * NMAX];
int invFacts[NMAX * NMAX];

void precalcFacts() {
    facts[0] = 1;
    for (int i = 1; i < NMAX * NMAX; ++ i)
        facts[i] = (1LL * i * facts[i - 1]) % MOD;

    invFacts[NMAX * NMAX - 1] = inv(facts[NMAX * NMAX - 1]);
    for (int i = NMAX * NMAX - 2; i >= 0; -- i)
        invFacts[i] = ((i + 1LL) * invFacts[i + 1]) % MOD;
}

inline int choose(int n, int k) {
    return ((1LL * facts[n] * invFacts[k]) % MOD * invFacts[n - k]) % MOD;
}

int dp[NMAX][NMAX];

int main()
{
    precalcFacts();

    int N, K;
    cin >> N >> K;

    K --;
    if (K == 0) {
        cout << "1\n";
        return 0;
    }

    dp[0][0] = 1;
    for (int i = 0; i <= N; ++ i)
        for (int j = i; j <= N; ++ j)
            if (i + j) {
                //We have i 0s left to place and j firsts to place
                if (i) //Place a 0
                    dp[i][j] = dp[i - 1][j];
                //Place a first
                dp[i][j] = (dp[i][j] + (1LL * dp[i][j - 1] * j) % MOD * choose(i + K * j - 1, K - 1)) % MOD;
            }

    cout << dp[N][N] << '\n';
    return 0;
}
