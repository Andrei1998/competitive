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

inline int lsb(int node) {
    return node & (-node);
}

const int NMAX = 500000 + 5;

int N;
int aib[NMAX];

void add(int where) {
    for (; where <= N; where += lsb(where))
        ++ aib[where];
}

int query(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        ans += aib[where];
    return ans;
}

int main()
{
    InputReader cin;
    cin >> N;

    long long int ans = 0;
    for (int i = 1; i <= N; ++ i) {
        int val;
        cin >> val;
        int x = query(val);
        ans += min(x, i - x - 1);
        add(val);
    }

    cout << ans << '\n';
    return 0;
}
