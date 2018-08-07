#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>

#define lint long long int
using namespace std;

vector <pair <int, int> > states;

int MOD;

void add(int &where, int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
    else if (where < 0)
        where += MOD;
}

const int PMAX = 345 + 5;

int P;
int q[PMAX];
int a[PMAX], da[PMAX];
int b[PMAX], db[PMAX];
int c[PMAX], dc[PMAX];
int d[PMAX], dd[PMAX];

bool x[PMAX][PMAX];

const int LAT = 2500 + 5;

int startLin, startCol;
int sPart[LAT][LAT];

void load() {
    memset(sPart, 0, sizeof sPart);

    for (auto it: states)
        if (startLin <= it.first && it.first < startLin + LAT &&
            startCol <= it.second && it.second < startCol + LAT)
                ++ sPart[it.first - startLin][it.second - startCol];

    for (int i = 0; i < LAT; ++ i)
        for (int j = 0; j < LAT; ++ j) {
            if (j > 0)
                sPart[i][j] += sPart[i][j - 1];
            if (i > 0)
                sPart[i][j] += sPart[i - 1][j];
            if (i > 0 && j > 0)
                sPart[i][j] -= sPart[i - 1][j - 1];
        }
}

inline int query(int l1, int c1, int l2, int c2) {
    l1 -= startLin;
    c1 -= startCol;
    l2 -= startLin;
    c2 -= startCol;

    if (l1 < 0)
        l1 = 0;
    if (l1 >= LAT)
        return 0;
    if (c1 < 0)
        c1 = 0;
    if (c1 >= LAT)
        return 0;

    if (l2 >= LAT)
        l2 = LAT - 1;
    if (l2 < 0)
        return 0;
    if (c2 >= LAT)
        c2 = LAT - 1;
    if (c2 < 0)
        return 0;

    int ans = sPart[l2][c2];
    if (c1 > 0)
        ans -= sPart[l2][c1 - 1];
    if (l1 > 0)
        ans -= sPart[l1 - 1][c2];
    if (c1 > 0 && l1 > 0)
        ans += sPart[l1 - 1][c1 - 1];
    return ans;
}

int main()
{
    ios_base :: sync_with_stdio(false);

    int M = 0;
    cin >> MOD >> M;

    for (int i = 0; i < M; ++ i) {
        int s, t, ds, dt, k;
        cin >> s >> t >> ds >> dt >> k;

        for (int j = 0; j < k; ++ j, add(s, ds), add(t, dt))
            states.push_back({s, t});
    }

    cin >> P;
    for (int i = 0; i < P; ++ i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        cin >> da[i] >> db[i] >> dc[i] >> dd[i];
        cin >> q[i];
    }

    for (startLin = 0; startLin < MOD; startLin += LAT)
        for (startCol = 0; startCol < MOD; startCol += LAT) {
            load();
            for (int i = 0; i < P; ++ i) {
                int A = a[i];
                int B = b[i];
                int C = c[i];
                int D = d[i];

                for (int j = 0; j < q[i]; ++ j, add(A, da[i]), add(B, db[i]), add(C, dc[i]), add(D, dd[i]))
                    if (!x[i][j])
                        x[i][j] = query(min(A, B), min(C, D), max(A, B), max(C, D));
            }
        }

    const lint MOD2 = 200904040930LL + 33;
    for (int i = 0; i < P; ++ i) {
        if (q[i] <= 20) {
            for (int j = 0; j < q[i]; ++ j)
                cout << x[i][j];
        }
        else {
            lint ans = 0;
            for (int j = q[i] - 1; j >= 0; -- j)
                ans = (7LL * ans + x[i][j]) % MOD2;
            cout << ans;
        }
        cout << '\n';

    }
    return 0;
}
