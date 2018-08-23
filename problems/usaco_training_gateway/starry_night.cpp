/*
ID: andreip3
LANG: C++14
TASK: starry
*/
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100 + 5;

int N, M;
string mat[NMAX];

typedef unsigned long long int lint;
lint weights[NMAX][NMAX];

lint getCode(vector <pair <int, int> > v) {
    pair <int, int> minV = v[0];
    for (auto it: v)
        minV = {min(minV.first, it.first), min(minV.second, it.second)};
    for (auto &it: v)
        it.first -= minV.first, it.second -= minV.second;
    pair <int, int> maxV = v[0];
    for (auto it: v)
        maxV = {max(maxV.first, it.first), max(maxV.second, it.second)};
    const int n = maxV.first, m = maxV.second;
    lint h[8] = {0};
    for (auto it: v) {
        const int l = it.first, c = it.second;
        h[0] += weights[l][c];
        h[1] += weights[n - l][c];
        h[2] += weights[l][m - c];
        h[3] += weights[n - l][m - c];
        h[4] += weights[c][l];
        h[5] += weights[c][n - l];
        h[6] += weights[m - c][l];
        h[7] += weights[m - c][n - l];
    }
    return *min_element(h, h + 8);
}

map <lint, char> chr;

vector <pair <int, int> > v;
void fill(int l, int c) {
    if (l < 0 || l >= N || c < 0 || c >= M || mat[l][c] != '1')
        return ;
    mat[l][c] = '0';
    v.push_back(make_pair(l, c));
    fill(l - 1, c),     fill(l + 1, c),     fill(l, c - 1),     fill(l, c + 1);
    fill(l - 1, c - 1), fill(l + 1, c - 1), fill(l - 1, c + 1), fill(l + 1, c + 1);
}

int main() {
    freopen("starry.in", "r", stdin);
    freopen("starry.out", "w", stdout);

    cin >> M >> N;
    for (int i = 0; i < N; ++ i)
        cin >> mat[i];
    for (int i = 0; i < max(N, M); ++ i)
        for (int j = 0; j < max(N, M); ++ j)
            weights[i][j] = (((1LL * rand()) << 31) + rand());

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            if (mat[i][j] == '1') {
                v.clear();
                fill(i, j);
                lint c = getCode(v);
                if (!chr.count(c))
                    chr[c] = 'a' + chr.size() - 1;
                for (auto it: v)
                    mat[it.first][it.second] = chr[c];
            }

    for (int i = 0; i < N; ++ i)
        cout << mat[i] << '\n';
    return 0;
}
