#include <iostream>
#include <cstdio>
#include <deque>

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

const int NMAX = 100000 + 5;
const int KMAX = 10 + 5;

typedef long long int lint;
const lint INF = 1E18;

int N, K;
int w[NMAX];
int s[NMAX];
lint s2[NMAX];

lint dpBrute[KMAX][NMAX];

lint c(int j, int i) {
    return s2[i] - s2[j] - 1LL * j * s[i] + 1LL * j * s[j];
}

lint dp[KMAX][NMAX];
lint ck(int k, int j, int i) {
    return dp[k - 1][j - 1] + c(j, i);
}

lint ckB(int k, int j, int i) {
    return dpBrute[k - 1][j - 1] + c(j, i);
}

void brute() {
    for (int i = 1; i <= N; ++ i)
        dpBrute[1][i] = c(1, i);
    for (int k = 2; k <= K; ++ k) {
        for (int i = k; i <= N; ++ i) {
            dpBrute[k][i] = INF;
            for (int j = k; j <= i; ++ j)
                dpBrute[k][i] = min(dpBrute[k][i], ckB(k, j, i));
        }
    }
}


int inters(int k, int j1, int j2) {
    /*int st = j2;
    int dr = N;
    int ans = N + 1;

    while (st <= dr) {
        int mid = (st + dr) >> 1;
        if (ck(k, j1, mid) >= ck(k, j2, mid)) {
            ans = mid;
            dr = mid - 1;
        }
        else
            st = mid + 1;
    }

    return ans;*/

    lint A = -(dp[k - 1][j1 - 1] - dp[k - 1][j2 - 1] + s2[j2] - s2[j1] + 1LL * j1 * s[j1] - 1LL * j2 * s[j2]);
    int B = (j2 - j1);

    //Ceil
    return (A + B - 1) / B;
}

deque <int> dq;
void solve() {
    for (int i = 1; i <= N; ++ i)
        dp[1][i] = c(1, i);
    for (int k = 2; k <= K; ++ k) {
        dq.clear();
        for (int i = k; i <= N; ++ i) {
            //j from [k - 1, i]
            //Add i
            while (dq.size() > 1) {
                int j2 = dq.back();
                dq.pop_back();
                int j1 = dq.back();

                int t1 = inters(k, j1, i);
                int t2 = inters(k, j2, i);

                if (t1 <= t2) {
                    dq.push_back(j2);
                    break;
                }
            }
            dq.push_back(i);

            //Rectify
            while (dq.size() > 1) {
                int j1 = dq.front();
                dq.pop_front();
                int j2 = dq.front();

                if (ck(k, j1, i) < ck(k, j2, i)) {
                    dq.push_front(j1);
                    break;
                }
            }

            //Compute
            int j = dq.front();
            dp[k][i] = ck(k, j, i);
        }
    }
}

int main()
{
    InputReader cin;

    cin >> N >> K;
    for (int i = 1; i <= N; ++ i)
        cin >> w[i];

    for (int i = 1; i <= N; ++ i) {
        s[i] = s[i - 1] + w[i];
        s2[i] = s2[i - 1] + 1LL * i * w[i];
    }

    //brute();
    solve();

    //cout << dpBrute[K][N];
    cout << dp[K][N] << endl;
    return 0;
}
