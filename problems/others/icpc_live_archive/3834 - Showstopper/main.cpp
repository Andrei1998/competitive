#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
const int PRIMES = sizeof(primes) / sizeof(int);
int invs[PRIMES][29];

typedef long long int lint;

struct Progr {
    unsigned a, r, n;
    Progr(unsigned _a = 0, unsigned _r = 0, unsigned _n = 0):
        a(_a), r(_r), n(_n) {}
};

vector <Progr> progrs;

int rem[PRIMES];

void process() {
    if (!progrs.empty()) {
        bool freq[29];
        for (int i = 0; i < PRIMES; ++ i) {
            const int p = primes[i];
            int &r = rem[i];
            r = -1;

            for (int j = 0; j < p; ++ j)
                freq[j] = 0;

            for (auto it: progrs) {
                it.a %= p;
                it.r %= p;
                it.n %= (2 * p);
                for (int j = 0, val = it.a; j < it.n; ++ j, val = val + it.r, val = (val >= p ? val - p : val))
                    freq[val] ^= 1;
            }

            for (int j = 0; j < p && r == -1; ++ j)
                if (freq[j])
                    r = j;

            if (r == -1) {
                cout << "no corruption\n";
                return ;
            }
        }

        lint prod = 1;
        for (int i = 0; i < PRIMES; ++ i)
            prod *= primes[i];

        lint ans = 0;
        for (int i = 0; i < PRIMES; ++ i)
            ans = (ans + (prod / primes[i]) * invs[i][(prod / primes[i]) % primes[i]] * rem[i]) % prod;

        if (ans == 0) {
            cout << "no corruption\n";
            return ;
        }

        lint cnt = 0;
        for (auto it: progrs)
            if (ans >= it.a && (ans - it.a) % it.r == 0 && (ans - it.a) / it.r < it.n)
                ++ cnt;
        cout << ans << ' ' << cnt << '\n';
    }
}

int main()
{
    //freopen("data.in", "r", stdin);
    //freopen("data.out", "w", stdout);
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < PRIMES; ++ i) {
        invs[i][1] = 1;
        for (int j = 2; j < primes[i]; ++ j) {
            invs[i][j] = (-(primes[i] / j) * invs[i][primes[i] % j]) % primes[i];
            if (invs[i][j] < 0)
                invs[i][j] += primes[i];
        }
    }

    stringstream ss;
    string str;
    while (1) {
        getline(cin, str);
        if (cin.eof())
            break;
        ss << str << "\n";

        lint x, y, z;
        ss >> x >> y >> z;
        if (ss.eof()) {
            process();
            progrs.clear();
            ss.clear();
        }
        else if (x <= y)
            progrs.push_back(Progr(x, z, (y - x) / z + 1));
    }
    process();
    return 0;
}
