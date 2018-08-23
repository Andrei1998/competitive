#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int N;
vector <string> strs;

const int NMAX = 15;
const int INF = 1E9 + 15;
bool erased[NMAX];

bool inside(const string &a, const string &b) {
    return b.find(a) != string :: npos;
}

int overlap(const string &a, const string &b) {
    for (int i = min(a.size(), b.size()); i; -- i)
        if (a.substr(a.size() - i) == b.substr(0, i))
            return i;
    return 0;
}

int cost[NMAX][NMAX];
int dp[1 << NMAX][NMAX];
string sol[1 << NMAX][NMAX];

void test(int T) {
    cout << "Scenario #" << T << ":\n";
    cin >> N;

    strs.resize(N);
    for (int i = 0; i < N; ++ i) {
        cin >> strs[i];
        erased[i] = false;
    }

    sort(strs.begin(), strs.end());
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N && !erased[i]; ++ j)
            if (i != j && inside(strs[i], strs[j]) && !erased[j])
                erased[i] = true;

    int pos = 0;
    for (int i = 0; i < N; ++ i)
        if (!erased[i])
            strs[pos ++] = strs[i];
    N = pos;

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if (i != j)
                cost[i][j] = overlap(strs[i], strs[j]);

    for (int i = 0; i < N; ++ i) {
        dp[1 << i][i] = strs[i].size();
        sol[1 << i][i] = strs[i];
    }

    for (int i = 2; i < (1 << N); ++ i)
        if (i & (i - 1)) {
            for (int j = 0; j < N; ++ j)
                if (i & (1 << j)) {
                    dp[i][j] = INF;
                    for (int k = 0; k < N; ++ k)
                        if ((i & (1 << k)) && k != j) {
                            int cst = dp[i - (1 << j)][k] + strs[j].size() - cost[j][k];

                            if (cst <= dp[i][j]) {
                                string str = strs[j] + sol[i - (1 << j)][k].substr(cost[j][k]);
                                if (cst < dp[i][j] || str < sol[i][j])
                                    sol[i][j] = str;
                                dp[i][j] = cst;
                            }
                        }
                }
        }

    int best = INF;
    string ans;
    for (int i = 0; i < N; ++ i)
        if (dp[(1 << N) - 1][i] <= best) {
            if (dp[(1 << N) - 1][i] < best || sol[(1 << N) - 1][i] < ans)
                ans = sol[(1 << N) - 1][i];
            best = dp[(1 << N) - 1][i];
        }

    /*vector <int> sol;
    int mask = (1 << N) - 1;
    while (mask) {
        sol.push_back(who);
        int nMask = mask - (1 << who);
        mask = nMask;
    }

    for (int i = 0; i + 1 < N; ++ i) {
        int ov = cost[sol[i]][sol[i + 1]];
        cout << strs[sol[i]].substr(0, strs[sol[i]].size() - ov);
    }
    cout << strs[sol.back()] << "\n\n";*/

    cout << ans << "\n\n";
}

int main()
{
    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i)
        test(i);
    return 0;
}
