#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int NMAX = 100000 + 5;
const int VALMAX = 100 + 5;

int N, M;
int v[NMAX];
int pattern[NMAX];
int where[NMAX], cnt;
int nxt[NMAX][VALMAX];
int prv[NMAX];

inline bool moveLeft(int pos) {
    bool did = false;
    while (prv[where[pos]] > where[pos - 1]) {
        did = true;
        where[pos] = prv[where[pos]];
    }
    return did;
}

inline bool extend() {
    if (cnt == M) {
        return false;
    }
    else {
        if (nxt[where[cnt] + 1][pattern[cnt + 1]] <= N) {
            where[cnt + 1] = nxt[where[cnt] + 1][pattern[cnt + 1]];
            ++cnt;
            return true;
        }
        else {
            return false;
        }
    }
}

long long conta(int _N, int _v[], int _M, int _pattern[]) {
    // Initialization
    N = _N, M = _M;
    for (int i = 1; i <= N; ++i)
        v[i] = _v[i - 1];
    for (int i = 1; i <= M; ++i)
        pattern[i] = _pattern[i - 1];

    // Precompute nxt
    int lst[VALMAX];
    for (int j = 0; j < VALMAX; ++j)
        nxt[N + 1][j] = N + 1, lst[j] = 0;
    for (int i = 1; i <= N; ++i) {
        prv[i] = lst[v[i]];
        lst[v[i]] = i;
    }
    for (int i = N; i; --i) {
        for (int j = 0; j < VALMAX; ++j)
            nxt[i][j] = nxt[i + 1][j];
        nxt[i][v[i]] = i;
    }

    lint ans = 0;
    for (int i = N; i; --i) {
        where[0] = i - 1;
        for (int pos = 1; pos <= cnt; ++pos) {
            // Try moving position pos further to the left
            if (!moveLeft(pos))
                break;
        }

        // Try extending the solution
        while (extend());

        // Count answer
        if (cnt == M)
            ans += N - where[M] + 1;
    }

    return ans;
}
