#include <bits/stdc++.h>

using namespace std;

enum ImposedColor {WHITE, BLACK, UNKNOWN};

const int NMAX = 2000 + 5;

int father[NMAX * NMAX / 2];
int h[NMAX * NMAX / 2];
ImposedColor imposed[NMAX * NMAX / 2];

static int find(int node) {
    if (father[father[node]] != father[node])
        return find(father[node]);
    else
        return father[node];
}
stack <pair <int, ImposedColor> > stk;
static inline int unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
        return 0;
    if (h[a] > h[b])
        swap(a, b);

    if (imposed[a] != UNKNOWN && imposed[b] != UNKNOWN && imposed[a] != imposed[b])
        return -1;

    stk.push(make_pair(a, imposed[b]));
    father[a] = b;
    if (h[a] == h[b])
        ++ h[b];
    if (imposed[a] != UNKNOWN)
        imposed[b] = imposed[a];
    return 1;
}
static inline void undo(int cnt) {
    while (cnt-- && !stk.empty()) {
        const int node = stk.top().first;
        imposed[father[node]] = stk.top().second;
        stk.pop();
        if (h[node] == h[father[node]] - 1)
            -- h[father[node]];
        father[node] = node;
    }
}

int N, M;
int cnt;
static inline void init() {
    while (!stk.empty())
        stk.pop();
    for (int i = 1; i <= cnt; ++ i)
        father[i] = i, h[i] = 0, imposed[i] = UNKNOWN;
}


int label[NMAX][NMAX][2];

bool graph[NMAX][NMAX];
vector <pair <int, int> > newEdges;
int p[NMAX];
int pInv[NMAX];

bool success;
void backtr(int node) {
    // Was the last node placed correctly?
    int pushed = 0;
    for (int i = 1; i < node; ++ i) {
        const int nr1 = unite(label[i][node][0], label[p[i]][p[node]][1]);
        const int nr2 = unite(label[i][node][1], label[p[i]][p[node]][0]);
        pushed += (nr1 == 1) + (nr2 == 1);
        if (nr1 == -1 || nr2 == -1
                      || find(label[i][node][0]) == find(label[i][node][1])) {
            undo(pushed);
            return ;
        }
    }

    // If N was ok then we are done
    if (node == N) {
        for (int i = 1; i <= N; ++ i)
            for (int j = 1; j < i; ++ j) {
                const int node2 = find(label[i][j][0]);
                if (imposed[node2] == UNKNOWN) {
                    imposed[node2] = BLACK;
                    imposed[find(label[i][j][1])] = WHITE;
                }
            }
        for (int i = 1; i <= N; ++ i)
            for (int j = 1; j < i; ++ j)
                if (graph[i][j] == 0 && imposed[find(label[i][j][0])] == BLACK)
                    newEdges.push_back(make_pair(i, j));
        success = true;
        return ;
    }

    for (int i = 1; i <= N; ++ i) {
        if (!pInv[i]) {
            pInv[i] = node + 1, p[node + 1] = i;
            backtr(node + 1);
            if (success)
                return ;
            pInv[i] = 0, p[node + 1] = 0;
        }
    }
    undo(pushed);
}

bool solve() {
    cerr << "TRY " << N << endl;
    for (int i = 1; i <= N; ++ i)
        p[i] = pInv[i] = 0;
    cnt = 0;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j < i; ++ j) {
            label[i][j][0] = label[j][i][0] = ++ cnt;
            label[i][j][1] = label[j][i][1] = ++ cnt;
        }
    init();
    success = false;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j < i; ++ j)
            if (graph[i][j] == 1) {
                imposed[label[i][j][0]] = BLACK;
                imposed[label[i][j][1]] = WHITE;
            }
            else
                imposed[label[i][j][0]] = imposed[label[i][j][1]] = UNKNOWN;
    backtr(0);
    return success;
}

void check() {
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j < i; ++ j)
            if (graph[i][j] == graph[p[i]][p[j]])
                cerr << "WA " << ' ' << i << ' ' << j << endl;
    cerr << "--] DONE" << endl;
}

void print(int oldN) {
    cout << N - oldN << ' ' << newEdges.size() << '\n';
    for (auto it: newEdges)
        cout << it.first << ' ' << it.second << '\n';
    for (int i = 1; i <= N; ++ i)
        cout << p[i] << '\n';
}

void testBack(const string testName) {
    cerr << "Start " << testName << " [--";
    const string in  = testName + ".txt";
    const string out = testName + "_solution.txt";

    freopen(in.c_str(), "r", stdin);
    freopen(out.c_str(), "w", stdout);

    newEdges.clear();
    cin >> N >> M;
    memset(graph, 0, sizeof graph);
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = graph[b][a] = true;
    }

    int oldN = N;
    while (N % 4 >= 2 || !solve())
        ++ N;

    for (auto it: newEdges)
        graph[it.first][it.second] = graph[it.second][it.first] = true;
    print(oldN);
    check();
}

void backtrIsomorphism(int node) {
    for (int i = 1; i < node; ++ i)
        if (graph[i][node] == graph[p[i]][p[node]])
            return ;

    if (node == N) {
        success = true;
        return ;
    }

    for (int i = 1; i <= N; ++ i) {
        if (!pInv[i]) {
            pInv[i] = node + 1, p[node + 1] = i;
            backtrIsomorphism(node + 1);
            if (success)
                return ;
            pInv[i] = 0, p[node + 1] = 0;
        }
    }
}

void testIsomorphismBack(const string testName) {
    cerr << "Start " << testName << " [--";
    const string in  = testName + ".txt";
    const string out = testName + "_solution.txt";

    freopen(in.c_str(), "r", stdin);
    freopen(out.c_str(), "w", stdout);

    newEdges.clear();
    cin >> N >> M;
    memset(graph, 0, sizeof graph);
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = graph[b][a] = true;
    }

    success = false;
    for (int i = 1; i <= N; ++ i)
        p[i] = pInv[i] = 0;

    backtrIsomorphism(0);
    assert(success);

    for (auto it: newEdges)
        graph[it.first][it.second] = graph[it.second][it.first] = true;
    print(N);
    check();
}

void testAprox4(const string testName) {
    cerr << "Start " << testName << " [--";
    const string in  = testName + ".txt";
    const string out = testName + "_solution.txt";

    freopen(in.c_str(), "r", stdin);
    freopen(out.c_str(), "w", stdout);

    newEdges.clear();
    cin >> N >> M;
    memset(graph, 0, sizeof graph);
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = graph[b][a] = true;
    }

    int oldN = N;
    N *= 4;

    auto addEdge = [&](const int a, const int b) {
        graph[a][b] = graph[b][a] = 1;
        newEdges.emplace_back(a, b);
    };
    for (int i = 1; i <= oldN; ++ i)
        for (int j = 1; j < i; ++ j)
            if (!graph[i][j]) {
                addEdge(3 * oldN + i, 3 * oldN + j);
                addEdge(2 * oldN + i, 2 * oldN + j);
            }
            else
                addEdge(oldN + i, oldN + j);

    auto drawAll = [&](const int l1, const int r1, const int l2, const int r2) {
        for (int i = l1; i <= r1; ++ i)
            for (int j = l2; j <= r2; ++ j)
                addEdge(i, j);
    };

    drawAll(1, oldN, oldN + 1, oldN + oldN);
    drawAll(1, oldN, 2 * oldN + 1, 2 * oldN + oldN);
    drawAll(3 * oldN + 1, 3 * oldN + oldN, oldN + 1, oldN + oldN);

    for (int i = 1; i <= oldN; ++ i) {
        p[i]            = 3 * oldN + i;
        p[oldN + i]     = 2 * oldN + i;
        p[2 * oldN + i] = i;
        p[3 * oldN + i] = oldN + i;
    }

    for (int i = 1; i <= N; ++ i)
        pInv[p[i]] = i;
    print(oldN);
    check();
}

void testAprox2(const string testName) {
    cerr << "Start " << testName << " [--";
    const string in  = testName + ".txt";
    const string out = testName + "_solution.txt";

    freopen(in.c_str(), "r", stdin);
    freopen(out.c_str(), "w", stdout);

    newEdges.clear();
    cin >> N >> M;
    memset(graph, 0, sizeof graph);
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = graph[b][a] = true;
    }

    int oldN = N;
    if (N % 2) ++ N;

    const auto addEdge = [&](const int a, const int b) {
        graph[a][b] = graph[b][a] = 1;
        newEdges.emplace_back(a, b);
    };
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j < i; ++ j)
            if (!graph[i][j])
                addEdge(i, j);

    int n1 = 1, n2 = N + 1;
    N *= 2;

    while (n2 <= N) {
        p[n1] = n2;
        p[n2] = n1 + 1;
        p[n1 + 1] = n2 + 1;
        p[n2 + 1] = n1;
        n1 += 2, n2 += 2;
    }

    vector <vector <bool> > arr(N + 1, vector <bool>(N + 1, false));
    for (int i = 1; i <= N / 2; ++ i)
        for (int j = N / 2 + 1; j <= N; ++ j)
            if (!arr[i][j]) {
                bool val = 0;
                while (!arr[i][j]) {
                    arr[i][j] = arr[j][i] = true;
                    if (val)
                        addEdge(i, j);
                    val ^= 1;
                    i = p[i], j = p[j];
                }
            }

    for (int i = 1; i <= N; ++ i)
        pInv[p[i]] = i;
    print(oldN);
    check();
}

int nr_leaves(int t[], int n) {
    int leaves = 0;
    for (int i = 1; i <= n; i++) {
        int ok = 1;
        for (int j = 1; j <= n; j++)
            if (t[j - 1] == i) // 0-based indexing
                ok = 0;
        if (ok == 1)
            leaves++;
    }
    return leaves;
}

int main()
{
    //int t[] = {6, 5, 5, 2, 0, 3, 3, 3, 8, 7, 7};
    //int n = 11;
    //cout << nr_leaves(t, n) << endl;

    testBack("01_AMS");
    testBack("03_BOS");
    testBack("04_CPT");
    testBack("05_DUB");
    testIsomorphismBack("02_BER");

    testBack("06_GDN");
    testBack("07_GRU");
    testBack("08_HDN");
    testBack("09_IAS");
    testBack("10_LGA");
    testBack("11_LHR");
    testBack("12_LUX");
    testBack("13_PEK");
    testBack("14_SEA");
    testBack("15_SFO");
    testBack("16_YVR");
    return 0;
}
