#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300000 + 5;
const int VALMAX = 2 * 15000 + 5;

typedef long long int lint;

lint aib[VALMAX + 5][4];
static inline void updateAib(int where, lint val0, lint val1, lint val2, lint val3) {
    ++ where;
    for (; where < VALMAX + 5; where += where & (-where)) {
        aib[where][0] += val0;
        aib[where][1] += val1;
        aib[where][2] += val2;
        aib[where][3] += val3;
    }
}

static inline void queryAib(int where, lint &ans0, lint &ans1, lint &ans2, lint &ans3) {
    ++ where;
    for (; where; where -= where & (-where)) {
        ans0 += aib[where][0];
        ans1 += aib[where][1];
        ans2 += aib[where][2];
        ans3 += aib[where][3];
    }
}
static inline void queryAib(int l, int r, lint &ans0, lint &ans1, lint &ans2, lint &ans3) {
    queryAib(l - 1, ans0, ans1, ans2, ans3);
    ans0 *= (-1);
    ans1 *= (-1);
    ans2 *= (-1);
    ans3 *= (-1);
    queryAib(r, ans0, ans1, ans2, ans3);
}

int N;
static inline void addPoint(const int x) {
    updateAib(x, 1, x, 1LL * x * x, 1LL * x * x * x);
}

__float128 query(const long double x, int l, int r) {
    lint ans0 = 0, ans1 = 0, ans2 = 0, ans3 = 0;
    queryAib(l, r, ans0, ans1, ans2, ans3);

    __float128 xx = x;

    return  xx * xx * xx * ans0
           -3.0L * xx * xx     * ans1
           +3.0L * xx          * ans2
           -1.0L               * ans3;
}

inline __float128 querySumDist(const long double x) {
    int till = (int)(floorl(x) + 100000.1) - 100000;
    __float128 ans = query(x, 0, till) - query(x, till + 1, VALMAX);
    return ans;
}

int main()
{
    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> N;
    N = 300000;
    for (int p = 1; p <= N; ++ p) {
        if (p % 10000 == 0)
            cout << p << endl;

        // Read new point
        int x;
        //cin >> x;
        x = rand() % 30000 - 15000;
        x += 15000;
        addPoint(x);

        // Ternary search
        long double l = 0, r = VALMAX;
        for (int s = 0; s < 45; ++ s) {
            long double mid1 = (2.0L * l + r) / 3.0L;
            long double mid2 = (l + 2.0L * r) / 3.0L;
            if (querySumDist(mid1) < querySumDist(mid2))
                r = mid2;
            else
                l = mid1;
        }

        //cout << fixed << setprecision(6) << (long double)(l - 15000.0L) << '\n';
    }

    return 0;
}
