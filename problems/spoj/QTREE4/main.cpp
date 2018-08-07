#include <iostream>
#include <cstdio>
#include <random>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cassert>
#include <utility>

using namespace std;

class InputReader {
    public:
        InputReader() {
            input_file = stdin;//fopen(file_name, "r");
            cursor = 0;
            fread(buffer, SIZE, 1, input_file);
        }

        inline InputReader &operator >>(int &n) {
            while((buffer[cursor] < '0' || buffer[cursor] > '9') && buffer[cursor] != '-') {
                advance();
            }

            int sign = 1;
            if (buffer[cursor] == '-') {
                sign = -1;
                advance();
            }

            n = 0;
            while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
                n = n * 10 - buffer[cursor] + '0';
                advance();
            }

            n *= sign;
            return *this;
        }

        inline InputReader &operator >>(char &n) {
            while(buffer[cursor] < 'A' || buffer[cursor] > 'Z')
                advance();

            n = buffer[cursor];
            advance();

            return *this;
        }
    private:
        FILE *input_file;
        static const int SIZE = 1 << 18;
        int cursor;
        char buffer[SIZE];
        inline void advance() {
            ++ cursor;
            if(cursor == SIZE) {
                cursor = 0;
                fread(buffer, SIZE, 1, input_file);
            }
        }
};

const int NMAX = 100000 + 5;

int N;
vector <pair <int, int> > graph[NMAX];

//Only degrees <= 3
vector <pair <int, int> > tree[2 * NMAX];
void addEdge(int a, int b, int c) {
    tree[a].push_back(make_pair(b, c));
    tree[b].push_back(make_pair(a, c));
}

void buildBetterTree(int node, int father, int fatherCost) {
    if (father != 0)
        graph[node].erase(find(graph[node].begin(), graph[node].end(), make_pair(father, fatherCost)));

    if (!graph[node].empty()) {
        addEdge(node, graph[node][0].first, graph[node][0].second);

        int nd = node;
        for (int i = 1; i < graph[node].size(); ++ i) {
            addEdge(nd, ++ N, 0);
            addEdge(N, graph[node][i].first, graph[node][i].second);
            nd = N;
        }

        for (auto it: graph[node])
            buildBetterTree(it.first, node, it.second);
    }
}

int dst[2 * NMAX];
int euler[4 * NMAX];
int first[2 * NMAX];
int h[2 * NMAX];
int szz;

void computeDst(int node, int father) {
    euler[++ szz] = node;
    first[node] = szz;

    for (auto it: tree[node])
        if (it.first != father) {
            dst[it.first] = it.second + dst[node];
            h[it.first] = 1 + h[node];
            computeDst(it.first, node);
            euler[++ szz] = node;
        }
}

int dp[20][4 * NMAX];
int logg2[4 * NMAX];

void precLca() {
    for (int i = 2; i <= szz; ++ i)
        logg2[i] = 1 + logg2[i >> 1];

    for (int i = 1; i <= szz; ++ i)
        dp[0][i] = euler[i];

    for (int i = 1; (1 << i) <= szz; ++ i)
        for (int j = 1; j + (1 << i) - 1 <= szz; ++ j)
            if (h[dp[i - 1][j]] < h[dp[i - 1][j + (1 << (i - 1))]])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j + (1 << (i - 1))];
}

int lca(int a, int b) {
    a = first[a];
    b = first[b];

    if (b < a)
        swap(a, b);
    int y = logg2[b - a + 1];

    if (h[dp[y][a]] < h[dp[y][b - (1 << y) + 1]])
        return dp[y][a];
    else
        return dp[y][b - (1 << y) + 1];
}

int getDst(int a, int b) {
    return dst[a] + dst[b] - 2 * dst[lca(a, b)];
}

//Centroid
bool out[2 * NMAX];
int sz[2 * NMAX];

void dfsSz(int node, int father) {
    sz[node] = 1;
    for (auto it: tree[node])
        if (!out[it.first] && it.first != father) {
            dfsSz(it.first, node);
            sz[node] += sz[it.first];
        }
}

int getCentroid(int node, int father, int szAll) {
    for (auto it: tree[node])
        if (!out[it.first] && it.first != father) {
            if (sz[it.first] > szAll / 2)
                return getCentroid(it.first, node, szAll);
        }
    return node;
}

vector <int> sons[2 * NMAX];
int father[2 * NMAX];
int whichSon[2 * NMAX];

int DEI(int node, int ftr, int hh = 0) {
    dfsSz(node, 0);
    node = getCentroid(node, 0, sz[node]);
    out[node] = true;

    if (ftr) {
        sons[ftr].push_back(node);
        whichSon[node] = sons[ftr].size() - 1;
        father[node] = ftr;
    }

    for (auto it: tree[node])
        if (!out[it.first])
            DEI(it.first, node, hh + 1);
    return node;
}

//Segment tree given by centroid tree
const int INF = 1e9 + 15;
bool active[2 * NMAX];
int best[2 * NMAX];

priority_queue <pair <int, int> > pqs[2 * NMAX][3];

int getMax(priority_queue <pair <int, int> > &ms) {
    while (!ms.empty())
        if (!active[ms.top().second])
            ms.pop();
        else
            break;


    if (ms.empty())
        return -INF;
    else
        return ms.top().first;
}

void computeDp(int node) {
    if (active[node])
        best[node] = 0;
    else
        best[node] = -INF;

    int aux[3];
    for (int i = 0; i < sons[node].size(); ++ i)
        aux[i] = getMax(pqs[node][i]);

    for (int i = 0; i < sons[node].size(); ++ i) {
        if (active[node])
            best[node] = max(best[node], aux[i]);
        for (int j = i + 1; j < sons[node].size(); ++ j)
            best[node] = max(best[node], aux[i] + aux[j]);
    }
    for (auto it: sons[node])
        best[node] = max(best[node], best[it]);
}

void update(int node, bool add = true) {
    int initNode = node;
    while (node) {
        if (father[node]) {
            if (add)
                pqs[father[node]][whichSon[node]].push(make_pair(getDst(father[node], initNode), initNode));
        }
        computeDp(node);
        node = father[node];
    }
}

int main()
{
    //InputReader cin;
    ios_base :: sync_with_stdio(false);
    //freopen("data.in", "r", stdin);

    cin >> N;
    int n = N;
    for (int i = 1; i < N; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(b, c));
        graph[b].push_back(make_pair(a, c));
    }

    buildBetterTree(1, 0, 0);

    /*cout << "N = " << N << endl;
    for (int i = 1; i <= N; ++ i) {
        cout << "node = " << i << endl;
        for (auto it: tree[i])
            cout << it.first << ' ' << it.second << endl;
        cout << endl;
    }*/

    int root = DEI(1, 0);

    /*for (int i = 1; i <= N; ++ i) {
        cout << "node = " << i << ' ' << father[i] << endl;
        for (auto it: sons[i])
            cout << it << ' ';
        cout << endl;
    }*/

    computeDst(1, 0);
    precLca();

    /*cout << "root = " << root << endl;
    for (int i = 1; i <= N; ++ i)
        cout << i << ' ' << father[i] << endl;
    for (int i = 1; i <= N; ++ i)
        best[i] = bestDown[i] = -INF;*/

    for (int i = 1; i <= n; ++ i) {
        //Activate all nodes
        active[i] = true;
        update(i, active[i]);
    }

    int Q = 0;
    cin >> Q;

    while (Q --) {
        char op;
        cin >> op;

        if (op == 'A') {
            if (best[root] < 0)
                cout << "They have disappeared.\n";
            else
                cout << best[root] << '\n';
        }
        else {
            int node;
            cin >> node;
            active[node] ^= 1;
            update(node, active[node]);
        }
    }

    return 0;
}
