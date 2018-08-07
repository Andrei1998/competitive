#include <bits/stdc++.h>

//11:51
using namespace std;

class InputReader {
    public:
    InputReader() {
        input_file = stdin;
        cursor = 0;
        int cnt = fread(buffer, 1, SIZE, input_file);
        if (cnt < SIZE)
            buffer[cnt] = 0;
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
            int cnt = fread(buffer, 1, SIZE, input_file);
            if (cnt < SIZE)
                buffer[cnt] = 0;
        }
    }
} fin;

const int NMAX = 2 * 100000 + 5;

int N;
int A[NMAX];

int logg2[NMAX];
int dp[18][NMAX];

int queryMax(int l, int r) {
    if (l > r)
        return 0;
    int y = logg2[r - l + 1];
    return max(dp[y][l], dp[y][r - (1 << y) + 1]);
}

int bruteQueryMax(int l, int r) {
    int maxim = A[l];
    for (int i = l; i <= r; ++ i)
        maxim = max(maxim, A[i]);
    return maxim;
}

map <pair <int, int>, int> Map;

const int MOD = 1000000000 + 7;
int solve(int st, int dr) {
    if (st == dr)
        return 1;
    if (Map.count(make_pair(st, dr)))
        return Map[make_pair(st, dr)];

    int ans = 0;
    for (int i = st + 1; i < dr; ++ i) {
        if (A[i] > A[st + 1])
            break;

        if (A[i + 1] >= queryMax(i + 2, dr) && ((i - st) % 2 == 1)) {
            int aux = solve(st + 1, i);
            if (aux && (dr - i) % 2 == 1)
                ans = (ans + 1LL * aux * solve(i + 1, dr)) % MOD;
        }
    }

    Map[make_pair(st, dr)] = ans;
    return ans;
}

int main() {
    fin >> N;
    for (int i = 1; i <= N; ++ i) {
        fin >> A[i];
        dp[0][i] = A[i];
    }

    for (int i = 2; i <= N; ++ i)
        logg2[i] = 1 + logg2[i >> 1];
    for (int i = 1; (1 << i) <= N; ++ i)
        for (int j = 1; j + (1 << i) - 1 <= N; ++ j)
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);

    cout << solve(1, N) << '\n';
    return 0;
}
