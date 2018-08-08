#include <bits/stdc++.h>

// 22:43
using namespace std;

typedef long long int lint;

const int NMAX = 2000 + 5;
const int MOD = 998244353;

inline void add(int &where, const int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}

int N, M;
int a[NMAX], b[NMAX];
int vl[NMAX][2];

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
    ios_base :: sync_with_stdio(false);
#endif
    cin >> N >> M;
    for (int i = 1; i <= N; ++ i)
        cin >> a[i];
    for (int i = 1; i <= M; ++ i)
        cin >> b[i];

    int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        const int val = a[i];
        int sumSmaller = 0, sumLarger = 0;
        for (int j = 1; j <= M; ++ j) {
            if (b[j] == val) {
                int dp_i_j_0 = sumSmaller, dp_i_j_1 = sumLarger;
                add(dp_i_j_1, 1);
                add(ans, dp_i_j_0), add(ans, dp_i_j_1);
                add(vl[j][0], dp_i_j_0), add(vl[j][1], dp_i_j_1);
            }
            else if (b[j] < val)
                add(sumSmaller, vl[j][1]);
            else
                add(sumLarger, vl[j][0]);
        }
    }
    cout << ans << endl;
    return 0;
}
