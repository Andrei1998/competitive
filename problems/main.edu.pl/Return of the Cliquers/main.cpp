#include <iostream>

using namespace std;

const int MODS[4] = {2, 13, 5281, 7283};

int raise(int a, int b, int MOD) {
    if (!b)
        return 1;
    else if (b & 1)
        return (1LL * a * raise(a, b - 1, MOD)) % MOD;
    else {
        int aux = raise(a, b >> 1, MOD);
        return (1LL * aux * aux) % MOD;
    }
}

int inv(int nr, int MOD) {
    return raise(nr, MOD - 2, MOD);
}

const int MOD = 1000000000 - 402;

int TCR(int a[4]) {
    int ans = 0;
    for (int i = 0; i < 4; ++ i) {
        int prod = MOD / MODS[i];
        ans = (ans + (1LL * prod * a[i]) % MOD * inv(prod, MODS[i])) % MOD;
    }

    return ans;
}

int facts[4][9000];
int invFacts[4][9000];

void precalcFacts() {
    for (int i = 0; i < 4; ++ i) {
        facts[i][0] = 1;
        for (int j = 1; j < MODS[i]; ++ j)
            facts[i][j] = (1LL * facts[i][j - 1] * j) % MODS[i];

        invFacts[i][MODS[i] - 1] = inv(facts[i][MODS[i] - 1], MODS[i]);
        for (int j = MODS[i] - 2; j >= 0; -- j)
            invFacts[i][j] = (1LL * invFacts[i][j + 1] * (j + 1)) % MODS[i];
    }
}

int comb(int n, int k, int index) {
    if (k > n)
        return 0;

    if (n < MODS[index])
        return ((1LL * facts[index][n] * invFacts[index][k]) % MODS[index] * invFacts[index][n - k]) % MODS[index];
    return (1LL * comb(n / MODS[index], k / MODS[index], index) * comb(n % MODS[index], k % MODS[index], index)) % MODS[index];
}

int comb(int n, int k) {
    int a[4];
    for (int i = 0; i < 4; ++ i)
        a[i] = comb(n, k, i);
    return TCR(a);
}

int computeBrute(int N, int k) {
    int ans = 1;
    while (N) {
        ans = (1LL * ans * comb(N - 1, k - 1)) % MOD;
        N -= k;
    }

    return ans;
}

int brute(int N, int M) {
    if (M == MOD + 1 || M == 2 * MOD + 2)
        return 0;

    int ans = 0;
    for (int i = 1; i <= N; ++ i)
        if (N % i == 0) {
            ans += computeBrute(N, i);
            if (ans >= MOD)
                ans -= MOD;
        }

    return raise(M, ans, MOD + 1);
}

int compute(int N, int k) {
    int ans[4] = {0};
    for (int mod = 0; mod < 4; ++ mod) {
        ;
    }

    return TCR(ans);
}

int solve(int N, int M) {
    if (M == MOD + 1 || M == 2 * MOD + 2)
        return 0;

    int ans = 0;
    for (int i = 1; i * i <= N; ++ i)
        if (N % i == 0) {
            ans += compute(N, i);
            if (ans >= MOD)
                ans -= MOD;
            if (i * i != N) {
                ans += compute(N, N / i);
                if (ans >= MOD)
                    ans -= MOD;
            }
        }

    return raise(M, ans, MOD + 1);
}

int main()
{
    precalcFacts();

    int N, M;
    //cin >> N >> M;

    N = 6;
    M = 2;

    cout << solve(N, M) << '\n';
    cout << brute(N, M) << '\n';

    return 0;
}
