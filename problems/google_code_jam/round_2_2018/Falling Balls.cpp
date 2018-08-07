#include <bits/stdc++.h>

using namespace std;

const int CMAX = 100 + 5;

int C;
int v[CMAX];
int now[CMAX], dest[CMAX];

vector <string> solve() {
    cin >> C;
    for (int i = 1; i <= C; ++ i) {
        cin >> v[i];
        now[i] = i;
    }
    int cnt = 0;
    for (int i = 1; i <= C; ++ i)
        for (int j = 1; j <= v[i]; ++ j)
            dest[++ cnt] = i;

    vector <string> sol;
    if (cnt != C || dest[1] != 1 || dest[C] != C)
        return sol;

    string def;
    for (int i = 1; i <= C; ++ i)
        def += ".";

    while (1) {
        string str = def;
        bool moved = false;
        for (int i = 1; i <= C; ++ i)
            if (dest[i] < now[i]) {
                moved = true;
                str[now[i] - 1] = '/';
                now[i] --;
            }
            else if (dest[i] > now[i]) {
                moved = true;
                str[now[i] - 1] = '\\';
                now[i] ++;
            }
        if (!moved)
            break;
        else
            sol.push_back(str);
    }
    sol.push_back(def);
    return sol;
}

int main() {
    //freopen("data.in", "r", stdin);

    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i) {
        vector <string> str = solve();
        cout << "Case #" << i << ": ";
        if (str.empty())
            cout << "IMPOSSIBLE\n";
        else
            cout << str.size() << '\n';
        for (const auto &it: str)
            cout << it << '\n';
    }
    return 0;
}
