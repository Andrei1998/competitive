#include <iostream>
#include <complex>

using namespace std;

// Ciobanu multiply
inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
	unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
	asm(
		"divl %4; \n\t"
		: "=a" (d), "=d" (m)
		: "d" (xh), "a" (xl), "r" (y)
	);
#else
	__asm {
		mov edx, dword ptr[xh];
		mov eax, dword ptr[xl];
		div dword ptr[y];
		mov dword ptr[d], eax;
		mov dword ptr[m], edx;
	};
#endif
	out_d = d; out_m = m;
}

// x / y < 2^32 !
inline unsigned fasterLLMod(unsigned long long x, unsigned y) {
	unsigned dummy, r;
	fasterLLDivMod(x, y, dummy, r);
	return r;
}
// End of multiply

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
        facts[i] = fasterLLMod(1ULL * facts[i - 1] * i, MOD);

    invFacts[N] = inv(facts[N]);
    for (int i = N - 1; i >= 0; -- i)
        invFacts[i] = fasterLLMod((i + 1ULL) * invFacts[i + 1], MOD);

    catalan[1] = 1;
    for (int i = 1; 2 * i <= N && i <= K; ++ i)
        catalan[2 * i] = fasterLLMod(1ULL * fasterLLMod(1ULL * facts[2 * (i - 1)] * invFacts[i - 1], MOD) * invFacts[i], MOD);
}

inline void add(int &where, int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}

int dp[NMAX];

// Do convolution
const long double PI = acos(-1);
//typedef complex <long double> Point;

struct Point {
    long double x, y;
    Point(long double _x = 0, long double _y = 0):
        x(_x), y(_y) {}

    Point operator+(const Point &arg) const {
        return Point(x + arg.x, y + arg.y);
    }
    Point operator-(const Point &arg) const {
        return Point(x - arg.x, y - arg.y);
    }
    Point operator*(const Point &arg) const {
        return Point(x * arg.x - y * arg.y, x * arg.y + y * arg.x);
    }
    Point operator/(const int &arg) const {
        return Point(x / arg, y / arg);
    }
    friend inline Point conj(const Point &arg) {
        return Point(arg.x, -arg.y);
    }
};

int rev[19][1 << 18];
Point w[2][19][1 << 18];

void fft(Point v[], const int BITS, const int inv = 1) {
    int N = (1 << BITS);
    for (int i = 0; i < N; ++ i) {
        int reved = rev[BITS][i];
        if (i < reved)
            swap(v[i], v[reved]);
    }

    bool type = (inv == 1);
    for (int len = 2, cnt = 1; len <= N; len <<= 1, ++ cnt)
        for (int start = 0; start < N; start += len)
            for (int i = 0; i < len / 2; ++ i) {
                Point a = v[start + i];
                Point b = w[type][cnt][i] * v[start + i + len / 2];

                v[start + i] = a + b;
                v[start + i + len / 2] = a - b;
            }

    if (inv == -1)
        for (int i = 0; i < N; ++ i)
            v[i] = v[i] / N;
}

Point aux[1 << 18];
void dualFft(const int BITS, Point a[], Point b[]) {
    int N = (1 << BITS);
    for (int i = 0; i < N; ++ i) {
        aux[i] = Point(a[i].x, b[i].x);
    }
    fft(aux, BITS);

    for (int i = 0; i < N; ++ i) {
        int j = (N - i) & (N - 1);
        a[i] = (aux[i] + conj(aux[j])) * Point(0.5, 0);
        b[i] = (aux[i] - conj(aux[j])) * Point(0, -0.5);
    }
}

void dualFftINV(const int BITS, Point a[], Point b[]) {
    int N = (1 << BITS);
    for (int i = 0; i < N; ++ i)
        aux[i] = a[i] + b[i] * Point(0, 1);
    fft(aux, BITS, -1);

    for (int i = 0; i < N; ++ i) {
        a[i] = aux[i].x;
        b[i] = aux[i].y;
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

void convolute() {
    if (M * P < 100000) { //CATCH
        // Brute for small sizes
        for (int i = 0; i <= M + P; ++ i)
            res[i] = 0;
        for (int i = 0; i <= M; ++ i)
            for (int j = 0; j <= P; ++ j)
                res[i + j] = fasterLLMod(res[i + j] + 1ULL * a[i] * b[j], MOD);
    }
    else {
        int BITS = 0;
        while ((1 << BITS) <= M + P)
            ++ BITS;

        for (int i = 0; i <= M; ++ i) {
            ca[i] = a[i];
            ca1[i] = a[i] / 31622;
            ca2[i] = a[i] - (a[i] / 31622) * 31622;
        }
        for (int i = M + 1; i < (1 << BITS); ++ i)
            ca[i] = ca1[i] = ca2[i] = 0;

        for (int i = 0; i <= P; ++ i) {
            cb[i] = b[i];
            cb1[i] = b[i] / 31622;
            cb2[i] = b[i] - (b[i] / 31622) * 31622;
        }
        for (int i = P + 1; i < (1 << BITS); ++ i)
            cb[i] = cb1[i] = cb2[i] = 0;

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
            int gr2 = fasterLLMod((unsigned long long int)(ca1cb1[i].x + 0.5), MOD);
            int gr1 = fasterLLMod((unsigned long long int)(csum[i].x + 0.5), MOD);
            int gr0 = fasterLLMod((unsigned long long int)(ca2cb2[i].x + 0.5), MOD);
            res[i] = fasterLLMod(1ULL * 31622 * 31622 * gr2 + 1ULL * 31622 * gr1 + gr0, MOD);
        }
    }
}

void solve(int l, int r) {
    //cout << "Solve " << l << ' ' << r << endl;
    if (l == r) {
        add(dp[l], catalan[l]); // Group with 0
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
    for (int bits = 0; bits <= 18; ++ bits) {
        for (int i = 1; i < (1 << bits); ++ i) {
            rev[bits][i] = rev[bits][i >> 1] >> 1;
            if (i & 1)
                rev[bits][i] += (1 << (bits - 1));
        }
    }
    for (int inv = 0; inv < 2; ++ inv)
        for (int bits = 1, len = 2; bits <= 18; ++ bits, len <<= 1) {
            w[inv][bits][0] = 1;
            w[inv][bits][1] = Point(cos(2 * PI / len), sin(2 * PI / len));

            if (!inv)
                w[inv][bits][1].y *= (-1);
            for (int i = 2; i < len / 2; ++ i)
                w[inv][bits][i] = w[inv][bits][i - 1] * w[inv][bits][1];
        }

    //cin >> N >> K;

    //N = 100000;
    //K = 100000;

    N = 100000;
    K = 91324;

    precalc();

    solve(1, N);

    cout << dp[N] << '\n';
    return 0;
}
