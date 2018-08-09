#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

inline void add(lint &where, const lint val, const lint MOD) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}

lint multiply(const lint a, lint b, const lint MOD) {
    lint ans = 0, aux = a % MOD;
    while (b) {
        if (b & 1)
            add(ans, aux, MOD);
        add(aux, aux, MOD);
        b >>= 1;
    }
    return ans;
}

lint expo(const lint a, lint b, const lint MOD) {
    assert(b >= 0);
    lint ans = 1, aux = a % MOD;
    while (b) {
        if (b & 1)
            ans = multiply(ans, aux, MOD);
        aux = multiply(aux, aux, MOD);
        b >>= 1;
    }
    return ans;
}

class QuadraticIdentity {
public:
    bool halve(vector <lint> &v) {
        const int N = v.size();
        if (N <= 500)
            return false;
        int pos = 0;
        for (int i = 0; i < v.size(); i += 2)
            v[pos ++] = v[i];
        v.resize(pos);
        return true;
    }

    lint crt(const vector <lint> &_p, const vector <lint> &_r, const vector <lint> &_before) {
        const int N = _p.size();
        assert(_r.size() == N);

        vector <lint> p(N + 1), r(N + 1), before(N + 1);
        for (int i = 1; i <= N; ++ i)
            p[i] = _p[i - 1], r[i] = _r[i - 1], before[i] = _before[i - 1];

        vector <lint> pref_prod(N + 1), suf_prod(N + 2);

        pref_prod[0] = 1;
        for (int i = 1; i <= N; ++ i)
            pref_prod[i] = pref_prod[i - 1] * p[i];

        suf_prod[N + 1] = 1;
        for (int i = N; i >= 1; -- i)
            suf_prod[i] = suf_prod[i + 1] * p[i];

        vector <lint> without(N + 2);
        vector <lint> other(N + 2);

        int j;
        lint ans = 0;
        for (int i = 1; i <= N; ++ i) {
            without[i] = 1;
            for (j = 1; j <= N; ++ j)
                if (i != j)
                    without[i] = multiply(without[i], p[j],  p[i]);

            const lint exp = expo(without[i], before[i], p[i]);
            other[i] = multiply(r[i], exp, p[i]);
            add(ans, multiply(multiply(pref_prod[i - 1], other[i], pref_prod[N]), suf_prod[i + 1], pref_prod[N]), pref_prod[N]);
        }

        return ans;
    }

    vector <lint> getFixedPoints(lint nr) {
        vector <lint> prs;
        vector <lint> before;
        auto f = [&](const lint i) {
            if (nr % i == 0) {
                lint pr = 1;
                while (nr % i == 0) {
                    nr /= i;
                    pr *= i;
                }

                prs.push_back(pr);
                before.push_back(pr - pr / i - 1);
            }
        };

        f(2);
        for (lint i = 3; i * i <= nr; i += 2)
            f(i);
        if (nr > 1) {
            prs.push_back(nr);
            before.push_back(nr - 2);
        }
        sort(prs.begin(), prs.end());

        vector <lint> ans;
        int N = prs.size();
        vector <lint> r(N);
        for (int i = 0; i < (1 << N); ++ i) {
            for (int j = 0; j < N; ++ j)
                if (i & (1 << j))
                    r[j] = 1;
                else
                    r[j] = 0;
            ans.push_back(crt(prs, r, before));
        }

        sort(ans.begin(), ans.end());
        while (halve(ans));
        return ans;
    }
};

int main() {
    QuadraticIdentity q;
    //auto x = q.getFixedPoints(2LL*3*5*7*11*13*17*19*23*29*31*37*41);
    auto x = q.getFixedPoints(7);
    for (auto it: x)
        cout << it << ' ';
    cout << endl;
    return 0;
}
