#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100000 + 5;

int N, K;
int frst[NMAX];

/*bool win[100][100]; // win[N][K] = start with (N, K)
bool brute() {
    memset(frst, -1, sizeof frst);
    for (int n = 1; n <= N; ++ n) {
        for (int k = 1; k <= K; ++ k) {
            for (int l = 1; l <= k && l <= n; ++ l) {
                if (!win[n - l][l]) {
                    win[n][k] = true;
                    if (frst[n] == -1)
                        frst[n] = k;
                }
            }
        }
    }
}*/

int main() {
    /*N = 100, K = 100;
    brute();
    for (int i = 0; i < 100; ++ i)
        cout << i << ' ' << frst[i] << ' ' << (i & (-i)) << endl;
    for (int i = 1; i <= 40; ++ i) {
        for (int j = 1; j <= 40; ++ j)
            cout << win[i][j] << ' ';
        cout << endl;
    }*/


    cin >> N >> K;
    for (int i = 1; i <= N; ++ i)
        frst[i] = i & (-i);

    if (K < frst[N]) {
        cout << "FAIL\n";
    }
    else {
        cout << "WIN\n";
        if (K == N) {
            cout << N << endl;
            return 0;
        }
        for (int i = 1; i <= K; ++ i) {
            if (i < frst[N - i]) {
                cout << i << endl;
                return 0;
            }
        }
    }
    return 0;
}
