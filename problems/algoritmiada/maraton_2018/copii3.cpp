#include <bits/stdc++.h>

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

    inline InputReader &operator >>(string &str) {
        str = "";
        while(buffer[cursor] < '0' || buffer[cursor] > '9') {
            advance();
        }
        while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
            str += buffer[cursor];
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

const int NMAX = 320000 + 5;

int N;
string str;
int zeroes[NMAX];
int zeroesSz;
int ones[NMAX];
int onesSz;

typedef long long int lint;
lint sumPosZero[NMAX];
lint sumPosOnes[NMAX];

int nextZero[NMAX];
int prevZero[NMAX];
int nextOne[NMAX];
int prevOne[NMAX];

lint getInCost(int l, int m, int r) {
    //assert(0 <= l - 1 && l - 1 <= m && m <= r && r <= onesSz);
    const lint sumL = sumPosOnes[m] - sumPosOnes[l - 1];
    const lint sumR = -sumPosOnes[r] + sumPosOnes[m];
    return sumL + sumR;
}

lint getOutCost(int l, int r, int cnt1, int cnt2) {
    //assert(l - cnt1 + 1 >= 1 && r + cnt2 - 1 <= zeroesSz);
    const lint sumL = -sumPosZero[l] + sumPosZero[l - cnt1];
    const lint sumR = sumPosZero[r + cnt2 - 1] - sumPosZero[r - 1];
    return sumL + sumR;
}

lint solve(int l, int r) {
    const int a = nextOne[l], b = prevOne[r];
    if (a > b)
        return 0;

    const int c = prevZero[l - 1], d = nextZero[r + 1];
    const int rBound = min(a + c - 1, b);
    const int lBound = max(a - 1, b - (zeroesSz - d) - 1);
    if (lBound > rBound)
        return -1;

    auto getCost = [&](const int i) {
        return getInCost(a, i, b) + getOutCost(c, d, i - a + 1, b - i);
    };

    l = lBound, r = rBound;
    while (r - l > 10) {
        int mid1 = (2 * l + r) / 3;
        int mid2 = (l + 2 * r) / 3;
        const lint c1 = getCost(mid1);
        const lint c2 = getCost(mid2);
        if (c1 < c2)
            r = mid2;
        else
            l = mid1;
    }

    lint best = 1E18;
    for (int i = l; i <= r; ++ i)
        best = min(best, getCost(i));
    return best;
}

int main() {
    InputReader cin("copii3.in");
    ofstream cout("copii3.out");

    int Q;
    cin >> N >> Q;
    cin >> str;

    str = " " + str;
    for (int i = 1; i <= N; ++ i) {
        if (str[i] == '0')
            zeroes[++ zeroesSz] = i;
        else
            ones[++ onesSz] = i;
    }

    for (int i = 1; i <= zeroesSz; ++ i)
        sumPosZero[i] = sumPosZero[i - 1] + zeroes[i];
    for (int i = 1; i <= onesSz; ++ i)
        sumPosOnes[i] = sumPosOnes[i - 1] + ones[i];

    int one = 0, zero = 0;
    for (int i = 1; i <= N; ++ i) {
        if (str[i] == '0')
            ++ zero;
        else
            ++ one;
        prevZero[i] = zero, prevOne[i] = one;
    }
    ++ one, ++ zero;
    nextZero[N + 1] = zero, nextOne[N + 1] = one;
    for (int i = N; i; -- i) {
        if (str[i] == '0')
            -- zero;
        else
            -- one;
        nextZero[i] = zero, nextOne[i] = one;
    }

    while (Q --) {
        int l, r;
        cin >> l >> r;
        cout << solve(l, r) << '\n';
    }
    return 0;
}
