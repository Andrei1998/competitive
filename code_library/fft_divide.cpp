#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000000 + 7;
const int NMAX = 100000 + 5;
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
inline int inv(int nr) {
    return raise(nr, MOD - 2);
}
int N, K;
int facts[NMAX];
int invFacts[NMAX];
int catalan[NMAX];
void precalc() {
    facts[0] = 1;
    for (int i = 1; i <= N; ++ i)
        facts[i] = (1LL * facts[i - 1] * i) % MOD;

    invFacts[N] = inv(facts[N]);
    for (int i = N - 1; i >= 0; -- i)
        invFacts[i] = ((i + 1LL) * invFacts[i + 1]) % MOD;

    catalan[1] = 1;
    for (int i = 1; 2 * i <= N && i <= K; ++ i)
        catalan[2 * i] = ((1LL * facts[2 * (i - 1)] * invFacts[i - 1]) % MOD * invFacts[i]) % MOD;
}
inline void add(int &where, int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}
int dp[NMAX];

struct Point {
    long double x, y;
    explicit Point(): x(0), y(0) {}
    explicit Point(long double _x, long double _y): x(_x), y(_y) {}
    explicit Point(long double theta): x(cosl(theta)), y(sinl(theta)) {}
    Point operator+(const Point &arg) const { return Point(x + arg.x, y + arg.y); }
    Point operator-(const Point &arg) const { return Point(x - arg.x, y - arg.y); }
    Point operator*(const Point &arg) const { return Point(x * arg.x - y * arg.y, x * arg.y + y * arg.x); }
    Point operator/(const int &arg) const { return Point(x / arg, y / arg); }
    friend inline Point conj(const Point &arg) { return Point(arg.x, -arg.y); }
    long double real() const { return x; }
    long double imag() const { return y; }
};
ostream& operator<<(ostream &g, const Point &p) {
    g << '(' << p.x << ',' << p.y << ')';
    return g;
}

const long double PI = acosl(-1.0L);
//typedef complex <long double> Point;
const int FFT_BITSMAX = 18;
const int FFT_NMAX    = (1 << FFT_BITSMAX);

Point w[2][2 * FFT_NMAX];
void precomputeRoots() {
    w[0][1] = w[1][1] = Point(1, 0);
    for (int k = 1; k <= FFT_BITSMAX; ++ k) {
        Point W0(2.0 * PI / (1 << k));
        Point W1 = conj(W0);
        const int bound = (1 << k);
        for (int i = (1 << (k - 1)); i < bound; ++ i) {
            w[0][2 * i] = w[0][i], w[0][2 * i + 1] = w[0][i] * W0;
            w[1][2 * i] = w[1][i], w[1][2 * i + 1] = w[1][i] * W1;
        }
    }
}

int rev[FFT_NMAX];
void fft(Point v[], const int BITS, const bool inv = false) {
    static bool computed = false;
    if (!computed)
        precomputeRoots(), computed = true;
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
        //long double theta = PI / len;
        //if (inv) theta *= (-1);
        //const Point w = Point(cos(theta), sin(theta));
        for (int start = 0; start < N; start += 2 * len) {
            //Point wk = Point(1, 0);
            for (int i = 0; i < len; ++ i) {
                const Point b = v[start + i + len] * w[inv][2 * len + i];
                //const Point b = v[start + i + len] * wk;
                v[start + i + len] = v[start + i] - b;
                v[start + i] = v[start + i] + b;

                //wk = wk * w;
            }
        }
    }
    if (inv)
        for (int i = 0; i < N; ++ i)
            v[i] = v[i] / N;
}

Point aux[1 << 18];
void dualFft(const int BITS, Point a[], Point b[]) {
    int N = (1 << BITS);
    for (int i = 0; i < N; ++ i)
        aux[i] = Point(a[i].real(), b[i].real());
    fft(aux, BITS);

    for (int i = 0; i < N; ++ i) {
        int j = (N - i) & (N - 1);
        a[i] = (aux[i] + conj(aux[j])) * Point(0.5L, 0);
        b[i] = (aux[i] - conj(aux[j])) * Point(0, -0.5L);
    }
}

void dualFftINV(const int BITS, Point a[], Point b[]) {
    int N = (1 << BITS);
    for (int i = 0; i < N; ++ i)
        aux[i] = a[i] + b[i] * Point(0, 1);
    fft(aux, BITS, -1);

    for (int i = 0; i < N; ++ i) {
        a[i] = Point(aux[i].real(), 0);
        b[i] = Point(aux[i].imag(), 0);
    }
}

int M, P;

int a[NMAX];
Point ca[1 << 18];
Point ca1[1 << 18];
Point ca2[1 << 18];
Point ca3[1 << 18];

int b[NMAX];
Point cb[1 << 18];
Point cb1[1 << 18];
Point cb2[1 << 18];
Point cb3[1 << 18];

Point ca1cb1[1 << 18];
Point ca2cb2[1 << 18];
Point csum[1 << 18];

int res[1 << 18];
Point cres[1 << 18];

typedef long long int lint;

void convolute() {
    if (M * P < 100000) {
        //Brute for small sizes
        for (int i = 0; i <= M + P; ++ i)
            res[i] = 0;
        for (int i = 0; i <= M; ++ i)
            for (int j = 0; j <= P; ++ j)
                res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % MOD;
    }
    else {
        int BITS = 0;
        while ((1 << BITS) <= M + P)
            ++ BITS;

        for (int i = 0; i <= M; ++ i) {
            ca[i] = Point(a[i], 0);
            ca1[i] = Point(a[i] / 31622, 0);
            ca2[i] = Point(a[i] % 31622, 0);
        }
        for (int i = M + 1; i < (1 << BITS); ++ i)
            ca[i] = ca1[i] = ca2[i] = Point(0, 0);

        for (int i = 0; i <= P; ++ i) {
            cb[i] = Point(b[i], 0);
            cb1[i] = Point(b[i] / 31622, 0);
            cb2[i] = Point(b[i] % 31622, 0);
        }
        for (int i = P + 1; i < (1 << BITS); ++ i)
            cb[i] = cb1[i] = cb2[i] = Point(0, 0);

        dualFft(BITS, ca1, cb1);
        dualFft(BITS, ca2, cb2);

        for (int i = 0; i < (1 << BITS); ++ i) {
            ca3[i] = ca2[i] + ca1[i];
            cb3[i] = cb2[i] + cb1[i];

            ca1cb1[i] = ca1[i] * cb1[i];
            ca2cb2[i] = ca2[i] * cb2[i];
            csum[i] = ca3[i] * cb3[i] - ca1cb1[i] - ca2cb2[i];
        }

        dualFftINV(BITS, ca1cb1, ca2cb2);
        fft(csum, BITS, -1);

        for (int i = 0; i < (1 << BITS); ++ i) {
            int gr2 = ((lint)(ca1cb1[i].real() + 0.5L)) % MOD;
            int gr1 = ((lint)(csum[i].real() + 0.5L)) % MOD;
            int gr0 = ((lint)(ca2cb2[i].real() + 0.5L)) % MOD;
            res[i] = (1LL * 31622 * 31622 * gr2 + 1LL * 31622 * gr1 + gr0) % MOD;
        }
    }
}

void solve(int l, int r) {
    //cout << "Solve " << l << ' ' << r << endl;
    if (l == r) {
        add(dp[l], catalan[l]); //Group with 0
        return ;
    }

    int mid = (l + r) >> 1;
    solve(l, mid);

    M = mid - l;
    P = r - l;
    for (int i = l; i <= mid; ++ i)
        a[i - l] = dp[i];
    for (int i = 0; i <= r - l; ++ i)
        b[i] = catalan[i];

    // FFT
    convolute();

    for (int i = mid + 1; i <= r; ++ i)
        add(dp[i], res[i - l]);

    solve(mid + 1, r);
}

/*int brute[NMAX];
void solveBrute() {
    brute[0] = 1;
    for (int i = 1; i <= N; ++ i) {
        for (int l = 0; l <= i; ++ l)
            add(brute[i], (1LL * brute[l] * catalan[i - l]) % MOD);
        cout << i << ' ' << brute[i] << ' ' << dp[i] << endl;
    }
}*/

int main()
{
    cin >> N >> K;

    //N = 100000;
    //K = 100000;

    precalc();

    solve(1, N);

    cout << dp[N] << '\n';
    return 0;
}
