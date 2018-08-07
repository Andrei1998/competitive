#include <iostream>
#include <string>
#include <cstdlib>

//20:06
using namespace std;

const int NMAX = 75;
const int INF = NMAX * NMAX * NMAX * NMAX;

int N;
string str;

int cost[NMAX][NMAX];

int separators[NMAX];
int sz;

int dp[NMAX][NMAX]; // dp[i][j] = imparti 1 ... i folosind primii j separatori

int main()
{
    //cin >> N;
    //cin >> str;

    N = 20;
    str = "VKVKVVVKVOVKVQKKKVVK";

    string str2 = " ";
    for (int i = 0; i < N; ++ i)
        if (str[i] == 'V')
            str2 += "V";
        else if (str[i] == 'K')
            str2 += "K";
        else
            separators[++ sz] = str2.size() - 1;
    str = str2;
    N = str.size() - 1;

    cout << "am N = " << N << endl;
    for (int i = 1; i <= sz; ++ i)
        cout << i << ' ' << separators[i] << endl;

    for (int start = 1; start <= N; ++ start) {
        int v = 0;
        for (int j = start; j <= N; ++ j) {
            cost[start][j] = cost[start][j - 1];
            if (str[j] == 'V')
                ++ v;
            else
                cost[start][j] += v;
        }
    }

    int minimum = INF;
    for (int i = 1; i <= 18; ++ i)
        for (int j = i + 1; j + 1 <= 18; ++ j) {
            int cst = cost[1][i] + cost[i + 1][j] + cost[j + 1][18];
            cst += abs(separators[1] - i) + abs(separators[2] - j);
            if (cst < minimum)
                minimum = cst;
        }
    cout << "deci " << minimum << endl;

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= sz; ++ j)
            dp[i][j] = INF;
    for (int i = 0; i <= N; ++ i)
        dp[i][0] = cost[1][i];
    for (int i = 0; i <= sz; ++ i)
        dp[0][i] = 0;

    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= sz; ++ j)
            for (int k = 0; k < i; ++ k)
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + abs(separators[j] - k) + cost[k + 1][i]);
    cout << dp[N][sz] << '\n';
    return 0;
}
