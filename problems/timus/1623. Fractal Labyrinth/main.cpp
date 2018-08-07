#include <iostream>
#include <fstream>
#include <algorithm>
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
    inline InputReader &operator >>(char &n) {
        n = buffer[cursor] - '0';
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

const int INF = 1e9;

int N, K;
int dist[6][21][6][21];

bool RF() {
    bool changed = false;
    for (int i = 0; i <= K; ++ i)
        for (int j = 0; j < N; ++ j)
            for (int l = 0; l <= K; ++ l)
                for (int p = 0; p < N; ++ p)
                    for (int t = 0; t <= K; ++ t)
                        for (int b = 0; b < N; ++ b) {
                            int &AC = dist[l][p][t][b];
                            int AB = dist[l][p][i][j];
                            int BC = dist[i][j][t][b];

                            if (AB + BC < AC) {
                                AC = AB + BC;
                                changed = true;
                            }
                        }
    return changed;
}

int main()
{
    InputReader cin;
    cin >> N >> K;

    for (int i = 0; i < 6; ++ i)
        for (int j = 0; j < 21; ++ j)
            for (int k = 0; k < 6; ++ k)
                for (int l = 0; l < 21; ++ l)
                    dist[i][j][k][l] = INF;
    for (int i = 0; i < 6; ++ i)
        for (int j = 0; j < 21; ++ j)
            dist[i][j][i][j] = 0;

    int M = 0;
    cin >> M;

    while (M --) {
        int l1, c1, l2, c2;
        char aux;

        cin >> l1 >> aux >> c1;
        cin >> aux;
        cin >> l2 >> aux >> c2;

        dist[l1][c1][l2][c2] = 1;
        dist[l2][c2][l1][c1] = 1;
    }

    do {
        for (int i = 0; i < N; ++ i)
            for (int j = 0; j < N; ++ j)
                for (int l = 1; l <= K; ++ l)
                    dist[l][i][l][j] = min(dist[l][i][l][j], dist[0][i][0][j]);
    } while (RF());

    int start, finish;
    cin >> start >> finish;

    int ans = dist[0][start][0][finish];
    if (ans == INF)
        cout << "no solution\n";
    else
        cout << ans << '\n';
    return 0;
}
