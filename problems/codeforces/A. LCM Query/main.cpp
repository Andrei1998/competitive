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

bool prime(int nr) {
    if (nr <= 1)
        return false;
    for (int i = 2; i * i <= nr; ++ i)
        if (nr % i == 0)
            return false;
    return true;
}

vector <int> primes;
int whichPrime[65];

const int MOD = 1000000000 + 7;

struct Lcm {
    long double val;
    int print;

    Lcm() {
        val = 0;
        print = 1;
    }

    friend bool operator<(const Lcm &a, const Lcm &b) {
        return a.val > b.val;
    }
};

const int NMAX = 20000 + 5;

int N, M;
int v[NMAX];
int nxt[65], cnt[18];

Lcm computeLcm() {
    Lcm ans;

    for (int i = 1; i <= 17; ++ i) {
        int aux = cnt[i];
        while (aux --) {
            ans.val += logl(primes[i - 1]);
            ans.print = (1LL * ans.print * primes[i - 1]) % MOD;
        }
    }

    return ans;
}

vector <Lcm> lcmAdd[NMAX];
vector <Lcm> lcmRemove[NMAX];

void addInterv(int st, int dr, const Lcm &l) {
    lcmAdd[st].push_back(l);
    lcmRemove[dr + 1].push_back(l);
}

multiset <Lcm> Set;

int anss[NMAX];

void sweep() {
    for (int i = 1; i <= N; ++ i) {
        for (auto it: lcmAdd[i])
            Set.insert(it);
        for (auto it: lcmRemove[i])
            Set.erase(Set.find(it));
        anss[i] = (*Set.rbegin()).print;
    }
}

int main()
{
    InputReader cin;

    for (int i = 1; i <= 60; ++ i)
        if (prime(i)) {
            primes.push_back(i);
            whichPrime[i] = primes.size();
        }

    cin >> N >> M;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];

    vector <int> relevants;
    for (int i = N; i; -- i) {
        memset(cnt, 0, sizeof cnt);
        nxt[v[i]] = i;

        relevants.clear();
        for (int j = 1; j <= 60; ++ j)
            if (nxt[j])
                relevants.push_back(nxt[j]);
        sort(relevants.begin(), relevants.end());
        relevants.push_back(N + 1);

        for (int k = 0; k + 1 < relevants.size(); ++ k) {
            int pos = relevants[k];
            int val = v[pos];
            for (int j = 2; j * j <= val; ++ j)
                if (val % j == 0) {
                    int _cnt = 0;
                    while (val % j == 0) {
                        val /= j;
                        ++ _cnt ;
                    }

                    cnt[whichPrime[j]] = max(cnt[whichPrime[j]], _cnt);
                }
            if (val > 1)
                cnt[whichPrime[val]] = max(cnt[whichPrime[val]], 1);

            addInterv(pos - i + 1, relevants[k + 1] - i, computeLcm());
        }
    }

    sweep();

    while (M --) {
        int l;
        cin >> l;
        cout << anss[l] << '\n';
    }
    return 0;
}
