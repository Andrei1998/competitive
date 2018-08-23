#include <iostream>
#include <cstring>

#define lint long long int
using namespace std;

const int DIGITS = 6000;
const int BASE = 1000000000;

struct BigInteger {
    int v[DIGITS];

    BigInteger(int c = 0) {
        memset(v, 0, sizeof v);
        v[0] = 1;
        v[1] = c;
    }

    friend BigInteger operator*(const BigInteger &a, int b) {
        BigInteger res;
        res.v[0] = a.v[0];

        lint tr = 0;
        for (int i = 1; i <= res.v[0]; ++ i) {
            tr += 1LL * a.v[i] * b;
            res.v[i] = tr % BASE;
            tr /= BASE;
        }

        while (tr) {
            res.v[++ res.v[0]] = tr % BASE;
            tr /= BASE;
        }

        return res;
    }
};

ostream& operator<<(ostream &g, const BigInteger &nr) {
    for (int i = nr.v[0]; i; -- i) {
        if (i < nr.v[0]) {
            if (nr.v[i] / 10 == 0)
                g << '0';
            if (nr.v[i] / 100 == 0)
                g << '0';
            if (nr.v[i] / 1000 == 0)
                g << '0';
            if (nr.v[i] / 10000 == 0)
                g << '0';
            if (nr.v[i] / 100000 == 0)
                g << '0';
            if (nr.v[i] / 1000000 == 0)
                g << '0';
            if (nr.v[i] / 10000000 == 0)
                g << '0';
            if (nr.v[i] / 100000000 == 0)
                g << '0';
        }
        g << nr.v[i];
    }
    return g;
}

int main()
{
    int n;
    cin >> n;
    if (n & 1)
        -- n;

    if (n % 4 == 2) {
        cout << "0\n";
        return 0;
    }

    BigInteger ans = 1;
    for (int i = n - 2; i >= 0; i -= 4)
        ans = ans * i;
    cout << ans << '\n';
    return 0;
}
