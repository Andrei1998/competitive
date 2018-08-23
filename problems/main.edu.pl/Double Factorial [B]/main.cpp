#include <iostream>
#include <algorithm>
#include <cstring>

#define lint long long int
using namespace std;

const int DIGITS = 40;

class BigInteger {
public:
    int v[DIGITS];

    BigInteger(lint c = 0) {
        memset(v, 0, sizeof v);
        do  {
            v[++ v[0]] = c % 10;
            c /= 10;
        } while (c);
    }

    friend BigInteger operator+(const BigInteger &a, const BigInteger &b) {
        BigInteger ans;
        ans.v[0] = max(a.v[0], b.v[0]);

        int tr = 0;
        for (int i = 1; i <= ans.v[0]; ++ i) {
            ans.v[i] = a.v[i] + b.v[i] + tr;
            if (ans.v[i] >= 10) {
                ans.v[i] -= 10;
                tr = 1;
            }
            else
                tr = 0;
        }
        if (tr)
            ans.v[++ ans.v[0]] = tr;

        return ans;
    }

    friend BigInteger operator*(const BigInteger &a, const BigInteger &b) {
        BigInteger ans;
        ans.v[0] = a.v[0] + b.v[0] - 1;

        for (int i = 1; i <= a.v[0]; ++ i)
            for (int j = 1; j <= b.v[0]; ++ j)
                ans.v[i + j - 1] += a.v[i] * b.v[j];

        int tr = 0;
        for (int i = 1; i <= ans.v[0]; ++ i) {
            ans.v[i] += tr;
            tr = ans.v[i] / 10;
            ans.v[i] %= 10;
        }

        while (tr) {
            ans.v[++ ans.v[0]] = tr;
            tr = ans.v[ans.v[0]] / 10;
            ans.v[ans.v[0]] %= 10;
        }

        return ans;
    }
};

ostream &operator<<(ostream &g, const BigInteger &nr) {
    for (int i = nr.v[0]; i; -- i)
        g << nr.v[i];
    return g;
}

int main()
{
    lint N;
    cin >> N;

    BigInteger ans = 0;
    lint p = 5;
    while (p <= N) {
        lint groups = N / p;

        if (groups % 2 == 0)
            ans = ans + BigInteger(groups / 2) * (groups - 1LL) * p;
        else
            ans = ans + BigInteger((groups - 1) / 2) * groups * p;
        ans = ans + BigInteger(N - p * groups + 1) * groups;
        p *= 5;
    }

    cout << ans << '\n';
    return 0;
}
