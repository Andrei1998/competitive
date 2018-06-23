#include <bits/stdc++.h>

using namespace std;

const int MOD = 924844033; // The modulus given in the statement
const int primes[] = {2, 3, 7}; // Prime factors of MOD - 1
const int G = 5; // Found by running findGenerator
const int BITSMAX = 16;
const int NMAX    = (1 << BITSMAX);

int raise(int a, int b) {
    int ans = 1, aux = a;
    while (b) {
        if (b & 1)
            ans = (1LL * ans * aux) % MOD;
        aux = (1LL * aux * aux) % MOD;
        b >>= 1;
    }
    return ans;
}
inline int getInv(int x) {
    return raise(x, MOD - 2);
}

/*bool isGenerator(int nr) {
    for (auto it: primes)
        if (raise(nr, (MOD - 1) / it) == 1)
            return false;
    return true;
}
int findGenerator() {
    int g = 2;
    while (!isGenerator(g))
        ++ g;
    return g;
}
int w[2][2 * NMAX];
void precomputeRoots() {
    w[0][1] = w[1][1] = 1;
    for (int k = 1; k <= BITSMAX; ++ k) {
        int W0 = raise(G, ((MOD - 1) / (1 << k)));
        int W1 = getInv(W0);
        const int bound = (1 << k);
        for (int i = (1 << (k - 1)); i < bound; ++ i) {
            w[0][2 * i] = w[0][i], w[0][2 * i + 1] = (1LL * w[0][i] * W0) % MOD;
            w[1][2 * i] = w[1][i], w[1][2 * i + 1] = (1ll * w[1][i] * W1) % MOD;
        }
    }
}*/

int rev[NMAX];
void ntt(int v[], const int BITS, const bool inv = false) {
    //static bool computed = false;
    //if (!computed)
    //    precomputeRoots(), computed = true;
    const int N = (1 << BITS);
    for (int i = 1; i < N; ++ i) {
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1)
            rev[i] += N / 2;
    }
    for (int i = 0; i < N; ++ i)
        if (i < rev[i])
            swap(v[i], v[rev[i]]);
    for (int len = 1; len < N; len <<= 1) {
        int w = raise(G, ((MOD - 1) / (2 * len)));
        if (inv)
            w = getInv(w);
        for (int start = 0; start < N; start += 2 * len) {
            int wk = 1;
            for (int i = 0; i < len; ++ i) {
                //const int b = (1LL * v[start + i + len] * w[inv][2 * len + i]) % MOD;
                const int b = (1LL * v[start + i + len] * wk) % MOD;
                v[start + i + len] = v[start + i] - b;
                if (v[start + i + len] < 0)
                    v[start + i + len] += MOD;
                v[start + i] = v[start + i] + b;
                if (v[start + i] >= MOD)
                    v[start + i] -= MOD;
                wk = (1LL * wk * w) % MOD;
            }
        }
    }
    if (inv) {
        int aux = getInv(N);
        for (int i = 0; i < N; ++ i)
            v[i] = (1LL * v[i] * aux) % MOD;
    }
}

int pointsA[NMAX];
int pointsB[NMAX];
int pointsRes[NMAX];
template <typename RandomIt>
void convolute(RandomIt a, int Na, RandomIt b, int Nb, RandomIt res) {
    /*if (Na * Nb <= 16 * 16) {
        for (int i = 0; i < Na + Nb; ++ i)
            res[i] = 0;
        for (int i = 0; i < Na; ++ i)
            for (int j = 0; j < Nb; ++ j)
                res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % MOD;
        return ;
    }*/

    int BITS = 0;
    while ((1 << BITS) < Na + Nb - 1) ++ BITS;
    const int N = (1 << BITS);

    for (int i = 0; i < Na; ++ i)
        pointsA[i] = a[i];
    for (int i = Na; i < N; ++ i)
        pointsA[i] = 0;
    for (int i = 0; i < Nb; ++ i)
        pointsB[i] = b[i];
    for (int i = Nb; i < N; ++ i)
        pointsB[i] = 0;

    ntt(pointsA, BITS);
    ntt(pointsB, BITS);

    for (int i = 0; i < N; ++ i)
        pointsRes[i] = (1LL * pointsA[i] * pointsB[i]) % MOD;

    ntt(pointsRes, BITS, true);

    for (int i = 0; i < N; ++ i)
        res[i] = pointsRes[i];
}

const int VALMAX = 30000 + 5;
int freqA[VALMAX];
int freqB[VALMAX];
int freqC[NMAX];

int main()
{
    ifstream cin("bacterii2.in");
    ofstream cout("bacterii2.out");

    int T = 0;
    cin >> T;

    while (T --) {
        memset(freqA, 0, sizeof freqA);
        memset(freqB, 0, sizeof freqB);

        int N;
        cin >> N;
        int maxA = 0;
        while (N --) {
            int val;
            cin >> val;
            ++ freqA[val];
            maxA = max(maxA, val);
        }

        int M;
        cin >> M;
        int maxB = 0;
        while (M --) {
            int val;
            cin >> val;
            ++ freqB[val];
            maxB = max(maxB, val);
        }

        convolute(freqA, maxA + 1, freqB, maxB + 1, freqC);

        for (int i = 0; i <= maxA + maxB; ++ i)
            if (freqC[i])
                cout << i << ' ' << freqC[i] << '\n';
        if (T)
            cout << '\n';
    }

    return 0;
}
