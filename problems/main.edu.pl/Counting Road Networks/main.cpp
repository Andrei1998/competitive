#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

bool prime(int nr) {
    if (nr <= 1)
        return false;
    for (int i = 2; i * i <= nr; ++ i)
        if (nr % i == 0)
            return false;
    return true;
}

const int MOD = 663224321;
int fct[4] = {2, 5, 11, 23};

int raise(int a, long long int b) {
    if (!b)
        return 1;
    else if (b & 1)
        return (1LL * raise(a, b - 1) * a) % MOD;
    else {
        int aux = raise(a, b >> 1);
        return (1LL * aux * aux) % MOD;
    }
}

inline int inv(int nr) {
    return raise(nr, MOD - 2);
}

int gen;
void findGen() {
    for (gen = 3; gen < MOD; ++ gen) {
        bool ok = true;
        for (int i = 0; i < sizeof(fct) / sizeof(int); ++ i)
            if (raise(gen, (MOD - 1) / fct[i]) == 1) {
                ok = false;
                break;
            }
        if (ok)
            break;
    }
}

int bitReversal[19][1 << 18];

void fft(int N, int BITS, int p[], bool rev) {
    for (int i = 0; i < N; ++ i)
        if (i < bitReversal[BITS][i])
            swap(p[i], p[bitReversal[BITS][i]]);

    for (int len = 2; len <= N; len *= 2) {
        int w = raise(gen, (MOD - 1) / len);
        if (rev)
            w = inv(w);

        for (int start = 0; start < N; start += len) {
            for (int i = 0, wk = 1; i < len / 2; ++ i, wk = (1LL * wk * w) % MOD) {
                int a = p[start + i];
                int b = (1LL * wk * p[start + i + len / 2]) % MOD;

                p[start + i] = a + b;
                if (p[start + i] >= MOD)
                    p[start + i] -= MOD;

                p[start + i + len / 2] = a - b;
                if (p[start + i + len / 2] < 0)
                    p[start + i + len / 2] += MOD;
            }
        }
    }

    if (rev) {
        int invN = inv(N);
        for (int i = 0; i < N; ++ i)
            p[i] = (1LL * p[i] * invN) % MOD;
    }
}

int a[1 << 18];
int Na;
int b[1 << 18];
int Nb;
int res[1 << 18];
int Nres;

void convolute() {
    if (Na * Nb <= 500000) {
        for (int i = 0; i < Na + Nb - 1; ++ i)
            res[i] = 0;
        for (int i = 0; i < Na; ++ i)
            for (int j = 0; j < Nb; ++ j)
                res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % MOD;
    }
    else {
        int bits = 0;
        while ((1 << bits) < Na + Nb - 1)
            ++ bits;

        for (int i = Na; i < (1 << bits); ++ i)
            a[i] = 0;
        fft(1 << bits, bits, a, false);

        for (int i = Nb; i < (1 << bits); ++ i)
            b[i] = 0;
        fft(1 << bits, bits, b, false);

        for (int i = 0; i < (1 << bits); ++ i)
            res[i] = (1LL * a[i] * b[i]) % MOD;
        fft(1 << bits, bits, res, true);
    }
    Nres = Na + Nb - 1;
}

const int NMAX = 100000 + 5;
int facts[NMAX];
int invFacts[NMAX];

int c[NMAX];

int cFactor[NMAX];
int lenFactor[NMAX];

void DEI(int st, int dr) {
    if (st == dr) {
        c[st] = (1LL * c[st] * facts[st - 1]) % MOD;
        c[st] = raise(2, st * (st - 1LL) / 2) - c[st];
        if (c[st] < 0)
            c[st] += MOD;

        cFactor[st] = (1LL * c[st] * invFacts[st - 1]) % MOD;

        return ;
    }

    int mid = (st + dr) >> 1;
    DEI(st, mid);

    Na = 0;
    for (int i = st; i <= mid; ++ i)
        a[Na ++] = cFactor[i];
    Nb = 0;
    for (int i = 1; i <= dr - st; ++ i)
        b[Nb ++] = lenFactor[i];

    convolute();
    for (int i = 0; i < Nres; ++ i) {
        if (i + st + 1 > mid && i + st + 1 <= dr) {
            c[i + st + 1] += res[i];
            if (c[i + st + 1] >= MOD)
                c[i + st + 1] -= MOD;
        }
    }

    DEI(mid + 1, dr);
}

int main()
{
    for (int bits = 0; bits < 19; ++ bits) {
        for (int i = 1; i < (1 << bits); ++ i) {
            bitReversal[bits][i] = bitReversal[bits][i >> 1] >> 1;
            if (i & 1)
                bitReversal[bits][i] += (1 << (bits - 1));
        }
    }

    facts[0] = 1;
    for (int i = 1; i <= 100000; ++ i)
        facts[i] = (1LL * facts[i - 1] * i) % MOD;
    invFacts[100000] = inv(facts[100000]);
    for (int i = 100000 - 1; i >= 0; -- i)
        invFacts[i] = ((i + 1LL) * invFacts[i + 1]) % MOD;
    for (int i = 1; i <= 100000; ++ i)
        lenFactor[i] = (1LL * raise(2, i * (i - 1LL) / 2) * invFacts[i]) % MOD;
    findGen();

    DEI(1, 100000);

    int Q = 0;
    cin >> Q;

    while (Q --) {
        int cnt;
        cin >> cnt;
        cout << c[cnt] << '\n';
    }
    return 0;
}
