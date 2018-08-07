#include <iostream>

//21:56
using namespace std;

const int MOD = 1000000000 - 401;

int raise(int a, int b) {
    if (!b)
        return 1;
    else if (b & 1)
        return (1LL * a * raise(a, b - 1)) % MOD;
    else {
        int aux = raise(a, b >> 1);
        return (1LL * aux * aux) % MOD;
    }
}

const int NMAX = 200000 + 5;

int part[NMAX];

int pentagonals[NMAX];
int pentagonalsSz;

int main()
{
    int N, M;
    cin >> N >> M;

    N = 200000;

    for (int k = 1; ; ++ k) {
        pentagonals[pentagonalsSz ++] = k * (3 * k - 1) / 2;
        if (pentagonals[pentagonalsSz - 1] > N) {
            -- pentagonalsSz;
            break;
        }
        pentagonals[pentagonalsSz ++] = k * (3 * k + 1) / 2;
        if (pentagonals[pentagonalsSz - 1] > N) {
            -- pentagonalsSz;
            break;
        }
    }

    part[0] = 1;
    part[1] = 1;

    for (int i = 2; i <= N; ++ i) {
        for (int j = 0; j < pentagonalsSz; ++ j) {
            if (pentagonals[j] > i)
                break;

            if (j % 4 < 2) {
                part[i] += part[i - pentagonals[j]];
                if (part[i] >= MOD - 1)
                    part[i] -= (MOD - 1);
            }
            else {
                part[i] -= part[i - pentagonals[j]];
                if (part[i] < 0)
                    part[i] += (MOD - 1);
            }
        }
    }

    cout << raise(M, part[N]) << '\n';
    return 0;
}
