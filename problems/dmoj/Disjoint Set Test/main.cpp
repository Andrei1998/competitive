#include <bits/stdc++.h>

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

const int NMAX = 100000 + 5;

int N;
int father[NMAX];
int h[NMAX];

void init() {
    for (int i = 1; i <= N; ++ i)
        father[i] = i;
}

int find(int node) {
    if (father[father[node]] != father[node])
        father[node] = find(father[node]);
    return father[node];
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

int ans[NMAX];

int main()
{
    //ios_base :: sync_with_stdio(false);
    InputReader cin;

    int M = 0;
    cin >> N >> M;
    init();

    int pos = 0;
    for (int i = 1; i <= M && pos + 1 < N; ++ i) {
        int a, b;
        cin >> a >> b;

        if (unite(a, b))
            ans[pos ++] = i;
    }

    if (pos + 1 < N)
        cout << "Disconnected Graph\n";
    else {
        for (int i = 0; i + 1 < N; ++ i)
            cout << ans[i] << '\n';
    }
    return 0;
}
