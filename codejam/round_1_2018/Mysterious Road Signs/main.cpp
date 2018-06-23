#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100000 + 5;
const int VALMAX = 1000000 + 5;

int N;
int A[NMAX], B[NMAX];

vector <int> freqA[2 * VALMAX];
vector <int> freqB[2 * VALMAX];

map <pair <int, int>, vector <int> > freqAB;

int getCnt(int l, int r, const vector <int> &v) {
    return upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l);
}

int getCntMap(int l, int r, pair <int, int> val) {
    if (!freqAB.count(val))
        return 0;
    else
        return getCnt(l, r, freqAB[val]);
}

int getFirstWithoutA(int l, int r, int val) {
    int st = l;
    int dr = r;
    int ans = r + 1;
    while (st <= dr) {
        const int mid = (st + dr) / 2;
        if (getCnt(l, mid, freqA[val]) == mid - l + 1)
            st = mid + 1;
        else {
            ans = mid;
            dr = mid - 1;
        }
    }
    return ans;
}

int getFirstWithoutB(int l, int r, int val) {
    int st = l;
    int dr = r;
    int ans = r + 1;
    while (st <= dr) {
        const int mid = (st + dr) / 2;
        if (getCnt(l, mid, freqB[val]) == mid - l + 1)
            st = mid + 1;
        else {
            ans = mid;
            dr = mid - 1;
        }
    }
    return ans;
}

int getFirstWithout(int l, int r, int v1, int v2) {
    if (v2 < v1)
        swap(v1, v2);
    int st = l;
    int dr = r;
    int ans = r + 1;
    while (st <= dr) {
        const int mid = (st + dr) / 2;
        if (getCnt(l, mid, freqA[v1]) + getCnt(l, mid, freqB[v2]) - getCntMap(l, mid, make_pair(v1, v2)) == mid - l + 1)
            st = mid + 1;
        else {
            ans = mid;
            dr = mid - 1;
        }
    }
    return ans;

}

void updAns(int &ans, int &cnt, int nr) {
    if (nr > ans)
        ans = nr, cnt = 1;
    else if (nr == ans)
        ++ cnt;
}

void read() {
    cin >> N;
    for (int i = 1; i <= N; ++ i) {
        int d, a, b;
        cin >> d >> a >> b;
        A[i] = d - b + 1000000;
        B[i] = d + a + 1000000;
    }
}

void solve() {
    for (int i = 1; i <= N; ++ i) {
        freqA[A[i]].push_back(i);
        freqB[B[i]].push_back(i);
        freqAB[make_pair(A[i], B[i])].push_back(i);
    }

    int ans = -1, cnt = -1;
    for (int i = 1; i <= N; ++ i) {
        int bestL = 0;

        // Try 1
        int X = A[i];
        int pos = getFirstWithoutA(i, N, X);
        if (pos == N + 1)
            bestL = max(bestL, N - i + 1);
        else {
            int Y = B[pos];
            int pos2 = getFirstWithout(i, N, X, Y);
            bestL = max(bestL, pos2 - i);
        }

        // Try 2
        int Y = B[i];
        pos = getFirstWithoutB(i, N, Y);
        if (pos == N + 1)
            bestL = max(bestL, N - i + 1);
        else {
            int X = A[pos];
            int pos2 = getFirstWithout(i, N, X, Y);
            bestL = max(bestL, pos2 - i);
        }

        updAns(ans, cnt, bestL);
    }
    cout << ans << ' ' << cnt << '\n';

    freqAB.clear();
    for (int i = 0; i < 2 * VALMAX; ++ i)
        freqA[i].clear(), freqB[i].clear();
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    //freopen("data.in", "r", stdin);

    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i) {
        cout << "Case #" << i << ": ";
        read();
        solve();
    }
    return 0;
}
