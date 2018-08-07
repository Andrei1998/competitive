#include "rainbow.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int NMAX = 200000 + 5;

int N, M, L, Q;
int sr, sc;
string str;

// Subtask 2
bool matt[3][NMAX];
int comps[3][NMAX];
int comps2[NMAX];

// Subtask 4
int mat[1005][1005];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int label[1005][1005];
pair <int, int> rep[1005 * 1005];
bool used[1005 * 1005];
int sPart[1005][1005];

void dfs(int l, int c, int b1, int b2, int b3, int b4, int cmp) {
    label[l][c] = cmp;
    for (int i = 0; i < 4; ++ i) {
        int nl = l + dx[i];
        int nc = c + dy[i];
        if (nl >= b1 && nl <= b2 && nc >= b3 && nc <= b4 && !label[nl][nc] && !mat[nl][nc])
            dfs(nl, nc, b1, b2, b3, b4, cmp);
    }
}

void init(int R, int C, int _sr, int _sc, int _M, char *S) {
    N = R;
    M = C;
    sr = _sr;
    sc = _sc;
    L = _M;
    str = string(S);

    if (N == 2) {
        matt[sr][sc] = 1;

        int lin = sr, col = sc;
        for (auto it: str) {
            if (it == 'N')
                lin --;
            else if (it == 'S')
                lin ++;
            else if (it == 'W')
                col --;
            else
                col ++;
            matt[lin][col] = 1;
        }

        matt[1][0] = matt[1][M + 1];
        matt[2][0] = matt[2][M + 1];
        for (int i = 1; i <= 2; ++ i)
            for (int j = 1; j <= M; ++ j)
                if (matt[i][j] == 1)
                    comps[i][j] = comps[i][j - 1];
                else if (matt[i][j - 1] == 0)
                    comps[i][j] = comps[i][j - 1];
                else
                    comps[i][j] = comps[i][j - 1] + 1;

        for (int j = 1; j <= M; ++ j) {
            if (matt[1][j] == 1 && matt[2][j] ==1)
                comps2[j] = comps2[j - 1];
            else if (matt[1][j] == 1 && matt[2][j] == 0) {
                if (matt[2][j - 1] == 1)
                    comps2[j] = 1 + comps2[j - 1];
                else
                    comps2[j] = comps2[j - 1];
            }
            else if (matt[1][j] == 0 && matt[2][j] == 1) {
                if (matt[1][j - 1] == 1)
                    comps2[j] = 1 + comps2[j - 1];
                else
                    comps2[j] = comps2[j - 1];
            }
            else {
                if (matt[1][j - 1] == 0 || matt[2][j - 1] == 0)
                    comps2[j] = comps2[j - 1];
                else
                    comps2[j] = 1 + comps2[j - 1];
            }
        }
    }
    else if (N <= 1000 && M <= 1000) {
        mat[sr][sc] = 1;

        int lin = sr, col = sc;
        for (auto it: str) {
            if (it == 'N')
                lin --;
            else if (it == 'S')
                lin ++;
            else if (it == 'W')
                col --;
            else
                col ++;
            mat[lin][col] = 1;
        }
    }
}

vector <int> blocks[NMAX];

map <pair <int, pair <int, int> >, int> Map;

vector <int> graph[4 * NMAX];

bool viss[4 * NMAX];

void dfss(int node) {
    viss[node] = true;
    for (auto it: graph[node])
        if (!viss[it])
            dfss(it);
}

int colour(int ar, int ac, int br, int bc) {
    int l1 = ar, l2 = br, c1 = ac, c2 = bc;

    int ans = 0;
    if (N == 2) {
        if (l1 == l2) {
            ans = comps[l1][c2] - comps[l1][c1 - 1];
            if (matt[l1][c1 - 1] == 0 && matt[l1][c1] == 0)
                ++ ans;

        }
        else {
            ans = comps2[c2] - comps2[c1 - 1];
            if ((matt[1][c1] == 0 || matt[2][c1] == 0) && (matt[1][c1 - 1] == 0 || matt[2][c1 - 1] == 0))
                ++ ans;
        }
    }
    else if (N <= 1000 && M <= 1000) {
        int labels = 0;
        memset(label, 0, sizeof label);

        for (int i = l1; i <= l2; ++ i)
            for (int j = c1; j <= c2; ++ j)
                if (!label[i][j] && mat[i][j] == 0)
                    dfs(i, j, l1, l2, c1, c2, ++ labels);

        return labels;

        // Debug this :(
        if (l1 == l2) {
            for (int i = c1; i <= c2; ++ i)
                if (mat[l1][i] == 0)
                    if (i == c1 || mat[l1][i - 1] == 1)
                        ++ ans;

            return ans;
        }
        else if (c1 == c2) {
            for (int i = l1; i <= l2; ++ i)
                if (mat[i][c1] == 0)
                    if (i == l1 || mat[i - 1][c1] == 1)
                        ++ ans;
            return ans;
        }

        vector <int> toErase;

        vector <pair <int, int> > per;
        for (int i = c1; i <= c2; ++ i)
            per.push_back(make_pair(l1, i));
        for (int i = l1 + 1; i <= l2; ++ i)
            per.push_back(make_pair(i, c2));
        for (int i = c2 - 1; i >= c1; -- i)
            per.push_back(make_pair(l2, i));
        for (int i = l2 - 1; i > l1; -- i)
            per.push_back(make_pair(i, c1));

        int bad = 0;
        for (auto it: per)
            if (mat[it.first][it.second] == 1)
                ++ bad;
            else {
                if (!used[label[it.first][it.second]]) {
                    used[label[it.first][it.second]] = true;
                    toErase.push_back(label[it.first][it.second]);

                    int x = rep[label[it.first][it.second]].first;
                    int y = rep[label[it.first][it.second]].second;

                    if (l1 <= x && x <= l2 && c1 <= y && y <= c2)
                        -- ans;
                }
            }

        int doubles = 0;
        for (int i = 0; i < per.size(); ++ i) {
            int xl = per[i].first;
            int xc = per[i].second;
            int yl = per[(i + 1) % per.size()].first;
            int yc = per[(i + 1) % per.size()].second;

            if (mat[xl][xc] == 1 && mat[yl][yc] == 1)
                ++ doubles;
        }

        ans = sPart[l2][c2] - sPart[l2][c1 - 1] - sPart[l1 - 1][c2] + sPart[l1 - 1][c1 - 1];

        if (bad == 0)
            ++ ans;
        else
            ans += bad - doubles;

        for (auto it: toErase)
            used[it] = false;
        toErase.clear();
    }
    else {
        Map.clear();
        int lin = sr, col = sc;
        if (lin >= l1 && lin <= l2 && col >= c1 && col <= c2) {
            blocks[lin].push_back(col);
        }
        for (auto it: str) {
            if (it == 'N')
                lin --;
            else if (it == 'S')
                lin ++;
            else if (it == 'W')
                col --;
            else
                col ++;

            if (lin >= l1 && lin <= l2 && col >= c1 && col <= c2) {
                blocks[lin].push_back(col);
            }
        }

        for (int i = l1; i <= l2; ++ i) {
            sort(blocks[i].begin(), blocks[i].end());
            blocks[i].push_back(c2 + 1);
        }
        vector <pair <int, int> > v;
        int last = c1 - 1;
        for (auto it: blocks[l1]) {
            if (last + 1 < it) {
                v.push_back(make_pair(last + 1, it - 1));
                Map[make_pair(l1, v.back())] = Map.size();
            }
            last = it;
        }

        vector <pair <int, int> > v2;
        for (int i = l1 + 1; i <= l2; ++ i) {
            int last = c1 - 1;
            for (auto it: blocks[i]) {
                if (last + 1 < it) {
                    v2.push_back(make_pair(last + 1, it - 1));
                    Map[make_pair(i, v2.back())] = Map.size();
                }
                last = it;
            }

            int j = 0;
            for (auto it: v2) {
                while (j < v.size() && v[j].second <= it.second) {
                    if (v[j].second >= it.first) {
                        int A = Map[make_pair(i - 1, v[j])];
                        int B = Map[make_pair(i, it)];

                        graph[A].push_back(B);
                        graph[B].push_back(A);

                    }
                    ++ j;
                }

                if (j < v.size() && v[j].first <= it.second) {
                    int A = Map[make_pair(i - 1, v[j])];
                    int B = Map[make_pair(i, it)];

                    graph[A].push_back(B);
                    graph[B].push_back(A);
                }
            }

            v = v2;
            v2.clear();
        }

        ans = 0;
        for (int i = 1; i <= Map.size(); ++ i)
            if (!viss[i]) {
                dfss(i);
                ++ ans;
            }
    }

    return ans;
}
