#include <fstream>
#include <vector>
#include <cstdio>

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

const int NMAX = 1000000 + 5;

int N, K;
int a[NMAX];
int b[NMAX];

int aib[NMAX];

inline int lsb(int node) {
    return node & (-node);
}

int query(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        if (aib[where] > ans)
            ans = aib[where];
    return ans;
}

void update(int where, int val) {
    for (; where <= N; where += lsb(where))
        if (val > aib[where])
            aib[where] = val;
}

vector <int> freqB[NMAX];
vector <pair <int, int> > pending;

int main()
{
    InputReader cin("monkey.in");
    ofstream cout("monkey.out");

    cin >> N >> K;
    for (int i = 1; i <= N; ++ i)
        cin >> a[i];
    for (int i = 1; i <= N; ++ i) {
        cin >> b[i];
        freqB[b[i]].push_back(i);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        for (vector <int> :: iterator it = freqB[a[i]].begin(); it != freqB[a[i]].end(); ++ it) {
            int val = 1 + query(*it - 1);
            pending.push_back(make_pair(*it, val));
            if (val > ans)
                ans = val;
        }

        for (int j = 0; j < pending.size(); ++ j)
            update(pending[j].first, pending[j].second);
        pending.clear();
    }

    cout << ans << '\n';
    return 0;
}
