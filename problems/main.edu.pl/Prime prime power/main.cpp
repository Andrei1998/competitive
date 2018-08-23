#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

#define lint long long int
using namespace std;

const lint INF = 2e18;

lint raise(int a, int b) {
    if (!b)
        return 1;
    else if (b & 1) {
        lint ans = raise(a, b - 1);
        if (ans <= INF / a)
            ans *= a;
        else
            ans = INF;
        return ans;
    }
    else {
        lint ans = raise(a, b >> 1);
        if (ans <= INF / ans)
            ans *= ans;
        else
            ans = INF;
        return ans;
    }
}

const int VALMAX = 2.5e6;
bool prime[VALMAX + 5];

vector <int> primes;

void sieve() {
    for (int i = 2; i <= VALMAX; ++ i)
        prime[i] = true;
    for (int i = 2; i * i <= VALMAX; ++ i)
        if (prime[i])
            for (int j = i * i; j <= VALMAX; j += i)
                prime[j] = false;

    for (int i = 2; i <= VALMAX; ++ i)
        if (prime[i])
            primes.push_back(i);
}

const int C[] = {2, 9332593};

int raiseMOD(int a, int b, int MOD) {
    if (!b)
        return 1;
    else if (b & 1)
        return (1LL * a * raiseMOD(a, b - 1, MOD)) % MOD;
    else {
        int aux = raiseMOD(a, b >> 1, MOD);
        return (1LL * aux * aux) % MOD;
    }
}

bool probablyPrime(int p, int a, int &s, int &d) {
    if (__gcd(a, p) != 1)
        return false;

    int val = raiseMOD(a, d, p);
    if (val == 1)
        return true;

    for (int i = 0; i < s; ++ i) {
        if (val == p - 1)
            return true;
        val = (1LL * val * val) % p;
    }

    return false;
}

lint N;
int extraSieve[VALMAX + 5]; //Sieve for interval [extraSieveDisplacement, extraSieveDisplacement + VALMAX - 1]
int extraSieveDisplacement;

void computeExtraSieve() {
    for (int i = 1; i <= VALMAX; ++ i)
        if (prime[i]) {
            for (int j = i * ((extraSieveDisplacement + i - 1) / i); j < extraSieveDisplacement + VALMAX; j += i)
                extraSieve[j - extraSieveDisplacement] = true;
        }
}

bool isPrime(int nr) {
    if (nr <= VALMAX)
        return prime[nr];
    else
        return !extraSieve[nr - extraSieveDisplacement];

    //Rabin-Miller
    /*int s = 0;
    int d = nr - 1;
    while (d % 2 == 0) {
        d /= 2;
        ++ s;
    }
    for (int i = 0; i < sizeof(C) / sizeof(int); ++ i)
        if (!probablyPrime(nr, C[i], s, d))
            return false;
    return true;*/

    //Trial division
    /*for (int i = 0; i < primes.size() && primes[i] * primes[i] <= nr; ++ i)
        if (nr % primes[i] == 0)
            return false;
    return true;*/
}

const int EXPOSSZMAX = 20;
int expos[EXPOSSZMAX];
int exposSz;

int cursors[EXPOSSZMAX];

void advanceCursorCheck(int cursor) {
    do {
        ++ cursors[cursor];
    } while (!isPrime(cursors[cursor]) || raise(cursors[cursor], expos[cursor]) < N);
}

void advanceCursor(int cursor) {
    do {
        ++ cursors[cursor];
    } while (!isPrime(cursors[cursor]));
}

priority_queue <pair <lint, int> > pq;

int main()
{
    sieve();

    int k;
    cin >> N;
    cin >> k;

    //N = 1000000000000000000LL;
    //k = 100000;

    ++ N;

    for (int i = 0; i < primes.size() && primes[i] < 64; ++ i) {
        expos[++ exposSz] = primes[i];
        cursors[exposSz] = max(1, (int)pow(N, 1.0 / expos[exposSz]) - 10);
    }

    extraSieveDisplacement = cursors[1];
    computeExtraSieve();

    for (int i = 1; i <= exposSz; ++ i) {
        advanceCursorCheck(i);
        pq.push(make_pair(-raise(cursors[i], expos[i]), i));
    }


    int who;
    lint val;
    for (int i = 1; i <= k; ++ i) {
        val = -pq.top().first;
        who = pq.top().second;
        pq.pop();

        advanceCursor(who);
        pq.push(make_pair(-raise(cursors[who], expos[who]), who));
    }

    cout << val << '\n';
    return 0;
}
