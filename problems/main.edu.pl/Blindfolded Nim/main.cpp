#include <iostream>
#include <algorithm>
#include <iomanip>
//#include <utility>

#define double long double
using namespace std;

/*double dp[21][21][21][21];
pair <pair <int, int>, pair <int, int> > father[21][21][21][21];

template <typename T>
inline void update(double &dp, double val, T &father, T fVal) {
    if (val > dp) {
        dp = val;
        father = fVal;
    }
}

void brute() {
    for (int i = 0; i <= 20; ++ i)
        for (int j = 0; j <= 20; ++ j)
            for (int k = 0; k <= 20; ++ k)
                for (int l = !(i + j + k); l <= 20; ++ l) {
                    dp[i][j][k][l] = 0;
                    for (int p = 1; p <= 20; ++ p) {
                        if (p <= i)
                            update(dp[i][j][k][l], ((i - p + 1) / (i + 1.0)) * (1 - dp[i - p][j][k][l]), father[i][j][k][l], {{i - p, j}, {k, l}});
                        if (p <= j)
                            update(dp[i][j][k][l], ((j - p + 1) / (j + 1.0)) * (1 - dp[i][j - p][k][l]), father[i][j][k][l], {{i, j - p}, {k, l}});
                        if (p <= k)
                            update(dp[i][j][k][l], ((k - p + 1) / (k + 1.0)) * (1 - dp[i][j][k - p][l]), father[i][j][k][l], {{i, j}, {k - p, l}});
                        if (p <= l)
                            update(dp[i][j][k][l], ((l - p + 1) / (l + 1.0)) * (1 - dp[i][j][k][l - p]), father[i][j][k][l], {{i, j}, {k, l - p}});
                    }
                }


    int a = 10;
    int b = 19;
    int c = 3;
    int d = 7;

    cout << dp[a][b][c][d] << '\n';

    auto fat = father[a][b][c][d];
    cout << fat.first.first << ' ' << fat.first.second << ' ';
    cout << fat.second.first << ' ' << fat.second.second << endl;
}*/

const int VALMAX = 1000000 + 5;
int freq[VALMAX];

double ans;
inline void addH(int h) {
    ans = h / (h + 1.0L) * (1 - ans);
}

int main()
{
    ios_base :: sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++ i) {
        int val;
        cin >> val;

        ++ freq[val];
    }

    for (int i = VALMAX - 1; i; -- i)
        freq[i] += freq[i + 1];


    for (int i = 1; i <= VALMAX; ++ i) {
        // Could have used Matrix Expo
        for (int j = 1; j <= freq[i]; ++ j)
            addH(i);
    }

    //brute();
    cout << fixed << setprecision(20) << ans << '\n';
    return 0;
}
