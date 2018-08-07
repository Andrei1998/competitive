#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int N, M;

map <int, vector <pair <int, int> > > lins;
map <int, vector <pair <int, int> > > cols;

const int NMAX = 300000 + 5;

int st[NMAX];
int dr[NMAX];
int sus[NMAX];
int jos[NMAX];
bool isExit[NMAX];

queue <int> q;
int dist[NMAX];

int main()
{
    cin >> N >> M;
    int X, Y;
    cin >> X >> Y;

    int sz = 0;
    lins[X].push_back(make_pair(Y, ++ sz));
    cols[Y].push_back(make_pair(X, sz));

    int O;
    cin >> O;

    for (int i = 1; i <= O; ++ i) {
        int lin, col;
        cin >> lin >> col;

        lins[lin].push_back(make_pair(col, ++ sz));
        cols[col].push_back(make_pair(lin, sz));
    }

    int e = 0;
    cin >> e;

    for (int i = 1; i <= e; ++ i) {
        int lin, col;
        cin >> lin >> col;

        lins[lin].push_back(make_pair(col, ++ sz));
        cols[col].push_back(make_pair(lin, sz));
        isExit[sz] = true;
    }

    for (auto &it: lins) {
        sort(it.second.begin(), it.second.end());
        for (int i = 0; i + 1 < it.second.size(); ++ i) {
            st[it.second[i].second] = it.second[i + 1].second;
            dr[it.second[i + 1].second] = it.second[i].second;
        }
    }

    for (auto &it: cols) {
        sort(it.second.begin(), it.second.end());
        for (int i = 0; i + 1 < it.second.size(); ++ i) {
            sus[it.second[i].second] = it.second[i + 1].second;
            jos[it.second[i + 1].second] = it.second[i].second;
        }
    }

    q.push(1);
    dist[1] = 1;
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (isExit[node]) {
            cout << dist[node] - 2 << '\n';
            return 0;
        }

        if (st[node] && !dist[st[node]]) {
            q.push(st[node]);
            dist[st[node]] = 1 + dist[node];
        }
        if (dr[node] && !dist[dr[node]]) {
            q.push(dr[node]);
            dist[dr[node]] = 1 + dist[node];
        }
        if (sus[node] && !dist[sus[node]]) {
            q.push(sus[node]);
            dist[sus[node]] = 1 + dist[node];
        }
        if (jos[node] && !dist[jos[node]]) {
            q.push(jos[node]);
            dist[jos[node]] = 1 + dist[node];
        }
    }

    cout << "-1\n";
    return 0;
}
