/*
ID: andreip3
LANG: C++14
TASK: milk4
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

const int QMAX = 20000 + 5;
const int INF  = 1E6;

int Q;

const int NMAX = 100 + 5;
int N;
int v[NMAX];

int minMoves[2][QMAX];
bitset <NMAX> sol[2][QMAX];

bool cmpBit(const bitset <NMAX> &b1, const bitset <NMAX> &b2) {
    for (int i = 0; i < NMAX; ++ i)
        if (b1[i] > b2[i])
            return true;
        else if (b1[i] < b2[i])
            return false;
    return false;
}

int main() {
    ifstream cin("milk4.in");
    ofstream cout("milk4.out");

    cin >> Q >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    sort(v + 1, v + N + 1);
    N = unique(v + 1, v + N + 1) - v - 1;

    minMoves[(N + 1) & 1][Q] = 0;
    for (int i = 0; i < Q; ++ i)
        minMoves[(N + 1) & 1][i] = INF;

    for (int i = N; i; -- i)
        for (int j = 0; j <= Q; ++ j) {
            minMoves[i & 1][j] = INF;
            sol[i & 1][j].reset();
            for (int k = j + v[i]; k <= Q; k += v[i])
                if (1 + minMoves[(i + 1) & 1][k] < minMoves[i & 1][j])
                    minMoves[i & 1][j] = 1 + minMoves[(i + 1) & 1][k], sol[i & 1][j] = sol[(i + 1) & 1][k], sol[i & 1][j][i] = 1;
                else if (1 + minMoves[(i + 1) & 1][k] == minMoves[i & 1][j]) {
                    bitset <NMAX> b = sol[(i + 1) & 1][k];
                    b[i] = 1;
                    if (cmpBit(b, sol[i & 1][j]))
                        sol[i & 1][j] = sol[(i + 1) & 1][k], sol[i & 1][j][i] = 1;
                }
            if (minMoves[(i + 1) & 1][j] < minMoves[i & 1][j])
                minMoves[i & 1][j] = minMoves[(i + 1) & 1][j], sol[i & 1][j] = sol[(i + 1) & 1][j];
        }

    cout << minMoves[1][0];
    for (int i = 1; i <= N; ++ i)
        if (sol[1][0][i])
            cout << ' ' << v[i];
    cout << '\n';
    return 0;
}
