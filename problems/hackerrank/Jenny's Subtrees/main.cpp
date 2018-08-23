#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cstdio>
#include <utility>

using namespace std;

class InputReader {
public:
    InputReader() {
        input_file = stdin;
        cursor = 0;
        fread(buffer, SIZE, 1, input_file);
    }
    inline InputReader &operator >>(int &n) {
        while(buffer[cursor] < '0' || buffer[cursor] > '9') {
            advance();
        }
        n = 0;
        while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
            n = n * 10 + buffer[cursor] - '0';
            advance();
        }
        return *this;
    }
private:
    FILE *input_file;
    static const int SIZE = 1 << 17;
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

const int NMAX = 50000 + 5;

int szzz;
vector <int> tree[NMAX];

int n;
vector <int> graph[NMAX];
int sz[NMAX];

void buildTree(int node, int father, int rem) {
    ++ szzz;
    if (!rem)
        return ;

    for (auto it: graph[node])
        if (it != father) {
            tree[node].push_back(it);
            tree[it].push_back(node);
            buildTree(it, node, rem - 1);
        }
}

vector <int> centroids;

void dfsCentroids(int node, int father) {
    sz[node] = 1;
    int maxSon = -1;
    for (vector <int> :: iterator it = tree[node].begin(); it != tree[node].end(); ++ it)
        if (*it != father) {
            dfsCentroids(*it, node);
            sz[node] += sz[*it];
            if (sz[*it] > maxSon)
                maxSon = sz[*it];
        }

    int maximum = max(maxSon, szzz - sz[node]);
    if (maximum <= szzz / 2)
        centroids.push_back(node);
}

const int MOD1 = 1000000000 + 7;
const int MOD2 = 1000000000 + 21;
const int C1 = 633;
const int C2 = 67;

int powC1[2 * NMAX];
int powC2[2 * NMAX];

pair <int, int> hs[NMAX];

bool cmp(const int &a, const int &b) {
    return hs[a] < hs[b];
}

int ans;
void dfsMorph(int node, int father) {
    //Delete father from adjacency list
    vector <int> :: iterator it = find(tree[node].begin(), tree[node].end(), father);
    if (it != tree[node].end())
        tree[node].erase(it);

    //Solve sons
    sz[node] = 1;
    for (vector <int> :: iterator it = tree[node].begin(); it != tree[node].end(); ++ it) {
        dfsMorph(*it, node);
        sz[node] += sz[*it];
    }

    //Find hash of node
    sort(tree[node].begin(), tree[node].end(), cmp);
    for (vector <int> :: iterator it = tree[node].begin(); it != tree[node].end(); ++ it) {
        hs[node].first = (1LL * powC1[2 * sz[*it]] * hs[node].first + hs[*it].first) % MOD1;
        hs[node].second = (1LL * powC2[2 * sz[*it]] * hs[node].second + hs[*it].second) % MOD2;
    }

    hs[node].first = (1LL * hs[node].first * C1 + 1) % MOD1;
    hs[node].second = (1LL * hs[node].second * C2 + 1) % MOD2;

    if (father != 0)
        tree[node].push_back(father);
}

set <pair <pair <int, int>, pair <int, int> > > Set;

int main()
{
    //freopen("input.in", "r", stdin);
    //InputReader cin;

    int raza;
    cin >> n >> raza;

    powC1[0] = powC2[0] = 1;
    for (int i = 1; i <= 2 * n; ++ i) {
        powC1[i] = (1LL * C1 * powC1[i - 1]) % MOD1;
        powC2[i] = (1LL * C2 * powC2[i - 1]) % MOD2;
    }

    for (int i = 1; i < n; ++ i) {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            tree[j].clear();
            hs[j] = make_pair(0, 0);
            sz[j] = 0;
        }
        szzz = 0;
        buildTree(i, 0, raza);

        centroids.clear();
        dfsCentroids(i, 0);

        pair <int, int> h1, h2 = make_pair(-1, -1);
        dfsMorph(centroids[0], 0);
        h1 = hs[centroids[0]];

        if (centroids.size() == 2) {
            for (int j = 1; j <= n; ++ j) {
                hs[j] = make_pair(0, 0);
                sz[j] = 0;
            }

            dfsMorph(centroids[1], 0);
            h2 = hs[centroids[1]];
        }

        if (h2 < h1)
            swap(h2, h1);

        Set.insert(make_pair(h1, h2));
    }

    cout << Set.size() << '\n';
    return 0;
}
