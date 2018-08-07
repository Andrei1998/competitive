#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

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

const int NMAX = 500000 + 5;

int N, M;
vector <int> graph[NMAX];

bool vis[NMAX];
int order[NMAX];
int invOrder[NMAX];
int dp1[NMAX];
int dp2[NMAX];
int dp3[NMAX];
int dp4[NMAX];
int sz;

void dfsSort(int node) {
    vis[node] = true;
    for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it)
        if (!vis[*it])
            dfsSort(*it);
    order[-- sz] = node;
    invOrder[node] = sz;
}

vector <int> ins[NMAX];
vector <int> del[NMAX];

priority_queue <pair <int, int> > pq;

bool dead[2 * NMAX];
vector <int> freq[NMAX];

int main()
{
    InputReader cin;

    cin >> N >> M;
    for (int i = 1; i <= M; ++ i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    sz = N + 1;
    for (int i = 1; i <= N; ++ i)
        if (!vis[i])
            dfsSort(i);

    for (int i = N; i; -- i) {
        int node = order[i];
        for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it)
            dp2[node] = max(dp2[node], 1 + dp2[*it]);
    }
    for (int i = 1; i <= N; ++ i) {
        int node = order[i];
        for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it)
            dp1[*it] = max(dp1[*it], 1 + dp1[node]);
    }

    for (int i = 1; i <= N; ++ i) {
        int node = order[i];
        for (vector <int> :: iterator it = graph[node].begin(); it != graph[node].end(); ++ it) {
            int j = invOrder[*it];
            ins[i + 1].push_back(1 + dp1[node] + dp2[*it]);
            del[j].push_back(1 + dp1[node] + dp2[*it]);
        }
    }

    for (int i = 1; i <= N; ++ i)
        dp3[i] = max(dp3[i - 1], dp1[order[i]]);
    for (int i = N; i; -- i)
        dp4[i] = max(dp4[i + 1], dp2[order[i]]);

    int ans = NMAX;
    int node = -1;
    int entry = 0;
    for (int i = 1; i <= N; ++ i) {
        for (vector <int> :: iterator it = ins[i].begin(); it != ins[i].end(); ++ it) {
            pq.push(make_pair(*it, ++ entry));
            freq[*it].push_back(entry);
        }
        for (vector <int> :: iterator it = del[i].begin(); it != del[i].end(); ++ it) {
            dead[freq[*it].back()] = true;
            freq[*it].pop_back();
        }
        int maxi = max(dp3[i - 1], dp4[i + 1]);
        while (!pq.empty())
            if (dead[pq.top().second])
                pq.pop();
            else
                break;
        if (!pq.empty())
            maxi = max(maxi, pq.top().first);
        if (maxi < ans) {
            ans = maxi;
            node = order[i];
        }
    }

    cout << node << ' ' << ans << '\n';
    return 0;
}
