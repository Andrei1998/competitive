#include <fstream>
#include <cstdio>
#include <algorithm>
#include <vector>

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

const int NMAX = 500 + 5;

class MyCmp {
public:
    inline bool operator()(const vector <int> &a, const vector <int> &b) {
        if (a.size() != b.size())
            return a.size() < b.size();
        else
            return a < b;
    }
};

int v[NMAX];
vector <int> tras[NMAX];

int main()
{
    InputReader cin("6st.in");
    ofstream cout("6st.out");

    int N;
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];

    int M;
    cin >> M;
    for (int i = 1; i <= M; ++ i) {
        int sz;
        cin >> sz;
        tras[i].resize(sz);
        for (int j = 0; j < sz; ++ j)
            cin >> tras[i][j];
    }
    sort(tras + 1, tras + M + 1, MyCmp());

    int ans = 0;
    for (int i = 1; i <= M; ++ i) {
        int minimum = (1 << 30) - 1;
        for (vector <int> :: iterator it = tras[i].begin(); it != tras[i].end(); ++ it)
            minimum = min(minimum, v[*it]);
        ans += minimum;
        for (vector <int> :: iterator it = tras[i].begin(); it != tras[i].end(); ++ it)
            v[*it] -= minimum;
    }

    cout << ans << '\n';
    return 0;
}
