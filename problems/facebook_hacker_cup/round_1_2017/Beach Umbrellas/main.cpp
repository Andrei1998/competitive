#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1000000000 + 7;
const int NMAX = 2000 + 5;

int N, M;
int r[NMAX];

int prod[3][2 * NMAX]; //prod[i][j] = Permutations product if we miss out i terms, highest term being M + j
int ways[2 * NMAX]; //ways[i] = number of ways to place endings (or not place them) such that exactly i umbrella segments lie outside

int aux[2 * NMAX];
int conv[NMAX][2 * NMAX];

int waysBrute[2 * NMAX];

int test() {
    cin >> N >> M;

    if (N == 1) {
        cin >> r[1];
        return M;
    }

    M --;

    memset(r, 0, sizeof(r));
    for (int i = 1; i <= N; ++ i) {
        cin >> r[i];
        M -= 2 * r[i];
    }

    memset(aux, 0, sizeof(aux));
    memset(ways, 0, sizeof(ways));
    //memset(waysBrute, 0, sizeof(waysBrute));

    //Ways by brute
    /*for (int i = 1; i <= N; ++ i) {
        for (int j = 1; j <= N; ++ j)
            if (i != j)
                for (int k = 1; k <= r[i]; ++ k)
                    for (int l = 1; l <= r[j]; ++ l)
                        ++ waysBrute[k + l];

        for (int k = 1; k <= r[i]; ++ k)
            waysBrute[k] += 2;
    }*/

    for (int i = 1; i <= N; ++ i) {
        ++ aux[1];
        -- aux[r[i] + 1];
    }

    for (int i = 1; i <= 4000; ++ i)
        aux[i] += aux[i - 1];

    //Ways to pair two elements
    for (int i = 1; i <= 2000; ++ i)
        for (int j = 1; j <= 2000; ++ j) {
            ways[i + j] += aux[i] * aux[j];
            if (ways[i + j] >= MOD)
                ways[i + j] -= MOD;
        }

    //Subtract ways to pair an element with itself
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= 4000; ++ j) {
            ways[j] -= conv[r[i]][j];
            if (ways[j] < 0)
                ways[j] += MOD;
        }

    //Compute ways to only use one end
    for (int i = 1; i <= 4000; ++ i)
        aux[i] *= 2;

    /*for (int i = 0; i <= 4000; ++ i)
        if (ways[i] != waysBrute[i])
            cout << "Ohh... i = " << i << endl;*/

    //Doing nothing is, indeed, allowed
    ++ ways[0];

    memset(prod, 0, sizeof(prod));
    for (int missing = 0; missing <= 2; ++ missing)
        for (int gain = 0; gain <= 4000; ++ gain) {
            int start = M + gain + 1;
            if (start <= 0)
                prod[missing][gain] = 0;
            else {
                if (N - missing < 0)
                    prod[missing][gain] = 0;
                else
                    prod[missing][gain] = 1;

                for (int i = 1; i <= N - missing; ++ i) {
                    prod[missing][gain] = (1LL * prod[missing][gain] * start) % MOD;
                    ++ start;
                }
            }
        }

    int ans = prod[0][0]; //No filled end
    for (int i = 1; i <= 4000; ++ i) //One filled end
        ans = (ans + 1LL * aux[i] * prod[1][i]) % MOD;
    for (int i = 1; i <= 4000; ++ i) //Both ends filled
        ans = (ans + 1LL * ways[i] * prod[2][i]) % MOD;
    return ans;
}

int main()
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);

    conv[1][2] = 1;
    for (int r = 2; r <= 2000; ++ r) {
        for (int i = 0; i <= 4000; ++ i)
            conv[r][i] = conv[r - 1][i];

        for (int i = 1; i <= r; ++ i)
            conv[r][i + r] += 2;
        -- conv[r][r + r];

        for (int i = 0; i <= 4000; ++ i)
            conv[r][i] %= MOD;
    }

    int T = 0;
    cin >> T;

    for (int t = 1; t <= T; ++ t)
        cout << "Case #" << t << ": " << test() << '\n';
    return 0;
}
