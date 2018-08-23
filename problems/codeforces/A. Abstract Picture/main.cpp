#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <utility>

using namespace std;

const int NMAX = 3000 + 5;
const int SIGMA = 26;

int N;
int freqLin[NMAX][SIGMA];
int freqCol[NMAX][SIGMA];
int distLin[NMAX];
int distCol[NMAX];

string mat[NMAX];

bool outLin[NMAX];
bool outCol[NMAX];

int main()
{
    cin >> N;
    for (int i = 1; i <= N; ++ i) {
        cin >> mat[i];
        mat[i] = " " + mat[i];
        for (int j = 1; j <= N; ++ j)
            if (mat[i][j] != '?') {
                ++ freqLin[i][mat[i][j] - 'a'];
                if (freqLin[i][mat[i][j] - 'a'] == 1)
                    ++ distLin[i];
                ++ freqCol[j][mat[i][j] - 'a'];
                if (freqCol[j][mat[i][j] - 'a'] == 1)
                    ++ distCol[j];
            }
    }

    queue <pair <int, char> > q;
    for (int i = 1; i <= N; ++ i) {
        if (distLin[i] <= 1)
            q.push({i, 'h'});
        if (distCol[i] <= 1)
            q.push({i, 'v'});
    }

    vector <pair <pair <int, char>, char> > sol;
    while (!q.empty()) {
        int who = q.front().first;
        char type = q.front().second;

        char ch = 'a';
        if (type == 'h') {
            for (int col = 1; col <= N; ++ col)
                if (!outCol[col] && mat[who][col] != '?') {
                    ch = mat[who][col];
                    break;
                }
        }
        else {
            for (int lin = 1; lin <= N; ++ lin)
                if (!outLin[lin] && mat[lin][who] != '?') {
                    ch = mat[lin][who];
                    break;
                }
        }

        sol.push_back({q.front(), ch});
        q.pop();

        if (type == 'h') {
            outLin[who] = true;
            for (int col = 1; col <= N; ++ col)
                if (!outCol[col] && mat[who][col] != '?') {
                    -- freqCol[col][mat[who][col] - 'a'];
                    if (!freqCol[col][mat[who][col] - 'a']) {
                        distCol[col] --;
                        if (distCol[col] == 1)
                            q.push({col, 'v'});
                    }
                }
        }
        else {
            outCol[who] = true;
            for (int lin = 1; lin <= N; ++ lin)
                if (!outLin[lin] && mat[lin][who] != '?') {
                    -- freqLin[lin][mat[lin][who] - 'a'];
                    if (!freqLin[lin][mat[lin][who] - 'a']) {
                        distLin[lin] --;
                        if (distLin[lin] == 1)
                            q.push({lin, 'h'});
                    }
                }
        }
    }

    reverse(sol.begin(), sol.end());
    for (auto it: sol)
        cout << it.first.second << ' ' << it.first.first << ' ' << it.second << '\n';
    return 0;
}
