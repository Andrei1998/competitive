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

    bool operator<(const Building &arg) const {
        return N < arg.N;
    }

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

void printSol(const vector <SolEntry> &sol) {
    cout << sol.size() << endl;
    for (auto it: sol)
        cout << it << endl;
}

int main() {
    freopen("c_going_green.in", "r", stdin);
    freopen("c_going_green.out", "w", stdout);

    cin >> N >> M >> D >> CNT;

    //cout << N << ' ' << M << ' ' << D << ' ' << CNT << endl;
    for (int i = 0; i < CNT; ++ i)
        cin >> buildings[i];

    vector <pair <int, Building> > types;
    vector <int> areas;
    for (int i = 0; i < CNT; ++ i)
        if (buildings[i].type == 'U') {
            types.push_back(make_pair(buildings[i].utility_index, buildings[i]));
            areas.push_back(buildings[i].N * buildings[i].M);
        }

    sort(types.begin(), types.end());
    sort(areas.begin(), areas.end());

    for (auto it: types) {
        cout << "Index " << it.first << endl;
        cout << it.second << endl;
    }
    cout << endl;
	
    /*vector <pair <double, int> > v;
    for (int i = 0; i < CNT; ++ i)
        if (buildings[i].type == 'R')
            v.push_back(make_pair(buildings[i].getResAreaRatio(), i));
    sort(v.begin(), v.end());
    for (auto it: v)
        cout << it.second << ' ' << it.first << endl;
    cout << buildings[7] << endl;*/

    //printSol(getSol());
    return 0;
}
