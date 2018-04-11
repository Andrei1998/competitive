#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ulint;

const ulint INF = (1ULL << 63);

ulint overflowAdd(ulint a, ulint b) {
    if (a == INF || b == INF)
        return INF;
    ulint sum = a + b;
    if (sum >= INF)
        return INF;
    else
        return sum;
}

ulint overflowMultiply(ulint a, ulint b) {
    if (a >= INF / b)
        return INF;
    else
        return a * b;
}

int prime(int nr) {
    if (nr <= 1)
        return false;
    for (int i = 2; i * i <= nr; ++ i)
        if (nr % i == 0)
            return false;
    return true;
}

int primes[15], primesCnt;
ulint primesPow[15][100];
int expos[15];

ulint comb[100][100];
map <ulint, ulint> Anss;

void backtr(int pos, ulint prod) {
    if (prod >= INF)
        return ;

    if (pos == 15) {
        int cnt = 0;
        for (int i = 0; i < 15; ++ i)
            cnt += expos[i];

        ulint multi = 1;
        for (int i = 0; i < 15; ++ i) {
            multi = overflowMultiply(multi, comb[cnt][expos[i]]);
            cnt -= expos[i];
        }

        if (!Anss.count(multi))
            Anss[multi] = prod;
        else
            Anss[multi] = min(Anss[multi], prod);
        return ;
    }

    for (int i = 0; i < 63; ++ i) {
        if (pos == 0 || i <= expos[pos - 1]) {
            expos[pos] = i;
            backtr(pos + 1, overflowMultiply(prod, primesPow[pos][i]));
        }
    }
}

ulint solve(ulint n) {
    if (n == 1)
        return 2;
    return Anss[n];
}

int main()
{
    for (int i = 1; i <= 50; ++ i)
        if (prime(i))
            primes[primesCnt ++] = i;

    for (int i = 0; i < 15; ++ i) {
        primesPow[i][0] = 1;
        for (int j = 1; j < 100; ++ j)
            primesPow[i][j] = overflowMultiply(primesPow[i][j - 1], primes[i]);
    }

    for (int i = 0; i < 100; ++ i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++ j)
            comb[i][j] = overflowAdd(comb[i - 1][j - 1], comb[i - 1][j]);
    }

    backtr(0, 1);

    ulint n;
    while (cin >> n)
        cout << n << ' ' << solve(n) << endl;
    return 0;
}
