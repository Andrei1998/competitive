#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 50000 + 5;
const int QMAX = 4 * NMAX;
const int RAD = 300;

vector <int> allEnds;

int N;
struct Kangaroo {
    int l, r;
    int where;

    bool operator<(const Kangaroo &arg) {
        return r < arg.r;
    }
} kan[NMAX];

int Q;
struct Query {
    int l, r;
    int ans;

    bool operator<(const Query &arg) {
        return r < arg.r;
    }
} qr[QMAX];

vector <int> kanBuckets[2 * NMAX / RAD];
bool cmpKan(const int &a, const int &b) {
    return kan[a] < kan[b];
}

vector <int> qrBuckets[2 * NMAX / RAD];
bool cmpQr(const int &a, const int &b) {
    return qr[a] < qr[b];
}

struct ArrayMantainer {
    int father[NMAX];
    int h[NMAX];
    int sz[NMAX];
    bool active[NMAX];
    int best;

    void init(int N) {
        for (int i = 1; i <= N; ++ i)
            father[i] = i, h[i] = active[i] = false, sz[i] = 1;
        best = 0;
    }

    int find(int node) {
        if (father[father[node]] != father[node])
            father[node] = find(father[node]);
        return father[node];
    }

    void unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b)
            return ;

        best = max(best, sz[a] + sz[b]);
        if (h[a] < h[b]) {
            father[a] = b;
            sz[b] += sz[a];
        }
        else {
            if (h[a] == h[b])
                ++ h[a];
            father[b] = a;
            sz[a] += sz[b];
        }
    }

    void activate(int node) {
        active[node] = true;
        if (!best)
            best = 1;
        if (active[node - 1])
            unite(node, node - 1);
        if (active[node + 1])
            unite(node, node + 1);
    }
} ar[RAD + 5];

int bucketLeft[2 * NMAX / RAD + 5];
int bucketRight[2 * NMAX / RAD + 5];
int whichBucket[2 * NMAX];
int buckets;

void precomputeBuckets() {
    for (int i = 1; i <= allEnds.size(); i += RAD) {
        bucketLeft[++ buckets] = i;
        whichBucket[i] = buckets;
        for (int j = i + 1; j <= allEnds.size() && j < i + RAD; ++ j) {
            bucketRight[buckets] = j;
            whichBucket[j] = buckets;
        }
    }
}

int main()
{
    freopen("data.in", "r", stdin);
    cin >> N >> Q;
    for (int i = 1; i <= N; ++ i) {
        cin >> kan[i].l >> kan[i].r;
        kan[i].where = i;
        allEnds.push_back(kan[i].l);
        allEnds.push_back(kan[i].r);
    }

    sort(allEnds.begin(), allEnds.end());
    allEnds.resize(unique(allEnds.begin(), allEnds.end()) - allEnds.begin());

    precomputeBuckets();

    for (int i = 1; i <= N; ++ i) {
        kan[i].l = lower_bound(allEnds.begin(), allEnds.end(), kan[i].l) - allEnds.begin() + 1;
        kan[i].r = lower_bound(allEnds.begin(), allEnds.end(), kan[i].r) - allEnds.begin() + 1;
        kanBuckets[whichBucket[kan[i].l]].push_back(i);
    }

    for (int i = 1; i <= Q; ++ i) {
        cin >> qr[i].l >> qr[i].r;
        qr[i].l = lower_bound(allEnds.begin(), allEnds.end(), qr[i].l) - allEnds.begin() + 1;
        qr[i].r = upper_bound(allEnds.begin(), allEnds.end(), qr[i].r) - allEnds.begin();
        if (qr[i].l <= qr[i].r) {
            qrBuckets[whichBucket[qr[i].l]].push_back(i);
            cout << "am bagat " << qr[i].l << ' ' << qr[i].r << endl;
        }
    }

    for (int i = 1; i <= RAD; ++ i)
        ar[i].init(N);

    for (int bucket = buckets; bucket; -- bucket) {
        sort(kanBuckets[bucket].begin(), kanBuckets[bucket].end(), cmpKan);
        for (auto it: kanBuckets[bucket])
            cout << kan[it].l << ' ' << kan[it].r << endl;
        sort(qrBuckets[bucket].begin(), qrBuckets[bucket].end(), cmpQr);

        vector <int> :: iterator it2 = kanBuckets[bucket].begin();
        for (vector <int> :: iterator it = qrBuckets[bucket].begin(); it != qrBuckets[bucket].end(); ++ it) {
            int L = qr[*it].l;
            int R = qr[*it].r;

            while (it2 != kanBuckets[bucket].end() && kan[*it2].r <= R) {
                int L = kan[*it2].l;
                for (int i = L; i >= bucketLeft[bucket]; -- i) {
                    ar[i - bucketLeft[bucket] + 1].activate(kan[*it2].where);
                    cout << "update pe " << i - bucketLeft[bucket] + 1 << endl;
                }
                ++ it2;
            }

            qr[*it].ans = ar[L - bucketLeft[bucket] + 1].best;
        }

        while (it2 != kanBuckets[bucket].end()) {
            int L = kan[*it2].l;
            for (int i = L; i >= bucketLeft[bucket]; -- i)
                ar[i - bucketLeft[bucket] + 1].activate(kan[*it2].where);
            ++ it2;
        }

        for (int i = 2; i <= RAD; ++ i)
            ar[i] = ar[1];
    }

    for (int i = 1; i <= Q; ++ i)
        cout << qr[i].ans << '\n';
    return 0;
}
