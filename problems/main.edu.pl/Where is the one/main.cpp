#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 51, 53, 57};

const int NMAX = 300000;
int mask[NMAX];

int main()
{
    int sum = 0;
    for (int i = 0; i < sizeof(primes) / sizeof(int); ++ i)
        sum += primes[i];
    cout << sum * NMAX << endl;

    int mx = 0;
    int who = 0;
    for (int N = NMAX - 700; N < NMAX - 600; ++ N) {
        memset(mask, 0, sizeof mask);
        for (int i = 0; i < sizeof(primes) / sizeof(int); ++ i)
            for (int j = 0; j < N; ++ j) {
                mask[j] *= 2;
                if (j % primes[i] <= (N - 1) % primes[i])
                    ++ mask[j];
            }

        int cnt = 0;
        for (int i = 1; i + 1 < N; ++ i)
            if (mask[i] == (1 << (sizeof(primes) / sizeof(int))) - 1)
                ++ cnt;

        if (cnt > mx) {
            mx = cnt;
            who = N;
        }
    }

    cout << mx << ' ' << who << endl;
    return 0;
}
