#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100000 + 5;

int N;
int v[NMAX];
int where[NMAX];

void fix(vector<int>& v) {
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}

void augment(vector<int> &v) {
    vector<bool> exists(N + 1, false);
    for (int i = 0; i < v.size(); ++i) {
        exists[v[i]] = true;
    }
    int x = N;
    while (v.size() < N / 2) {
        while (exists[x] && x > 0) {
            --x;
        }
        assert(x > 0);
        v.push_back(x);
        exists[x] = true;
    }
    fix(v);
    assert(v.size() == N / 2);
}

vector<vector<int>> sol;
void do_once(int a, int b) {
    for (int i = 1; i <= N; ++i) {
        where[v[i]] = i;
    }
    vector<int> who;
    for (int i = a; i <= b; ++i) {
        who.push_back(i);
        who.push_back(where[i]);
    }
    fix(who);
    augment(who);

    // Execute.
    vector<int> vals;
    assert(who.size() == N / 2);
    for (int i = 0; i < who.size(); ++i) {
        vals.push_back(v[who[i]]);
    }
    sort(vals.begin(), vals.end());
    for (int i = 0; i < who.size(); ++i) {
        v[who[i]] = vals[i];
    }
    sol.push_back(who);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> v[i];
    }

    do_once(1, N / 4);
    do_once(N / 4 + 1, N / 2);
    do_once(N / 2 + 1, N);

    for (int i = 1; i <= N; ++i) {
        assert(v[i] == i);
    }

    cout << sol.size() << endl;
    for (int i = 0; i < sol.size(); ++i) {
        assert(sol[i].size() == N / 2);
        for (int j = 0; j < sol[i].size(); ++j) {
            cout << sol[i][j] << " \n"[j + 1 == sol[i].size()];
        }
    }
    return 0;
}