#include <iostream>
#include <algorithm>
#include <cassert>

#define lint long long int
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

int N;
int l[NMAX];

int main()
{
    InputReader cin;
    //freopen("input.in", "r", stdin);

    cin >> N;
    for (int i = 1; i <= N; ++ i) {
        int a, b;
        cin >> a >> b;
        l[i] = a + b;
    }

    int groups = 0;
    for (int start = 1, i; start <= N; start = i) {
        ++ groups;
        int sgn = 1;
        lint sum = 0;

        lint low = 0, up = l[start];
        for (i = start; i <= N; ++ i) {
            sum = 1LL * l[i] - sum;
            sgn *= (-1);

            if (sgn == 1)
                low = max(1LL * low, -sum);
            else
                up = min(1LL * up, sum);

            if (up < low)
                break;
        }
    }

    cout << N - groups << '\n';
    return 0;
}
