#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 1e5 + 5;
const int MMAX = 2 * NMAX;

int n, m;
int color[NMAX];
vector <int> graph[NMAX];

struct Query {
    int a, b, c;
    vector <int> ans;
} queries[MMAX];

vector <int> stks[NMAX];
vector <int> whichQueries[NMAX];

int h[NMAX];
int parc[2 * NMAX];
int first[NMAX];
int parcSz;

void dfs(int node, int father) {
    stks[color[node]].push_back(node);
    for (auto it: whichQueries[node])
        if (!stks[queries[it].c].empty())
            queries[it].ans.push_back(stks[queries[it].c].back());

    parc[++ parcSz] = node;
    first[node] = parcSz;

    for (auto it: graph[node])
        if (it != father) {
            h[it] = 1 + h[node];
            dfs(it, node);
            parc[++ parcSz] = node;
        }
    stks[color[node]].pop_back();
}

int logar[2 * NMAX];
int dp[19][2 * NMAX];

void computeRmq() {
    for (int i = 2; i <= parcSz; ++ i)
        logar[i] = 1 + logar[i >> 1];

    for (int i = 1; i <= parcSz; ++ i)
        dp[0][i] = parc[i];

    for (int i = 1; (1 << i) <= parcSz; ++ i)
        for (int j = 1; j + (1 << i) - 1 <= parcSz; ++ j)
            if (h[dp[i - 1][j]] < h[dp[i - 1][j + (1 << (i - 1))]])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j + (1 << (i - 1))];
}

int lca(int a, int b) {
    a = first[a], b = first[b];
    if (b < a)
        swap(a, b);
    int y = logar[b - a + 1];

    if (h[dp[y][a]] < h[dp[y][b - (1 << y) + 1]])
        return dp[y][a];
    else
        return dp[y][b - (1 << y) + 1];
}

bool doTest() {
    cin >> n >> m;
    if (cin.eof())
        return false;

    for (int i = 1; i <= n; ++ i)
        cin >> color[i];
    for (int i = 1; i <= n; ++ i) {
        whichQueries[i].clear();
        graph[i].clear();
    }

    for (int i = 1; i < n; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= m; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;

        queries[i].ans.clear();
        queries[i].a = a, queries[i].b = b, queries[i].c = c;
        whichQueries[a].push_back(i);
        whichQueries[b].push_back(i);
    }

    parcSz = 0;
    dfs(1, 0);
    computeRmq();

    for (int i = 1; i <= m; ++ i) {
        int a = queries[i].a, b = queries[i].b;
        int l = lca(a, b);

        bool done = false;
        for (auto it: queries[i].ans)
            if (h[l] <= h[it]) {
                cout << "Find\n";
                done = true;
                break;
            }

        if (!done)
            cout << "NotFind\n";
    }
    cout << '\n';

    return true;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    while (doTest())
        ;
    return 0;
}
