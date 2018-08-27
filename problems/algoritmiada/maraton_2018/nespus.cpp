#include <bits/stdc++.h>

using namespace std;

class InputReader {
public:
    InputReader() {}
    InputReader(const char *file_name) {
        input_file = fopen(file_name, "r");
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

const int NMAX = 100000 + 5;

int N, K;
int edgeA[NMAX];
int edgeB[NMAX];
int edgeC[NMAX];

set <int> graph[NMAX];
int color[NMAX];
int colors;
int sz[4 * NMAX];

int cntAtLeastK;
void updCntAtLeastK(int cl, int sign) {
    if (sz[cl] >= K)
        cntAtLeastK += sign;
}

int colorFrom(int node, int father, int cl) {
    int cnt = 1;
    color[node] = cl;
    for (auto it: graph[node])
        if (it != father)
            cnt += colorFrom(it, node, cl);
    return cnt;
}

bool traverse(int node, int father, int &cnt) {
    -- cnt;
    if (cnt == 0)
        return true;
    for (auto it: graph[node])
        if (it != father)
            if (traverse(it, node, cnt))
                return true;
    return false;
}

void link(int a, int b) {
    if (sz[color[a]] > sz[color[b]])
        swap(a, b);

    updCntAtLeastK(color[a], -1);
    updCntAtLeastK(color[b], -1);

    sz[color[a]] = 0;
    sz[color[b]] += colorFrom(a, 0, color[b]);
    updCntAtLeastK(color[b], 1);

    // Add edges
    graph[a].insert(b);
    graph[b].insert(a);
}

void cut(int a, int b) {
    // Erase edges
    graph[a].erase(b);
    graph[b].erase(a);

    // Determine smaller component
    int who = -1;
    int s = 1;
    while (1) {
        int cp = s;
        if (!traverse(a, 0, cp)) {
            who = a;
            break;
        }
        cp = s;
        if (!traverse(b, 0, cp)) {
            who = b;
            break;
        }
        s <<= 1;
    }

    if (who == b)
        swap(a, b);

    // Recolor smaller component
    ++ colors;
    sz[colors] = colorFrom(a, 0, colors);
    updCntAtLeastK(colors, 1);

    updCntAtLeastK(color[b], -1);
    sz[color[b]] -= sz[colors];
    updCntAtLeastK(color[b], 1);
}

int main() {
    InputReader cin("nespus.in");
    ofstream cout("nespus.out");

    cin >> N >> K;
    for (int i = 1; i < N; ++ i)
        cin >> edgeA[i] >> edgeB[i] >> edgeC[i];

    colors = N;
    for (int i = 1; i <= N; ++ i)
        color[i] = i, sz[i] = 1;

    int ans = edgeC[N - 1] - edgeC[1];
    int j = 0;
    for (int i = 1; i < N; ++ i) {
        while (j + 1 < N && cntAtLeastK == 0) {
            ++ j;
            link(edgeA[j], edgeB[j]);
        }
        if (cntAtLeastK == 0)
            break;
        ans = min(ans, edgeC[j] - edgeC[i]);
        cut(edgeA[i], edgeB[i]);
    }

    cout << ans << endl;
    return 0;
}
