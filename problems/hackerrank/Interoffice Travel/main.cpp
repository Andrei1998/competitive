#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;

//typedef complex <double> Point;

struct Point {
    double real;
    double imag;

    Point(double _real = 0, double _imag = 0):
        real(_real), imag(_imag) {}

    friend Point operator+(const Point &a, const Point &b) {
        return Point(a.real + b.real, a.imag + b.imag);
    }
    friend Point operator-(const Point &a, const Point &b) {
        return Point(a.real - b.real, a.imag - b.imag);
    }
    friend Point operator/(const Point &a, const double &b) {
        return Point(a.real / b, a.imag / b);
    }
    friend Point operator*(const Point &a, const Point &b) {
        return Point(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
    }
};

const int NMAX = 100000 + 5;
const double PI = acos(-1);

int bitRev[20][1 << 19];

void fft(Point p[], int N, int BITS, int inv) {
    for (int i = 0; i < N; ++ i)
        if (i < bitRev[BITS][i])
            swap(p[i], p[bitRev[BITS][i]]);

    for (int len = 2; len <= N; len *= 2) {
        double theta = 2 * PI / len * inv;
        Point w = Point(cos(theta), sin(theta));
        for (int start = 0; start < N; start += len) {
            Point wk = 1;
            for (int i = 0; i < len / 2; ++ i) {
                Point a = p[start + i];
                Point b = wk * p[start + i + len / 2];

                p[start + i] = a + b;
                p[start + i + len / 2] = a - b;
                wk = wk * w;
            }
        }
    }

    if (inv == -1)
        for (int i = 0; i < N; ++ i)
            p[i] = p[i] / N;
}

int N;
vector <int> graph[NMAX];
int w[2 * NMAX];
int ans[NMAX];

bool vis[NMAX];
int sz[NMAX];

void dfsSz(int node, int father) {
    sz[node] = 1;
    for (auto it: graph[node])
        if (it != father && !vis[it]) {
            dfsSz(it, node);
            sz[node] += sz[it];
        }
}

int dfsCentroid(int node, int all, int father) {
    for (auto it: graph[node])
        if (it != father && sz[it] > all / 2 && !vis[it])
            return dfsCentroid(it, all, node);
    return node;
}

int h[NMAX];
int hFreq[NMAX];
int maxH;

void addH(int node, int father) {
    maxH = max(maxH, h[node]);
    ++ hFreq[h[node]];
    for (auto it: graph[node])
        if (it != father && !vis[it]) {
            h[it] = 1 + h[node];
            addH(it, node);
        }
}

int a[2 * NMAX];
int b[2 * NMAX];
int res[4 * NMAX];

Point ca[4 * NMAX];
Point cb[4 * NMAX];
Point cres[4 * NMAX];

void convolute(int N) {
    if (N <= 20) {
        for (int i = 0; i < N; ++ i)
            res[i] = 0;
        for (int i = 0; i < N; ++ i)
            for (int j = 0; i + j < N; ++ j)
                res[i] += a[j] * b[i + j];
    }
    else {
        reverse(a, a + N);

        int K = 1;
        int bits = 0;

        while (K < 2 * N) {
            K *= 2;
            ++ bits;
        }

        for (int i = 0; i < N; ++ i) {
            ca[i] = a[i];
            cb[i] = b[i];
        }

        for (int i = N; i < K; ++ i)
            ca[i] = cb[i] = 0;

        fft(ca, K, bits, 1);
        fft(cb, K, bits, 1);
        for (int i = 0; i < K; ++ i)
            cres[i] = ca[i] * cb[i];
        fft(cres, K, bits, -1);

        for (int i = 0; i < N; ++ i)
            res[i] = cres[i + N - 1].real + 0.5;
    }
}

void addAns(int node, int father, int val) {
    ans[node] += val * res[h[node]];
    for (auto it: graph[node])
        if (it != father && !vis[it])
            addAns(it, node, val);
}

void DEI(int node) {
    dfsSz(node, 0);
    node = dfsCentroid(node, sz[node], 0);

    //Add everything
    h[node] = maxH = 0;
    addH(node, 0);

    //Convolution
    maxH *= 2;
    ++ maxH;
    for (int i = 0; i < maxH; ++ i)
        a[i] = hFreq[i];
    for (int i = 0; i < maxH; ++ i)
        b[i] = w[i];
    convolute(maxH);

    //Add
    addAns(node, 0, 1);
    //Reset
    for (int i = 0; i < maxH; ++ i)
        hFreq[i] = 0;

    //Subtract every subtree
    for (auto it: graph[node])
        if (!vis[it]) {
            maxH = 0;
            addH(it, node);
            //Convolution
            maxH *= 2;
            ++ maxH;
            for (int i = 0; i < maxH; ++ i) {
                a[i] = hFreq[i];
            }
            for (int i = 0; i < maxH; ++ i)
                b[i] = w[i];

            convolute(maxH);

            //Add
            addAns(it, node, -1);
            //Reset
            for (int i = 0; i < maxH; ++ i)
                hFreq[i] = 0;
        }

    vis[node] = true;
    for (auto it: graph[node])
        if (!vis[it])
            DEI(it);
}

int main()
{
    for (int bits = 0; bits < 20; ++ bits) {
        for (int i = 1; i < (1 << bits); ++ i) {
            bitRev[bits][i] = bitRev[bits][i >> 1] >> 1;
            if (i & 1)
                bitRev[bits][i] += (1 << (bits - 1));
        }
    }

    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++ i)
        cin >> w[i];

    for (int i = 1; i < N; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    DEI(1);

    for (int i = 1; i <= N; ++ i)
        cout << ans[i] << " \n"[i == N];
    return 0;
}
