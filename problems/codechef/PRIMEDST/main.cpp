#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int NMAX = 50000 + 5;

struct Point {
    double x, y;

    Point(double _x = 0, double _y = 0):
        x(_x), y(_y) {}

    friend Point operator+(const Point &a, const Point &b) {
        return Point(a.x + b.x, a.y + b.y);
    }
    friend Point operator-(const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }
    friend Point operator*(const Point &a, const Point &b) {
        return Point(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    friend void operator/=(Point &a, const double &alpha) {
        a.x /= alpha;
        a.y /= alpha;
    }
};

//FFT
const double PI = acos(-1);

int bitRev[4 * NMAX];
Point p[4 * NMAX];

void fft(int n, int bits, int inv = 1) {
    for (int i = 1; i < n; ++ i)
        bitRev[i] = (bitRev[i >> 1] >> 1) + (i & 1) * (1 << (bits - 1));

    for (int i = 0; i < n; ++ i)
        if (i < bitRev[i])
            swap(p[i], p[bitRev[i]]);

    for (int step = 2; step <= n; step *= 2) {
        double ang = inv * 2 * PI / step;
        Point w = Point(cos(ang), sin(ang));
        for (int start = 0; start < n; start += step) {
            Point wk(1);
            for (int i = 0; i < step / 2; ++i) {
                Point u = p[start + i];
                Point v = p[start + i + step / 2];

                p[start + i]            = u + wk * v;
                p[start + i + step / 2] = u - wk * v;

                wk = wk * w;
            }
        }
    }

    if (inv == -1)
        for (int i = 0; i < n; ++ i)
            p[i] /= n;
}

void product(int n, int v[]) {
    if (n <= 50) {
        int aux[105] = {0};
        for (int i = 0; i <= n; ++ i)
            for (int j = 0; j <= n; ++ j)
                aux[i + j] += v[i] * v[j];

        for (int i = 0; i <= 2 * n; ++ i)
            v[i] = aux[i];
        return ;
    }

    int k = 1, bits = 0;
    while (k <= 2 * n)
        k *= 2, ++bits;

    for (int i = 0; i < k; ++ i)
        p[i] = Point(v[i]);
    fft(k, bits);

    for (int i = 0; i < k; ++ i)
        p[i] = p[i] * p[i];
    fft(k, bits, -1);

    for (int i = 0; i < k; ++ i)
        v[i] = p[i].x + 0.5;
}

//Problem

int n;
vector <int> tree[NMAX];

bool vis[NMAX];

int sz[NMAX];
void computeSz(int node, int father) {
    sz[node] = 1;
    for (auto son: tree[node])
        if (son != father && !vis[son]) {
            computeSz(son, node);
            sz[node] += sz[son];
        }
}

int szRoot;
int centroid;

void getCentroid(int node, int father) {
    int largestSon = 0;
    for (auto son: tree[node])
        if (son != father && !vis[son]) {
            getCentroid(son, node);
            if (centroid)
                return ;
            if (sz[son] > largestSon)
                largestSon = sz[son];
        }

    if (szRoot - sz[node] > largestSon)
        largestSon = szRoot - sz[node];
    if (largestSon <= szRoot / 2)
        centroid = node;
}

int freqAns[2 * NMAX];

int maxH;
void addDists(int node, int father, int h, int freq[], int val = 1) {
    maxH = max(maxH, h);
    freq[h] += val;
    for (auto son: tree[node])
        if (son != father && !vis[son])
            addDists(son, node, h + 1, freq, val);
}

int freq[2 * NMAX];

void DEI(int node) {
    computeSz(node, 0);
    szRoot = sz[node];
    getCentroid(node, 0);

    maxH = 0;
    for (auto son: tree[centroid])
        if (!vis[son])
            addDists(son, centroid, 1, freq);
    ++freq[0];

    //FFT
    product(maxH, freq);

    //Add to global count
    for (int i = 0; i <= 2 * maxH; ++ i) {
        freqAns[i] += freq[i];
        freq[i] = 0;
    }

    for (auto son: tree[centroid])
        if (!vis[son]) {
            maxH = 0;
            addDists(son, centroid, 1, freq);

            //FFT
            product(maxH, freq);

            //Subtract from global count
            for (int i = 0; i <= 2 * maxH; ++ i) {
                freqAns[i] -= freq[i];
                freq[i] = 0;
            }
        }

    ++freqAns[0]; //The root is only counted once

    vis[centroid] = true;
    for (auto son: tree[centroid])
        if (!vis[son])
            DEI(son);
}

bool sieve[NMAX];
void Erat() {
    for (int i = 2; i * i <= n; ++ i)
        if (!sieve[i])
            for (int j = i * i; j <= n; j += i)
                sieve[j] = true;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    //freopen("data.in", "r", stdin);

    cin >> n;

    int a, b;
    for (int i = 1; i < n; ++ i) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    DEI(1);
    for (int i = 0; i < n; ++ i)
        freqAns[i] /= 2;

    Erat();
    int ans = 0;
    for (int i = 2; i < n; ++ i)
        if (!sieve[i])
            ans += freqAns[i];

    cout << fixed << setprecision(6) << 1.0 * ans / (n * (n - 1) / 2) << '\n';
    return 0;
}
