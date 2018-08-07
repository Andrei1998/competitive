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

const int SQRT = 150;

const int NMAX = 30000 + 5;
const int INF = 1E9 + 5;

int N, sz;
vector <pair <int, int> > graph[NMAX];

bitset <(SQRT + 1) * NMAX> vis;
int dist[(SQRT + 1) * NMAX];

inline void addEdge(int a, int b, int c) {
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
}

int B[NMAX];
int P[NMAX];

int main()
{
    InputReader cin;

    int M;
    cin >> N >> M;
    for (int i = 1; i <= N; ++ i)
        dist[i] = INF;

    sz = N;
    for (int b = 1; b <= SQRT; ++ b) {
        for (int i = 1; i <= N; ++ i)
            dist[sz + i] = INF;
        sz += N;
    }

    for (int i = 1; i <= M; ++ i) {
        cin >> B[i] >> P[i];
        ++ B[i];
        if (P[i] <= SQRT)
            graph[B[i]].push_back({P[i] * N + B[i], 0});
        else {
            int cnt = 0;
            for (int j = B[i] - P[i]; j > 0; j -= P[i])
                graph[B[i]].push_back({j, ++ cnt});
            cnt = 0;
            for (int j = B[i] + P[i]; j <= N; j += P[i])
                graph[B[i]].push_back({j, ++ cnt});
        }
    }

    priority_queue <pair <int, int> > q;
    q.push({0, B[1]});
    dist[B[1]] = 0;

    vector <pair <int, int> > v;
    while (!q.empty()) {
        int node = q.top().second;
        int dst = -q.top().first;
        q.pop();

        if (vis[node])
            continue;
        vis[node] = true;

        if (node == B[2]) {
            cout << dst << '\n';
            return 0;
        }

        //General edges
        if (node <= N)
            for (auto &it: graph[node])
                if (!vis[it.first] && dst + it.second < dist[it.first]) {
                    dist[it.first] = dst + it.second;
                    q.push({-dist[it.first], it.first});
                }

        //Superior state edges
        int b = (node - 1) / N + 1;
        if (b > 1) {
            int dr = b * N;
            int st = dr - N + 1;

            b --;

            v.clear();
            if (node - b >= st && !vis[node - b])
                v.push_back({node - b, 1});
            if (node + b <= dr && !vis[node + b])
                v.push_back({node + b, 1});
            if (!vis[(node - 1) % N + 1])
                v.push_back({(node - 1) % N + 1, 0});

            for (auto &it: v)
                if (dst + it.second < dist[it.first]) {
                    dist[it.first] = dst + it.second;
                    q.push({-dist[it.first], it.first});
                }
        }
    }

    cout << "-1\n";
    return 0;
}
