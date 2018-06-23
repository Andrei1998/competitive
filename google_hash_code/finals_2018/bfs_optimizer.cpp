#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200 + 5;

const int A = 5, B = 7;
const char pattern[9][9] = {"#######",
                            "#######",
                            ".######",
                            ".....##",
                            "......#"};

char printPos(int x, int y) {
    if (x < 0 || y < 0)
        return '.';
    if (x >= A || y >= B)
        return '.';
    return pattern[x][y];
}

map <pair <int, int>, int> dists;
map <pair <int, int>, bool> works;
void updCell(const pair <int, int> &cell, int val) {
    if (!dists.count(cell))
        dists[cell] = val;
    else
        dists[cell] = min(dists[cell], val);
}

int getDist(const pair <int, int> &a, const pair <int, int> &b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

bool full(int l1, int c1, int l2, int c2) {
    for (int i = l1; i <= l2; ++ i)
        for (int j = c1; j <= c2; ++ j)
            if (!works[make_pair(i, j)])
                return false;
    return true;
}

bool mat[100][100];

int main()
{
    freopen("data.out", "w", stdout);

    const int UP1 = 60;
    const int UP2 = 60;

    const int C1 = 43 + 1 - 1;
    const int C2 = 47 + 1 + 1;
    const int dx = 21 + 1;
    const int dy = 26 + 1;

    for (int i = 0; i < A; ++ i)
        for (int j = 0; j < B; ++ j)
            if (pattern[i][j] == '#')
                for (int x = -20; x <= UP1; ++ x)
                    for (int y = -20; y <= UP2; ++ y)
                        updCell(make_pair(x, y), getDist(make_pair(x, y), make_pair(i, j)));

    //Special diagonal
    for (int i = 0; i < A; ++ i)
        for (int j = 0; j < B; ++ j)
            if (pattern[i][j] == '#')
                for (int x = -20; x <= UP1; ++ x)
                    for (int y = -20; y <= UP2; ++ y)
                        updCell(make_pair(x, y), getDist(make_pair(x, y), make_pair(i + dx, j + dy)));

					
    for (int i = 0; i < A; ++ i)
        for (int j = 0; j < B; ++ j)
            if (pattern[i][j] == '#')
                for (int x = -20; x <= UP1; ++ x)
                    for (int y = -20; y <= UP2; ++ y)
                        updCell(make_pair(x, y), getDist(make_pair(x, y), make_pair(i, j + C2)));

    for (int i = 0; i < A; ++ i)
        for (int j = 0; j < B; ++ j)
            if (pattern[i][j] == '#')
                for (int x = -20; x <= UP1; ++ x)
                    for (int y = -20; y <= UP2; ++ y)
                        updCell(make_pair(x, y), getDist(make_pair(x, y), make_pair(i + C1, j)));

    for (int i = 0; i < A; ++ i)
        for (int j = 0; j < B; ++ j)
            if (pattern[i][j] == '#')
                for (int x = -20; x <= UP1; ++ x)
                    for (int y = -20; y <= UP2; ++ y)
                        updCell(make_pair(x, y), getDist(make_pair(x, y), make_pair(i + C1, j + C2)));
					

    for (int x = -20; x <= UP1; ++ x) {
        for (int y = -20; y <= UP2; ++ y) {
            int nr = dists[make_pair(x, y)];
            if (nr > 20) {
                nr = -1;
                works[make_pair(x, y)] = false;
            }
            else
                works[make_pair(x, y)] = true;
            cout << setw(2) << nr << ' ';
        }
        cout << endl;
    }

	
    return 0;

	
    for (int x = -20; x < 30; ++ x)
        for (int y = -20; y < 30; ++ y)
            if (works[make_pair(x, y)] && !works[make_pair(x + 1, y)] && !works[make_pair(x, y + 1)]) {
                for (int i = -20; i <= x; ++ i)
                    for (int j = -20; j <= y; ++ j)
                        if (full(i, j, x, y)) {
                            int a = x - i + 1;
                            int b = y - j + 1;
                            if (a == 20 && b == 27) {
                                cout << i << ' ' << j << ' ' << x << ' ' << y << endl;
                            }
                            mat[a][b] = true;
                        }
            }

    int maximum = -1;
    int wherex, wherey;
    for (int i = 1; i <= 70; ++ i)
        for (int j = 1; j <= 70; ++ j)
            if (mat[i][j]) {
                int cnt = (1000 / i) * (1000 / j) * (i * j - 23);
                if (cnt > maximum) {
                    maximum = cnt;
                    wherex = i;
                    wherey = j;
                }
            }

    cout << maximum * 5 << endl;
    cout << wherex << ' '<< wherey << endl;

    int x1 = -7;
    int y1 = -8;
    int x2 = 12;
    int y2 = 18;

    for (int i = x1; i <= x2; ++ i) {
        for (int j = y1; j <= y2; ++ j)
            cout << printPos(i, j);
        cout << endl;
    }
    return 0;
}
