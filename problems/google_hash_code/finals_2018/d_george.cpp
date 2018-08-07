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

    //for (int i = 0; i < g.N; ++ i)
    //    f << g.mat[i] << endl;
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

void printSol(const vector <SolEntry> &sol) {
    cout << sol.size() << endl;
    for (auto it: sol)
        cout << it << endl;
}

bool filled[NMAX][NMAX];

int main()
{
    freopen("d_wide_selection.in", "r", stdin);
    freopen("d_wide_selection.out", "w", stdout);

    vector<SolEntry> rez;
    int n, m, dist, nr;
    cin >> n >> m >> dist >> nr;
    map <int, int> used;
    for(int i = 0; i < nr; ++i) {
        Building b;
        cin >> b;

        if(b.type == 'R') continue;
        if(used[b.type]) continue;
        used[b.type] = true;

        for(int j = 0; j < 1e4; ++j) {
            int x = rand() % (N - 10), y = rand() % (M - 10);
            //cerr << x << ' ' << y << endl;
            
			if(x + lin >= N || y + col >= M || x + lin < 0 || y + col < 0)
                continue;
            bool good = true;
            for(int dx = 0; dx < lin; ++dx)
                for(int dy = 0; dy < col; ++dy)
                {
                    if(x + dx >= N || y + dy >= M)
                    {
                        good = false;
                        continue;
                    }
                    if(filled[x + dx][y + dy] && v[dx][dy] == '#') good = false;
                }
            if(!good) continue;

            rez.push_back(SolEntry(i, x, y));
            for(int dx = 0; dx < lin; ++dx)
                for(int dy = 0; dy < col; ++dy) {
                    if(v[dx][dy] == '#') filled[x+dx][y+dx] = true;
                }
        }
    }

    cout << (rez.size()) << '\n';
    for(auto x : rez) cout << x.which << ' ' << x.lin << ' ' << x.col << endl;
    return 0;
}
