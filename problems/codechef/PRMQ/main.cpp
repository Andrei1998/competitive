#include <iostream>
#include <vector>

using namespace std;

const int VALMAX = 1000000 + 5;
vector <int> primes;
int low[VALMAX];

void sieve() {
    for (int i = 2; i <= 1000000; ++ i) {
        if (!low[i]) {
            primes.push_back(i);
            low[i] = i;
        }

        for (int j = 0; j < primes.size() && primes[j] <= low[i] && primes[j] * i <= 1000000; ++ j)
            low[primes[j] * i] = primes[j];
    }
}

struct Query {
    int l, r;
    int sign;
    int pos;
    Query(int _l = 0, int _r = 0, int _sign = 0, int _pos = 0):
        l(_l), r(_r), sign(_sign), pos(_pos) {}
};

const int NMAX = 100000 + 5;

int N;
int a[NMAX];
vector <Query> queries[VALMAX];
vector <int> event[VALMAX];

inline int lsb(int node) {
    return node & (-node);
}

int aib[NMAX];

void update(int where) {
    for (; where <= N; where += lsb(where))
        ++ aib[where];
}

int query(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        ans += aib[where];
    return ans;
}

int anss[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    sieve();

    cin >> N;

    for (int i = 1; i <= N; ++ i) {
        cin >> a[i];
        while (a[i] != 1) {
            event[low[a[i]]].push_back(i);
            a[i] /= low[a[i]];
        }
    }

    int Q = 0;
    cin >> Q;

    for (int i = 1; i <= Q; ++ i) {
        int L, R, X, Y;
        cin >> L >> R >> X >> Y;
        queries[X - 1].push_back(Query(L, R, -1, i));
        queries[Y].push_back(Query(L, R, 1, i));
    }

    for (int i = 0; i < VALMAX; ++ i) {
        for (auto it: event[i])
            update(it);
        for (auto it: queries[i])
            anss[it.pos] += it.sign * (query(it.r) - query(it.l - 1));
    }

    for (int i = 1; i <= Q; ++ i)
        cout << anss[i] << '\n';
    return 0;
}
