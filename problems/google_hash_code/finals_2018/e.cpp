#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000 + 5;
const int CNTMAX = 200 + 5;
int N, M, D, CNT;

struct Building {
    char type;
    int N, M;
    int residents;
    int utility_index;

    vector <string> mat;

    double getResAreaRatio() {
        return 1.0 * residents / (N * M);
    }
} buildings[CNTMAX];

istream& operator>>(istream& f, Building &g) {
    f >> g.type >> g.N >> g.M;
    if (g.type == 'R')
        f >> g.residents;
    else
        f >> g.utility_index;

    g.mat.resize(g.N);
    for (int i = 0; i < g.N; ++ i)
        f >> g.mat[i];
    return f;
}

ostream& operator<<(ostream& f, const Building &g) {
    f << g.type << ' ' << g.N << ' ' << g.M << ' ';
    if (g.type == 'R')
        f << g.residents;
    else
        f << g.utility_index;
    f << endl;

    for (int i = 0; i < g.N; ++ i)
        f << g.mat[i] << endl;
    return f;
}

struct SolEntry {
    int id;
    int x, y;
    SolEntry(const int _id, const int _x = 0, const int _y = 0):
        id(_id), x(_x), y(_y) {}
};

ostream& operator<<(ostream& g, const SolEntry &s) {
    g << s.id << ' ' << s.x << ' ' << s.y;
    return g;
}

vector <SolEntry> getSol1() {
    static const int A = 20, B = 27;
    static char pattern[30][30]  = {"...........................",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "........#######............",
                                    "........#######............",
                                    ".........######............",
                                    ".............##............",
                                    "..............#............",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "...........................",
                                    "..........................."};

    static char mat[1000][1000];

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            mat[i][j] = pattern[i % A][j % B];

    vector <SolEntry> sol;
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            if (mat[i][j] == '.') {
                // Place single tile
                sol.push_back(SolEntry(1, i, j));
            }
            else if (mat[i][j] == '#') {
                if (mat[i - 1][j] == '.' && mat[i][j - 1] == '.') {
                    // Place utility tile
                    const int toX = i + buildings[19].N - 1;
                    const int toY = j + buildings[19].M - 1;

                    assert(toX < N && toY < M);
                    sol.push_back(SolEntry(19, i, j));
                }
            }
            else
                assert(0);

    return sol;
}

int getCost(const vector <SolEntry> &sol) {
    static char mat[NMAX][NMAX];

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            mat[i][j] = '.';

     for (auto it: sol) {
        const int who = it.id;
        const vector <string> &pattern = buildings[who].mat;
        if (buildings[who].type == 'R')
            continue;
        const int n = buildings[who].N;
        const int m = buildings[who].M;
        const int x = it.x;
        const int y = it.y;

        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j) {
                assert(0 <= x + i && x + i < N && 0 <= y + j && y + j < M);
                if (pattern[i][j] == '#')
                    mat[x + i][y + j] = pattern[i][j];
                else if (mat[i][j] == '#')
                    assert(0);
            }
    }

    queue <pair <int, int> > q;
    vector <vector <int> > dist(vector <vector <int> >(N, vector <int>(M, -1)));
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            if (mat[i][j] == '#') {
                q.push(make_pair(i, j));
                dist[i][j] = 0;
            }

    int cost = 0;
    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    while (!q.empty()) {
        const pair <int, int> node = q.front();
        q.pop();
        const int l = node.first;
        const int c = node.second;

        if (mat[l][c] != '#' && dist[l][c] <= D)
            cost += 5;
        for (int i = 0; i < 4; ++ i) {
            const int nl = l + dx[i];
            const int nc = c + dy[i];

            if (0 <= nl && nl < N && 0 <= nc && nc < M && dist[nl][nc] == -1) {
                dist[nl][nc] = 1 + dist[l][c];
                q.push(make_pair(nl, nc));
            }
        }
    }

    return cost;
}

vector <SolEntry> getSol2(int C1, int C2, int dx, int dy) {
    // First grid
    vector <SolEntry> sol;
    for (int x = 0; x + 4 < N; x += C1)
        for (int y = 0; y + 6 < M; y += C2)
            sol.push_back(SolEntry(19, x, y));
    // Second grid
    for (int x = dx; x + 4 < N; x += C1)
        for (int y = dy; y + 6 < M; y += C2)
            sol.push_back(SolEntry(19, x, y));

    // Build matrix to see empty cells
    static char mat[NMAX][NMAX];
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            mat[i][j] = '.';

     for (auto it: sol) {
        const int who = it.id;
        const vector <string> &pattern = buildings[who].mat;
        const int n = buildings[who].N;
        const int m = buildings[who].M;
        const int x = it.x;
        const int y = it.y;

        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j) {
                assert(0 <= x + i && x + i < N && 0 <= y + j && y + j < M);
                if (pattern[i][j] == '#')
                    mat[x + i][y + j] = pattern[i][j];
                else if (mat[i][j] == '#')
                    assert(0);
            }
    }

    // Add empty cells
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < M; ++ j)
            if (mat[i][j] == '.')
                sol.push_back(SolEntry(1, i, j));
    return sol;
}

void printSol(const vector <SolEntry> &sol) {
    cout << sol.size() << endl;
    for (auto it: sol)
        cout << it << endl;
}

int main() {
    freopen("e_precise_fit.in", "r", stdin);
    freopen("e_precise_fit.out", "w", stdout);

    cin >> N >> M >> D >> CNT;

    //cout << N << ' ' << M << ' ' << D << ' ' << CNT << endl;
    for (int i = 0; i < CNT; ++ i)
        cin >> buildings[i];

    //for (int i = 0; i < CNT; ++ i)
    //    if (buildings[i].type == 'R')
    //        cout << i << ' ' << buildings[i].getResAreaRatio() << endl;

    //printSol(getSol1());
    //auto it1 = getSol1();
    //cout << getCost(it1) << endl;

    printSol(getSol2(45, 46, 23, 26));
    return 0;
}
