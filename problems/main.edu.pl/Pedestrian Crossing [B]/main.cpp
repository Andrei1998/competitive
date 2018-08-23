#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

#define lint long long int
using namespace std;

class InputReader {
public:
    InputReader() {
        input_file = stdin;
        cursor = 0;
        fread(buffer, SIZE, 1, input_file);
    }
    template <typename T>
    inline InputReader &operator >>(T &n) {
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

const int NMAX = 5e5 + 5;

int N, s, MOD;
lint p[NMAX];

vector <pair <int, int> > intervs;
InputReader f;

void test() {
    f >> s >> MOD >> N;

    p[1] = MOD + s - 1;
    for (int i = 1; i <= N; ++ i)
        f >> p[i + 1];

    ++ N;
    for (int i = 2; i <= N; ++ i)
        p[i] += p[i - 1];

    intervs.clear();

    //Only whites
    for (int i = 2; i <= N; i += 2) {
        lint l = p[i - 1] + 1 - (s - 1);
        lint r = p[i];

        if (r - l + 1 >= MOD) {
            cout << "NIE\n";
            return ;
        }

        l %= MOD;
        r %= MOD;

        if (l <= r)
            intervs.push_back(make_pair(l, r));
        else {
            intervs.push_back(make_pair(0, r));
            intervs.push_back(make_pair(l, MOD - 1));
        }
    }

    sort(intervs.begin(), intervs.end());

    int dr = -1;
    for (vector <pair <int, int> > :: iterator it = intervs.begin(); it != intervs.end(); ++ it) {
        if (it -> first > dr + 1) {
            cout <<"TAK\n";
            return ;
        }
        else
            dr = max(dr, it -> second);
    }

    if (dr == MOD - 1)
        cout << "NIE\n";
    else
        cout << "TAK\n";
}

int main()
{
    //freopen("input.in", "r", stdin);

    int T = 0;
    f >> T;

    while (T --)
        test();

    return 0;
}
