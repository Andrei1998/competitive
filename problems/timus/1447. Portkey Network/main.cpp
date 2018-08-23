#include <iostream>
#include <algorithm>
#include <iomanip>

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
    static const int SIZE = 1 << 20;
    int cursor;
    char buffer[SIZE];
    inline void advance() {
        ++ cursor;
        if(cursor == SIZE) {
            cursor = 0;
            fread(buffer, SIZE, 1, input_file);
        }
    }
} in;

const int NMAX = 1000 + 5;
const int MMAX = 500000 + 5;
const int STEPS = 65;

int N, M;

double avg;

struct Edge {
    int a, b;
    int dist, cost;
    double realCost;

    inline double getCost() const {
        return cost - avg * dist;
    }

    friend bool operator<(const Edge &a, const Edge &b) {
        return a.realCost < b.realCost;
    }
} edges[MMAX];

int father[NMAX];
int h[NMAX];

void init() {
    for (int i = 1; i <= N; ++ i)
        father[i] = i, h[i] = 0;
}

int find(int node) {
    /*if (father[node] != father[father[node]])
        father[node] = find(father[node]);
    return father[node];*/

    int root = node;
    while (root != father[root])
        root = father[root];

    while (node != root) {
        int &aux = father[node];
        node = father[node];
        aux = root;
    }

    return root;
}

bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b)
        return false;

    if (h[a] < h[b])
        father[a] = b;
    else {
        if (h[a] == h[b])
            ++ h[a];
        father[b] = a;
    }

    return true;
}

bool works() {
    //Fast rejection
    int cnt = 0;
    for (int i = 1; i <= M && cnt < N - 1; ++ i) {
        edges[i].realCost = edges[i].getCost();
        if (edges[i].getCost() < 0)
            ++ cnt;
    }

    if (cnt == N - 1)
        return true;
    if (cnt == 0)
        return false;

    //Kruskal
    init();
    sort(edges + 1, edges + M + 1);

    double ans = 0;
    cnt = 0;
    for (auto it = edges + 1; it < edges + M + 1 && cnt < N - 1 && ans < 1E-8; ++ it)
        if (unite(it -> a, it -> b)) {
            ans += it -> getCost();
            ++ cnt;
        }
    return ans < 0;
}

int main()
{
    //ios_base :: sync_with_stdio(false);

    in >> N >> M;

    double r = 0;
    for (int i = 1; i <= M; ++ i) {
        in >> edges[i].a >> edges[i].b >> edges[i].dist >> edges[i].cost;
        r += edges[i].cost;
    }

    double l = 0;

    for (int step = 0; step < STEPS; ++ step) {
        avg = (l + r) * 0.5;
        if (works())
            r = avg;
        else
            l = avg;
    }

    cout << fixed << setprecision(10) << l << '\n';
    return 0;
}
