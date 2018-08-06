/*
ID: andreip3
LANG: C++14
TASK: buylow
*/
#include <bits/stdc++.h>

using namespace std;

const int BASE = 100000000;
const int DIGITS = 10;

struct BigInteger {
    int val[DIGITS + 2];
};

void init(BigInteger &a) {
    int i;
    a.val[0] = a.val[1] = 1;
    for(i = 2; i < DIGITS + 2; i ++)
        a.val[i] = 0;
}

BigInteger suma(BigInteger a, BigInteger b) {
    BigInteger c;
    init(c);
    c.val[0] = max(a.val[0], b.val[0]);
	
    int i, tr = 0;
    for (i = 1; i <= c.val[0]; i ++) {
        c.val[i] = a.val[i] + b.val[i] + tr;
        tr = c.val[i] / BASE;
        c.val[i] %= BASE;
    }

    while (tr) {
        c.val[++c.val[0]] = tr;
        tr=c.val[c.val[0]] / BASE;
        c.val[c.val[0]] %= BASE;
    }
    return c;
}

void afis(BigInteger &a) {
    for(int i = a.val[0]; i ; --i) {
        if (i < a.val[0]) {
            if (a.val[i] / 10 == 0)
                cout << '0';
            if (a.val[i] / 100 == 0)
                cout << '0';
            if (a.val[i] / 1000 == 0)
                cout << '0';
            if (a.val[i] / 10000 == 0)
                cout << '0';
            if (a.val[i] / 100000 == 0)
                cout << '0';
            if (a.val[i] / 1000000 == 0)
                cout << '0';
            if (a.val[i] / 10000000 == 0)
                cout << '0';
        }
        cout << a.val[i];
    }
}

const int NMAX = 5000 + 5;
int N, v[NMAX];

typedef long long int lint;
int dp[NMAX];
BigInteger cnt[NMAX];

int main() {
    freopen("buylow.in", "r", stdin);
    freopen("buylow.out", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; ++ i)
        cin >> v[i];
    ++ N;

    map <int, int> last;
    for (int i = 0; i < N; ++ i) {
        dp[i] = 1;
        init(cnt[i]);
        for (auto it: last) {
            const int j = it.second;
            if (v[i] < v[j]) {
                if (dp[j] + 1 > dp[i])
                    dp[i] = dp[j] + 1, cnt[i] = cnt[j];
                else if (dp[j] + 1 == dp[i])
                    cnt[i] = suma(cnt[i], cnt[j]);
            }
        }
        last[v[i]] = i;
    }

    cout << dp[N - 1] - 1 << ' ';
    afis(cnt[N - 1]);
    cout << '\n';
    return 0;
}
