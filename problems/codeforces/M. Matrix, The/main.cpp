#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, A, B;

void printMask(int mask) {
    string str;
    for (int i = 0; i < N; ++ i) {
        if (mask % 3 == 2)
            str += '1';
        else
            str += '0';
        mask /= 3;
    }
    reverse(str.begin(), str.end());
    cout << str << '\n';
}

vector <int> trans[59049 + 5];

//00122
//02121

int cnt;
void backtr(int pos, int mask1, int mask2) {
    if (pos == N) {
        trans[mask1].push_back(mask2);
        ++ cnt;
        return ;
    }

    mask1 *= 3, mask2 *= 3;
    backtr(pos + 1, mask1,     mask2);
    backtr(pos + 1, mask1,     mask2 + 2);
    backtr(pos + 1, mask1 + 1, mask2 + 1);
    backtr(pos + 1, mask1 + 2, mask2 + 2);
    backtr(pos + 1, mask1 + 2, mask2 + 1);
}

int popcount[3 * 59049 + 5];

typedef long long int lint;
const lint INF = 2E18 + 1555;

lint dp[12][59049 + 5];

int main()
{
    //freopen("data.in", "r", stdin);
    cin >> N >> A >> B;

    /*N = 10;
    A = 0;
    B = 10;
    */backtr(0, 0, 0);

    int put3 = 1;
    for (int i = 1; i <= N; ++ i)
        put3 *= 3;

    for (int i = 0; i < put3; ++ i) {
        popcount[3 * i] = popcount[i];
        popcount[3 * i + 1] = popcount[i];
        popcount[3 * i + 2] = popcount[i] + 1;
    }

    for (int i = 0; i < put3; ++ i)
        sort(trans[i].begin(), trans[i].end());

    dp[0][(put3 - 1) / 2] = 1;
    for (int lin = 1; lin <= N + 1; ++ lin)
        for (int mask = 0; mask < put3; ++ mask)
            if (lin == N + 1 || (A <= popcount[mask] && popcount[mask] <= B)) {
                for (auto it: trans[mask]) {
                    dp[lin][mask] += dp[lin - 1][it];
                    if (dp[lin][mask] >= INF)
                        dp[lin][mask] = INF;
                }
            }

    int Q = 0;
    cin >> Q;

    while (Q --) {
        lint T;
        cin >> T;

        if (T > dp[N + 1][0]) {
            cout << "No such matrix.\n";
            continue;
        }

        int mask = 0;
        for (int rem = N; rem; rem --) {
            for (auto it: trans[mask])
                if (dp[rem][it] < T) {
                    T -= dp[rem][it];
                }
                else {
                    mask = it;
                    break;
                }
            printMask(mask);
        }

        if (Q)
            cout << '\n';
    }
    return 0;
}
