

#include <iostream>

using namespace std;

const int NMAX = 200 + 5;

int N, D;
int MOD;

int inv[NMAX];

int dp[NMAX][NMAX][NMAX]; //dp[nodes][h][cnt] = arbori cu radacina pentru care toti subarborii sunt mai mici ca (h, cnt)
int dp2[NMAX][3][NMAX]; //dp2[nodes][subarbori = 0 / 1 / 2][cnt] = arbori cu radacina cu nodes noduri si care au toti subarborii de inaltime fix D / 2, fiecare in parte de marime <= cnt

int exactly(int nodes, int h) {
    int ans;
    if (!h)
        ans = dp[nodes][min(h, nodes)][nodes];
    else {
        ans = dp[nodes][min(h, nodes)][nodes] + MOD - dp[nodes][min(h - 1, nodes)][nodes];
        if (ans >= MOD)
            ans -= MOD;
    }

    return ans;
}

int main()
{
    cin >> N >> D >> MOD;

    if (N == 1) {
        cout << "1\n";
        return 0;
    }
    if (D == 0) {
        cout << "0\n";
        return 0;
    }

    inv[1] = 1;
    for (int i = 2; i <= N; ++ i) {
        inv[i] = (1LL * MOD / i * inv[MOD % i]) % MOD;
        if (inv[i])
            inv[i] = MOD - inv[i];
    }

    for (int h = 0; h <= N; ++ h)
        for (int cnt = 0; cnt <= 1; ++ cnt)
            dp[1][h][cnt] = 1;

    for (int nodes = 2; nodes <= N; ++ nodes)
        for (int h = 1; h <= nodes && h <= (D / 2 + 1); ++ h) {
            dp[nodes][h][0] = dp[nodes][h - 1][nodes];

            for (int cnt = 1; cnt <= nodes; ++ cnt) {
                int comb = 1;

                for (int k = 0; cnt * k < nodes; ++ k) {
                    dp[nodes][h][cnt] = (dp[nodes][h][cnt] + 1LL * dp[nodes - cnt * k][min(h, nodes - cnt * k)][min(cnt - 1, nodes - cnt * k)] * comb) % MOD;

                    comb = (1LL * inv[k + 1] * comb) % MOD;
                    comb = (1LL * (exactly(cnt, h - 1) + k) * comb) % MOD;
                }
            }
        }

    int ans = 0;
    if (D & 1) {
        D /= 2;

        for (int i = 1; i < N; ++ i)
            ans = (ans + 1LL * exactly(i, D) * exactly(N - i, D)) % MOD;

        //Adaugam dublurile
        if (N % 2 == 0) {
            ans += exactly(N / 2, D);
            if (ans >= MOD)
                ans -= MOD;
        }

        ans = (1LL * ans * inv[2]) % MOD;
    }
    else {
        D /= 2;

        dp2[1][0][1] = 1;

        //Dinamica inainte
        for (int nodes = 1; nodes <= N; ++ nodes)
            for (int trees = 0; trees <= 2; ++ trees)
                for (int cnt = 1; cnt <= N; ++ cnt) {
                    int comb = 1;

                    for (int k = 0; nodes + k * cnt <= N; ++ k) {
                        dp2[nodes + k * cnt][min(2, trees + k)][cnt + 1] = (dp2[nodes + k * cnt][min(2, trees + k)][cnt + 1] + 1LL * dp2[nodes][trees][cnt] * comb) % MOD;

                        comb = (1LL * inv[k + 1] * comb) % MOD;
                        comb = ((1LL * exactly(cnt, D - 1) + k) * comb) % MOD;
                    }
                }

        //Variem numarul de subarbori de inaltime fix D / 2
        for (int cnt = 1; cnt < N; ++ cnt)
            ans = (ans + 1LL * dp2[cnt + 1][2][N + 1] * dp[N - cnt][min(N - cnt, D - 1)][N - cnt]) % MOD;
    }

    cout << ans << '\n';
    return 0;
}
