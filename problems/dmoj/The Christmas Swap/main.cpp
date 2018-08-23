#include <iostream>
#include <algorithm>
#include <string>

#define lint long long int
using namespace std;

int N, K;
string str;

const int NMAX = 1e5 + 5;
int cnt0[NMAX];
lint sum0[NMAX];

lint moveBackAll(int st, int dr) {
    lint ssum = sum0[dr] - sum0[st - 1];
    int ccnt0 = cnt0[dr] - cnt0[st - 1];

    return ssum - st * ccnt0 - ccnt0 * (ccnt0 - 1LL) / 2;
}

lint moveForwardAll(int st, int dr) {
    if (dr < st)
        return 0;
    lint ssum = sum0[dr] - sum0[st - 1];
    int ccnt0 = cnt0[dr] - cnt0[st - 1];

    return dr * ccnt0 - ssum - ccnt0 * (ccnt0 - 1LL) / 2;
}

lint getCost(int st, int where, int dr) {
    return moveBackAll(st, where) +
           moveForwardAll(where + 1, dr);
}

bool works(int l) {
    int cnt = 0;

    int j = 0;
    int where = 1;

    for (int i = 1; i <= N; ++ i) {
        while (j + 1 <= N && cnt < l) {
            ++ j;
            cnt += (str[j] == '1');
        }

        if (str[i] == '1') {
            if (cnt < l)
                return false;

            if (where < i)
                where = i;

            while (where + 1 <= j && getCost(i, where, j) >= getCost(i, where + 1, j))
                ++ where;

            if (getCost(i, where, j) <= K)
                return true;
        }

        cnt -= (str[i] == '1');
    }

    return false;
}

int solve() {
    for (int i = 1; i <= N; ++ i) {
        cnt0[i] = cnt0[i - 1] + (str[i] == '0');
        sum0[i] = sum0[i - 1] + (str[i] == '0') * i;
    }

    int cnt = 0;
    for (auto it: str)
        cnt += (it == '1');

    int st = 1;
    int dr = cnt;
    int mid;
    int ans = 0;

    while (st <= dr) {
        mid = (st + dr) >> 1;
        if (works(mid)) {
            ans = mid;
            st = mid + 1;
        }
        else
            dr = mid - 1;
    }

    return ans;
}

int main() {
    cin >> N >> K;
    cin >> str;

    str = " " + str;

    cout << solve();

    for (auto &it: str)
        it ^= 1;

    cout << ' ' << solve() << '\n';
    return 0;
}
