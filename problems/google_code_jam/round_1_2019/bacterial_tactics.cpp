#include <bits/stdc++.h>

using namespace std;

//#define MOCK

int solve() {
    int N = 15, M = 15;
    #ifndef MOCK
    cin >> N >> M;
    #endif // MOCK
    vector <string> mat(N);
    #ifdef MOCK
    for (int i = 0; i < N; ++i) {
        string str;
        for (int j = 0; j < M; ++j) {
            str += '.';
            mat[i] = str;
        }
    }
    #else
    for (int i = 0; i < N; ++i) {
        cin >> mat[i];
    }
    #endif // MOCK
    // Precompute jumps
    vector <vector <int> > up(N, vector <int>(M, -1));
    vector <vector <int> > lft(N, vector <int>(M, -1));
    for (int j = 0; j < M; ++j) {
        if (mat[0][j] == '#') {
            up[0][j] = 0;
        }
    }
    for (int i = 0; i < N; ++i) {
        if (mat[i][0] == '#') {
            lft[i][0] = 0;
        }
    }
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (mat[i][j] == '#') {
                up[i][j] = i;
            } else {
                up[i][j] = up[i - 1][j];
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j < M; ++j) {
            if (mat[i][j] == '#') {
                lft[i][j] = j;
            } else {
                lft[i][j] = lft[i][j - 1];
            }
        }
    }
    vector <vector <int> > down(N, vector <int>(M, N));
    vector <vector <int> > rgt(N, vector <int>(M, M));
    for (int j = 0; j < M; ++j) {
        if (mat[N - 1][j] == '#') {
            down[N - 1][j] = N - 1;
        }
    }
    for (int i = 0; i < N; ++i) {
        if (mat[i][M - 1] == '#') {
            rgt[i][M - 1] = M - 1;
        }
    }
    for (int i = N - 2; i >= 0; --i) {
        for (int j = M - 1; j >= 0; --j) {
            if (mat[i][j] == '#') {
                down[i][j] = i;
            } else {
                down[i][j] = down[i + 1][j];
            }
        }
    }
    for (int i = N - 1; i >= 0; --i) {
        for (int j = M - 2; j >= 0; --j) {
            if (mat[i][j] == '#') {
                rgt[i][j] = j;
            } else {
                rgt[i][j] = rgt[i][j + 1];
            }
        }
    }
    // Grundy DP
    auto dp = vector <vector <vector <vector <int> > > >(N, vector <vector <vector <int> > >(N, vector <vector <int> >(M, vector <int>(M))));
    auto ask_dp = [&](const int l1, const int l2, const int c1, const int c2) {
        if (l2 < l1 || c2 < c1) {
            return 0;
        } else {
            return dp[l1][l2][c1][c2];
        }
    };
    auto compute_dp = [&](const int l1, const int l2, const int c1, const int c2) {
        vector <int> grundy;
        for (int i = l1; i <= l2; ++i) {
            for (int j = c1; j <= c2; ++j) {
                if (mat[i][j] != '#') {
                    // Place hor
                    if (lft[i][j] < c1 && rgt[i][j] > c2) {
                        grundy.push_back(ask_dp(l1, i - 1, c1, c2) ^ ask_dp(i + 1, l2, c1, c2));
                    }
                    // Place vert
                    if (up[i][j] < l1 && down[i][j] > l2) {
                        grundy.push_back(ask_dp(l1, l2, c1, j - 1) ^ ask_dp(l1, l2, j + 1, c2));
                    }
                }
            }
        }
        sort(grundy.begin(), grundy.end());
        grundy.resize(unique(grundy.begin(), grundy.end()) - grundy.begin());
        int ans = 0;
        while (ans < static_cast <int>(grundy.size()) && grundy[ans] == ans) {
            ++ans;
        }
        dp[l1][l2][c1][c2] = ans;
    };
    for (int l1 = N - 1; l1 >= 0; --l1) {
        for (int l2 = l1; l2 < N; ++l2) {
            for (int c1 = M - 1; c1 >= 0; --c1) {
                for (int c2 = c1; c2 < M; ++c2) {
                    compute_dp(l1, l2, c1, c2);
                }
            }
        }
    }
    // Count winning
    int res = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (mat[i][j] != '#') {
                // Place hor
                if (lft[i][j] < 0 && rgt[i][j] > M - 1) {
                    const int vl = ask_dp(0, i - 1, 0, M - 1) ^ ask_dp(i + 1, N - 1, 0, M - 1);
                    res += (vl == 0);
                }
                // Place vert
                if (up[i][j] < 0 && down[i][j] > N - 1) {
                    const int vl = ask_dp(0, N - 1, 0, j - 1) ^ ask_dp(0, N - 1, j + 1, M - 1);
                    res += (vl == 0);
                }
            }
        }
    }
    return res;
}

int main() {
    //freopen("data.in", "r", stdin);
    int T = 100;
    #ifndef MOCK
    cin >> T;
    #endif // MOCK
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": " << solve() << endl;
    }
    return 0;
}
