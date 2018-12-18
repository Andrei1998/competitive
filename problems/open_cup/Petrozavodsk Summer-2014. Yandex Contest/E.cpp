#include <bits/stdc++.h>

using namespace std;

const int MMAX = 10000 + 5;

int N, M;
vector <int> stud[MMAX];

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; ++ i) {
        stud[i].resize(N);
        for (int j = 0; j < N; ++ j)
            cin >> stud[i][j];
        if (i > 1 && stud[i] == stud[1]) {
            cout << "-1\n";
            return 0;
        }
    }

    vector <vector <int> > ans;
    for (int mask = 0; mask < (1 << N); ++ mask) {
        int weight = 10;
        ans.push_back(vector <int>());
        bool ok = true;
        for (int i = N - 1; i >= 0 && ok; -- i) {
            int c = stud[1][i];
            if (mask & (1 << i)) {
                weight *= (-1);
                -- c;
            }
            if (c <= 0)
                ok = false;
            ans.back().push_back(c);
        }
        if (ok) {
            ans.back().push_back(weight);
            reverse(ans.back().begin(), ans.back().end());
        }
        else
            ans.pop_back();
    }

    cout << ans.size() << endl;
    for (const auto &it: ans)
        for (int i = 0; i <= N; ++ i)
            cout << it[i] << " \n"[i == N];
    return 0;
}
