#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);
typedef complex <double> Point;
const int BITSMAX = 16;
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
        double theta = PI / len;
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

Point points[NMAX], pointsA[NMAX], pointsB[NMAX], pointsRes[NMAX];

template <typename RandomIt>
void convolute(RandomIt a, int Na, RandomIt b, int Nb, RandomIt res) {
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

    for (int i = 0; i < Na; ++ i)
        points[i] = Point(a[i], 0);
    for (int i = Na; i < N; ++ i)
        points[i] = Point();
    for (int i = 0; i < Nb; ++ i)
        points[i] = Point(points[i].real(), b[i]);

    fft(points, BITS);

    for (int i = 0; i < N; ++ i) {
        const Point &A = points[i];
        const Point &B = conj(points[(N - i) & (N - 1)]);
        pointsA[i] = (A + B) * Point(0.5, 0);
        pointsB[i] = (A - B) * Point(0, -0.5);
    }

    for (int i = 0; i < N; ++ i)
        pointsRes[i] = pointsA[i] * pointsB[i];

    fft(pointsRes, BITS, true);

    for (int i = 0; i < N; ++ i)
        res[i] = pointsRes[i].real() + 0.5;
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
