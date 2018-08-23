#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <cstdlib>

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
const int MMAX = 3 * 100000 + 5;
const int INF = 2e9 + 15;

//vector <int> allVals;

int N;
int v[NMAX];

int freq[NMAX];
int t[NMAX];
int st[NMAX];
int dr[NMAX];

const int RAD = 900;

int whichBucket[NMAX];
int bucketLeft[NMAX];
int bucketRight[NMAX];
int buckets;

void precompute() {
    for (int i = 1; i <= N; i += RAD) {
        bucketLeft[++ buckets] = i;
        for (int j = i; j < i + RAD && j <= N; ++ j) {
            bucketRight[buckets] = j;
            whichBucket[j] = buckets;
        }
    }
}

struct Query {
    int l, r;
    int pos;

    Query(int _l = 0, int _r = 0, int _pos = 0):
        l(_l), r(_r), pos(_pos) {}

    friend bool operator<(const Query &a, const Query &b) {
        return a.r < b.r;
    }
};

vector <Query> queries[NMAX / RAD + 5];

int anss[MMAX];

set <int> Set;

int ifInsert(int val) {
    int ans = INF;
    set <int> :: iterator it = Set.lower_bound(val);
    if (it != Set.end())
        ans = min(ans, *it - val);
    if (it != Set.begin()) {
        -- it;
        ans = min(ans, val - *it);
    }
    return ans;
}

int dp[RAD + 5][RAD + 5];

int main()
{
    InputReader cin;
    //freopen("data.in", "r", stdin);

    cin >> N;
    precompute();

    for (int i = 1; i <= N; ++ i) {
        cin >> v[i];
        //allVals.push_back(v[i]);
    }

    /*sort(allVals.begin(), allVals.end());
    allVals.resize(unique(allVals.begin(), allVals.end()) - allVals.begin());
    for (int i = 1; i <= N; ++ i)
        v[i] = lower_bound(allVals.begin(), allVals.end(), v[i]) - allVals.begin() + 1;
    int sz = allVals.size();*/

    int M = 0;
    cin >> M;

    for (int i = 1; i <= M; ++ i) {
        int l, r;
        cin >> l >> r;
        queries[whichBucket[l]].push_back(Query(l, r, i));
    }

    //stack <int> stk;
    for (int bucket = 1; bucket <= buckets; ++ bucket)
        if (!queries[bucket].empty()) {
            sort(queries[bucket].begin(), queries[bucket].end());

            //Init vals
            /*for (int i = 1; i <    ans = min(ans, *it - val);
    = sz; ++ i)
                t[i] = N + 1;

            //Prepare for stack
            for (int i = bucketLeft[bucket]; i <= N; ++ i)
                t[v[i]] = min(t[v[i]], i);

            //Stack l -> r
            for (int i = 1; i <= sz; ++ i) {
                while (!stk.empty() && t[stk.top()] > t[i])
                    stk.pop();
                if (stk.empty())
                    st[i] = 0;
                else
                    st[i] = stk.top();
                stk.push(i);
            }

            while (!stk.empty())
                stk.pop();

            //Stack r -> l
            for (int i = sz; i; -- i) {
                while (!stk.empty() && t[stk.top()] > t[i])
                    stk.pop();
                if (stk.empty())
                    dr[i] = N + 1;
                else
                    dr[i] = stk.top();
                stk.push(i);
            }*/

            int len = bucketRight[bucket] - bucketLeft[bucket] + 1;
            for (int i = len; i; -- i) {
                dp[i][i] = INF;
                for (int j = i + 1; j <= len; ++ j)
                    dp[i][j] = min(min(dp[i + 1][j], dp[i][j - 1]), abs(v[bucketLeft[bucket] + i - 1] - v[bucketLeft[bucket] + j - 1]));
            }

            Set.clear();
            int globAns = INF;
            int nxt = bucketRight[bucket] + 1;

            for (auto it: queries[bucket])
                if (whichBucket[it.r] == bucket) {
                    int l = it.l - bucketLeft[bucket] + 1;
                    int r = it.r - bucketLeft[bucket] + 1;
                    anss[it.pos] = dp[l][r];
                }
                else {
                    int l = it.l - bucketLeft[bucket] + 1;
                    int ans = dp[l][len];

                    while (nxt <= it.r) {
                        if (Set.count(v[nxt]))
                            goto done;

                        globAns = min(globAns, ifInsert(v[nxt]));
                        Set.insert(v[nxt]);
                        nxt ++;
                    }

                    for (int i = it.l; i <= bucketRight[bucket]; ++ i)
                        ans = min(ans, ifInsert(v[i]));
                    anss[it.pos] = min(ans, globAns);
                }
            done:;
        }

    for (int i = 1; i <= M; ++ i)
        cout << anss[i] << '\n';
    return 0;
}
