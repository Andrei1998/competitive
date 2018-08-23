#include <fstream>

using namespace std;

const int NMAX = 100000 + 5;

typedef long long int lint;

inline int lsb(int node) {
    return node & (-node);
}

int N;
int aib[NMAX];

void init() {
    for (int i = 1; i <= N; ++ i)
        aib[i] = 0;
}

void add(int where) {
    for (; where <= N; where += lsb(where))
        ++ aib[where];
}

void remove(int where) {
    for (; where <= N; where += lsb(where))
        -- aib[where];
}

int query(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        ans += aib[where];
    return ans;
}

int queryLess(int where) {
    return query(where);
}

int queryMore(int where) {
    return query(N) - query(where);
}

int _a[NMAX];
int _b[NMAX];

int a[2 * NMAX];
int b[NMAX];
int where[NMAX];

lint solve() {
    init();
    for (int i = 1; i <= N; ++ i)
        where[b[i]] = i;
    for (int i = 1; i <= N; ++ i)
        a[i] = where[a[i]];
    for (int i = 1; i <= N; ++ i)
        a[i + N] = a[i];

    lint ans = 1LL << 62;

    lint current = 0;
    for (int i = 1; i <= N; ++ i) {
        current += queryMore(a[i]);
        add(a[i]);
    }

    for (int i = N + 1; i <= 2 * N; ++ i) {
        current -= queryLess(a[i - N] - 1);
        remove(a[i - N]);
        current += queryMore(a[i]);
        add(a[i]);

        if (current < ans)
            ans = current;
    }

    return ans;
}

int main()
{
    ifstream cin("mincross.in");
    ofstream cout("mincross.out");

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> _a[i];
    for (int i = 1; i <= N; ++ i)
        cin >> _b[i];

    for (int i = 1; i <= N; ++ i) {
        a[i] = _a[i];
        b[i] = _b[i];
    }
    lint ans = solve();

    for (int i = 1; i <= N; ++ i) {
        a[i] = _b[i];
        b[i] = _a[i];
    }
    ans = min(ans, solve());

    cout << ans << '\n';
    return 0;
}
