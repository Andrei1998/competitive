#include <iostream>
#include <cstdio>

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

const int NMAX = 1000 + 5;

int query[NMAX];
int mat[NMAX][NMAX];

int main()
{
    InputReader cin;

    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; ++ i)
        for (int j = 1; j <= M; ++ j)
            cin >> mat[i][j];

    int Q = 0;
    cin >> Q;

    while (Q --) {
        for (int i = 1; i <= M; ++ i)
            cin >> query[i];

        int ans = 0;
        for (int i = 1; i <= N; ++ i) {
            bool ok = true;
            for (int j = 1; j <= M && ok; ++ j)
                if (query[j] != -1)
                    if (query[j] != mat[i][j])
                        ok = false;
            ans += ok;
        }

        cout << ans << '\n';
    }

    return 0;
}
