#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

class InputReader {
public:
    InputReader() {
        input_file = stdin;
        cursor = 0;
        fread(buffer, SIZE, 1, input_file);
    }
    inline InputReader &operator >>(int &n) {
        while((buffer[cursor] < '0' || buffer[cursor] > '9') && buffer[cursor] != '-') {
            advance();
        }

        int sign = 1;
        if (buffer[cursor] == '-') {
            sign = -1;
            advance();
        }

        n = 0;
        while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
            n = n * 10 + buffer[cursor] - '0';
            advance();
        }

        n *= sign;
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

int N;
vector <int> tree[NMAX];
int h[NMAX];
int H;

void dfs1(int node) {
    h[node] = 1;
    for (auto it: tree[node])
        if (it > 0) {
            dfs1(it);
            h[node] = max(h[node], 1 + h[it]);
        }
}

double logAtLeast = -1E18;
int itBest = -1;
int difBest = -1;

void dfs2(int node, int myH) {
    for (auto it: tree[node])
        if (it > 0)
            dfs2(it, myH - 1);
        else if (it) {
            it = -it;
            myH --;

            double val = log2(it) - myH;

            if (val > logAtLeast) {
                logAtLeast = val;
                itBest = it;
                difBest = H - myH;
            }

            myH ++;
        }
}

int main()
{
    InputReader cin;
    cin >> N;

    for (int i = 1; i <= N; ++ i)
        for (int j = 0; j < 2; ++ j) {
            int val;
            cin >> val;
            tree[i].push_back(val);
        }

    dfs1(1);
    H = h[1];

    dfs2(1, H);

    if (itBest == -1) {
        cout << "0\n";
        return 0;
    }

    string ans = "";
    do {
        ans += ((itBest % 2) + '0');
        itBest /= 2;
    } while (itBest);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < difBest; ++ i)
        ans += '0';

    cout << ans << '\n';
    return 0;
}
