#include <bits/stdc++.h>

using namespace std;

const long double PI = acosl(-1.0L);
typedef complex <long double> Point;
const int BITSMAX = 22;
const int NMAX    = (1 << BITSMAX);

/*struct Point {
    double x, y;
    Point(): x(0), y(0) {}
    explicit Point(double _x, double _y): x(_x), y(_y) {}
    explicit Point(double theta): x(cos(theta)), y(sin(theta)) {}
    Point operator+(const Point &arg) const { return Point(x + arg.x, y + arg.y); }
    Point operator-(const Point &arg) const { return Point(x - arg.x, y - arg.y); }
    Point operator*(const Point &arg) const { return Point(x * arg.x - y * arg.y, x * arg.y + y * arg.x); }
    Point operator/(const int &arg) const { return Point(x / arg, y / arg); }
    friend inline Point conj(const Point &arg) { return Point(arg.x, -arg.y); }
};
ostream& operator<<(ostream &g, const Point &p) {
    g << '(' << p.x << ',' << p.y << ')';
    return g;
}
Point w[2][2 * NMAX];
void precomputeRoots() {
    w[0][1] = w[1][1] = Point(1, 0);
    for (int k = 1; k <= BITSMAX; ++ k) {
		Point W0(2.0 * PI / (1 << k));
		Point W1 = conj(W0);
		const int bound = (1 << k);
        for (int i = (1 << (k - 1)); i < bound; ++ i) {
			w[0][2 * i] = w[0][i], w[0][2 * i + 1] = w[0][i] * W0;
            w[1][2 * i] = w[1][i], w[1][2 * i + 1] = w[1][i] * W1;
        }
    }
}*/

int rev[NMAX];
void fft(Point v[], const int BITS, const bool inv = false) {
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
        long double theta = PI / len;
        if (inv) theta *= (-1);
        const Point w = Point(cos(theta), sin(theta));
        for (int start = 0; start < N; start += 2 * len) {
            Point wk = Point(1, 0);
            for (int i = 0; i < len; ++ i) {
                //const Point b = v[start + i + len] * w[inv][2 * len + i];
                const Point b = v[start + i + len] * wk;
                v[start + i + len] = v[start + i] - b;
                v[start + i] = v[start + i] + b;

                wk = wk * w;
            }
        }
    }
    if (inv)
        for (int i = 0; i < N; ++ i)
            v[i] /= N;
}

Point pointsA[2 * NMAX], pointsB[2 * NMAX], pointsRes[2 * NMAX];

void convolute(int Na, int Nb) {
    /*if (Na * Nb <= 16 * 16) {
        for (int i = 0; i < Na + Nb; ++ i)
            res[i] = 0;
        for (int i = 0; i < Na; ++ i)
            for (int j = 0; j < Nb; ++ j)
                res[i + j] += a[i] * b[j];
        return ;
    }*/

    int BITS = 0;
    while ((1 << BITS) < Na + Nb - 1) ++ BITS;
    const int N = (1 << BITS);

    fft(pointsA, BITS);
    fft(pointsB, BITS);

    for (int i = 0; i < N; ++ i)
        pointsRes[i] = pointsA[i] * pointsB[i];

    fft(pointsRes, BITS, true);
}

Point weights[4][10];
Point conj_weights[4][10];

int to_int(char ch) {
    if (ch == 'n') {
        return 0;
    }
    if (ch == 's') {
        return 1;
    }
    if (ch == 'e') {
        return 2;
    }
    if (ch == 'w') {
        return 3;
    }
    assert(false);
}

int main()
{
    srand(time(nullptr));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 10; ++j) {
            weights[i][j] = polar(1.0L, (rand() % 10000) + (rand() % 100) * 0.01L);
            conj_weights[i][j] = conj(weights[i][j]); 
        }
    }

    int M, N;
    cin >> N >> M;
    assert(1 <= M && M < N && N <= 400000);

    for (int i = 0; i < N; ++i) {
        char ch;
        cin >> ch;
        if (ch != '?') {
            int nr = to_int(ch);
            int s;
            cin >> s;
            assert(0 <= nr && nr < 4);
            assert(0 <= s && s < 10);
            pointsA[i] = weights[nr][s];
        }
    }

    for (int i = 0; i < M; ++i) {
        char ch;
        cin >> ch;
        if (ch != '?') {
            int nr = to_int(ch);
            int s;
            cin >> s;
            assert(0 <= nr && nr < 4);
            assert(0 <= s && s < 10);
            // Also reverse.
            pointsB[M - i - 1] = conj_weights[nr][s];
        }
    }

    convolute(N, M);

    int ans = 0;
    for (int i = M - 1; i < N; ++i) {
        const Point x = pointsRes[i];
        if (fabsl(x.imag()) < 1E-8L && fabsl(x.real() - round(x.real())) < 1E-8L) {
            ++ans;
        }
    }

    cout << ans << endl;
    return 0;
}