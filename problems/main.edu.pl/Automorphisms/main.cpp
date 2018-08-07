#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

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

const int MOD = 1000000000 + 7;

const int NMAX = 500000 + 5;
int fact[NMAX];

void precalcFacts() {
    fact[0] = 1;
    for (int i = 1; i < NMAX; ++ i)
        fact[i] = (1LL * i * fact[i - 1]) % MOD;
}

int n;
vector <int> graph[NMAX];
int sz[NMAX];

vector <int> centroids;

void dfsCentroids(int node, int father) {
    sz[node] = 1;
    int maxSon = -1;
    for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it)
        if (*it != father) {
            dfsCentroids(*it, node);
            sz[node] += sz[*it];
            if (sz[*it] > maxSon)
                maxSon = sz[*it];
        }

    int maximum = max(maxSon, n - sz[node]);
    if (maximum <= n / 2)
        centroids.push_back(node);
}

const int MOD1 = 1000000000 + 7;
const int MOD2 = 1000000000 + 9;
const int C1 = 63;
const int C2 = 67;

int powC1[2 * NMAX];
int powC2[2 * NMAX];

pair <int, int> hs[NMAX];

bool cmp(const int &a, const int &b) {
    return hs[a] < hs[b];
}

int ans;
void dfsAutomorphisms (int node, int father) {
    //Delete father from adjacency list
    vector <int> :: iterator it = find(graph[node].begin(), graph[node].end(), father);
    if (it != graph[node].end())
        graph[node].erase(it);

    //Solve sons
    sz[node] = 1;
    for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it) {
        dfsAutomorphisms(*it, node);
        sz[node] += sz[*it];
    }

    //Find hash of node
    sort(graph[node].begin(), graph[node].end(), cmp);
    for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it) {
        hs[node].first = (1LL * powC1[2 * sz[*it]] * hs[node].first + hs[*it].first) % MOD1;
        hs[node].second = (1LL * powC2[2 * sz[*it]] * hs[node].second + hs[*it].second) % MOD2;
    }

    hs[node].first = (1LL * hs[node].first * C1 + 1) % MOD1;
    hs[node].second = (1LL * hs[node].second * C2 + 1) % MOD2;

    //Update no. of automorphisms
    int inGroup = 0;
    for (int i = 0; i < graph[node].size(); ++ i) {
        if (i > 0 && hs[graph[node][i]] != hs[graph[node][i - 1]]) {
            ans = (1LL * ans * fact[inGroup]) % MOD;
            inGroup = 1;
        }
        else
            ++ inGroup;
    }

    ans = (1LL * ans * fact[inGroup]) % MOD; //Last group
}

int main()
{
    //freopen("input.in", "r", stdin);
    InputReader cin;

    cin >> n;

    precalcFacts();
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

    dfsCentroids(1, 0);

    int root = centroids[0];
    if (centroids.size() == 2) {
        graph[centroids[0]].erase(find(graph[centroids[0]].begin(), graph[centroids[0]].end(), centroids[1]));
        graph[centroids[1]].erase(find(graph[centroids[1]].begin(), graph[centroids[1]].end(), centroids[0]));

        root = ++ n;
        graph[n].push_back(centroids[0]);
        graph[n].push_back(centroids[1]);
    }

    ans = 1;
    dfsAutomorphisms(root, 0);

    cout << ans << '\n';
    return 0;
}
