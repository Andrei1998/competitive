#include "cgdzlib.h"
#include <vector>
#include <iostream>

using namespace std;

pair <int, int> solve(int val, const vector <int> &v) {
    if (v.size() == 1)
        return make_pair(v[0], v[0]);
    vector <int> vAux[2];

    vAux[0].push_back(v[0]);
    for (int i = 1; i < v.size(); ++ i)
        vAux[!f(v[0], v[i], val)].push_back(v[i]);

    if (vAux[0].size() > vAux[1].size() || vAux[1].size() == 0)
        return solve(2 * val, vAux[0]);
    else if (vAux[0].size() < vAux[1].size() || vAux[0].size() == 0)
        return solve(2 * val, vAux[1]);
    else {
        pair <int, int> ans[2];
        for (int i = 0; i < 2; ++ i)
            ans[i] = solve(2 * val, vAux[i]);

        if (f(ans[0].first, ans[1].first, val / 2 * (v.size() - 1)))
            return make_pair(ans[0].first, ans[1].first);
        if (f(ans[0].second, ans[1].first, val / 2 * (v.size() - 1)))
            return make_pair(ans[0].second, ans[1].first);
        if (f(ans[0].first, ans[1].second, val / 2 * (v.size() - 1)))
            return make_pair(ans[0].first, ans[1].second);
        if (f(ans[0].second, ans[1].second, val / 2 * (v.size() - 1)))
            return make_pair(ans[0].second, ans[1].second);
    }

}

int main() {
    int N = inicjuj();
    if (N == 1)
        odpowiedz(1);

    vector <int> v(N);
    for (int i = 0; i < N; ++ i)
        v[i] = i + 1;

    pair <int, int> ans = solve(2, v);

    if (!g(ans.first, ans.second))
        odpowiedz(ans.first);
    else
        odpowiedz(ans.second);
    return 1;
}
