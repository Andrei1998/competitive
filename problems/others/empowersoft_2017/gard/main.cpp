#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

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

struct Interv {
    int l, r, c;
    bool active;
} intervs[NMAX];

vector <int> change[NMAX];

typedef long long int lint;
lint dp[NMAX];

class MyCmp {
public:
    inline bool operator()(const int &a, const int &b) const {
        return dp[intervs[a].l - 1] + intervs[a].c > dp[intervs[b].l - 1] + intervs[b].c;
    }
};

priority_queue <int, vector <int>, MyCmp> pq;

int main()
{
    InputReader cin("gard.in");
    ofstream cout("gard.out");

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; ++ i) {
        cin >> intervs[i].l >> intervs[i].r >> intervs[i].c;
        change[intervs[i].l].push_back(i);
        change[intervs[i].r + 1].push_back(i);
    }

    for (int i = 1; i <= N; ++ i) {
        for (vector <int> :: iterator it = change[i].begin(); it != change[i].end(); ++ it) {
            intervs[*it].active ^= 1;
            if (intervs[*it].active)
                pq.push(*it);
        }

        while (!pq.empty() && !intervs[pq.top()].active)
            pq.pop();
        int who = pq.top();
        dp[i] = dp[intervs[who].l - 1] + intervs[who].c;
    }

    cout << dp[N] << '\n';
    return 0;
}
