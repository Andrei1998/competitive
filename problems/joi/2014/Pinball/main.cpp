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

typedef long long int lint;
const int NMAX = 100000 + 5;
const lint INF = 1E18 + 256;

int N;
class Structure {
    lint dp[5 * NMAX];
    lint aib[5 * NMAX];
    inline int lsb(int node) {
        return node & (-node);
    }

public:
    void fill(const lint val) {
        for (int i = 1; i <= N; ++ i)
            dp[i] = aib[i] = val;
    }
    void update(int pos, const lint val) {
        dp[pos] = val;
        for (; pos <= N; pos += lsb(pos))
            aib[pos] = min(aib[pos], val);
    }
    lint getMin(const int l, int r) {
        lint ans = INF;
        while (r >= l)
            if (r - lsb(r) + 1 < l)
                ans = min(ans, dp[r --]);
            else
                ans = min(ans, aib[r]), r -= lsb(r);
        return ans;
    }
} lft, rgt;

int M;
int A[NMAX], B[NMAX], C[NMAX], D[NMAX];

int main()
{
    InputReader cin;
    //ios_base :: sync_with_stdio(false);

    cin >> M >> N;

    vector <int> vals = {1, N};
    for (int i = 1; i <= M; ++ i) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
        vals.push_back(A[i]);
        vals.push_back(B[i]);
        vals.push_back(C[i]);
    }

    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

    for (int i = 1; i <= M; ++ i) {
        A[i] = lower_bound(vals.begin(), vals.end(), A[i]) - vals.begin() + 1;
        B[i] = lower_bound(vals.begin(), vals.end(), B[i]) - vals.begin() + 1;
        C[i] = lower_bound(vals.begin(), vals.end(), C[i]) - vals.begin() + 1;
    }

    N = vals.size();
    if (N == 1) {
        cout << "0\n";
        return 0;
    }

    lft.fill(INF);
    rgt.fill(INF);
    lft.update(1, 0);
    rgt.update(N, 0);

    lint ans = INF;
    for (int i = 1; i <= M; ++ i) {
        lint vL = lft.getMin(A[i], B[i]);
        lint vR = rgt.getMin(A[i], B[i]);
        ans = min(ans, vL + vR + D[i]);
        lft.update(C[i], vL + D[i]);
        rgt.update(C[i], vR + D[i]);
    }

    if (ans == INF)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}
