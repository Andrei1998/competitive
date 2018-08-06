/*
ID: andreip3
LANG: C++14
TASK: frameup
*/

#include <bits/stdc++.h>

using namespace std;

const int NMAX = 30 + 5;

int N, M;
string mat[NMAX];

int cnt;
int l1[NMAX], c1[NMAX], l2[NMAX], c2[NMAX];
bool found[NMAX];

static inline bool onEdge(int l, int c, int col) {
    return   l1[col] <= l && l <= l2[col] && c1[col] <= c && c <= c2[col] &&
           !(l1[col] + 1 <= l && l <= l2[col] - 1 && c1[col] + 1 <= c && c <= c2[col] - 1);
}

set <int> graph[NMAX];
int inDeg[NMAX];

int sigma;
string str;

set <int> S;

void backtr() {
    if (!sigma) {
        cout << str << '\n';
        return ;
    }

    vector <int> copyS(S.begin(), S.end());
    for (auto node: copyS) {
        str += (char)(node + 'A');
        S.erase(node);
        for (auto it: graph[node]) {
            -- inDeg[it];
            if (!inDeg[it])
                S.insert(it);
        }

        -- sigma;
        backtr();
        ++ sigma;

        for (auto it: graph[node]) {
            ++ inDeg[it];
            if (inDeg[it] == 1)
                S.erase(it);
        }
        S.insert(node);
        str.pop_back();
    }
}

int main()
{
    freopen("frameup.in", "r", stdin);
    freopen("frameup.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < N; ++ i)
        cin >> mat[i];

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            if (mat[i][j] != '.') {
                const int ch = mat[i][j] - 'A';
                if (!found[ch])
                    l1[ch] = l2[ch] = i, c1[ch] = c2[ch] = j, found[ch] = true, ++ sigma;
                else {
                    l1[ch] = min(l1[ch], i);
                    l2[ch] = max(l2[ch], i);
                    c1[ch] = min(c1[ch], j);
                    c2[ch] = max(c2[ch], j);
                }
            }

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            if (mat[i][j] != '.')
                for (int k = 0; k < 26; ++ k)
                    if (found[k] && k != mat[i][j] - 'A' && onEdge(i, j, k))
                        graph[k].insert(mat[i][j] - 'A');
    for (int i = 0; i < 26; ++ i)
        for (auto it: graph[i])
            ++ inDeg[it];
    for (int i = 0; i < 26; ++ i)
        if (found[i] && !inDeg[i])
            S.insert(i);
    backtr();
    return 0;
}
