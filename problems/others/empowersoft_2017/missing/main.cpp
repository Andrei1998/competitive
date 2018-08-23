#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const int NMAX = 100000 + 5;
const int QMAX = 2 * NMAX;

inline int getDigit(const string &str, int digit) {
    if (digit < str.size())
        return str[digit] - 'a' + 1;
    else
        return 0;
}

int N;
string str[NMAX];

int ord[NMAX];
int newOrd[NMAX];

int freq[27];
void radix(int digit) {
    memset(freq, 0, sizeof freq);
    for (int i = 1; i <= N; ++ i)
        ++ freq[getDigit(str[i], digit)];
    for (int i = 1; i <= 26; ++ i)
        freq[i] += freq[i - 1];

    for (int i = N; i; -- i)
        newOrd[freq[getDigit(str[ord[i]], digit)] --] = ord[i];
    memcpy(ord, newOrd, sizeof(newOrd));
}

const int MOD1 = 999999937;
const int MOD2 = 999999929;
const int C1 = 61;
const int C2 = 73;

int powC1[50];
int powC2[50];

const int MOD = 221987;

typedef long long int lint;
vector <pair <lint, int> > hs[MOD];

void add(const pair <int, int> &p, int index) {
    lint val = p.first * 1000000000LL + p.second;
    lint b = val % MOD;

    for (vector <pair <lint, int> > :: iterator it = hs[b].begin(); it != hs[b].end(); ++ it)
        if (it -> first == val)
            return ;
    hs[b].push_back(make_pair(val, index));
}

int doFind(const pair <int, int> &p) {
    lint val = p.first * 1000000000LL + p.second;
    lint b = val % MOD;

    for (vector <pair <lint, int> > :: iterator it = hs[b].begin(); it != hs[b].end(); ++ it)
        if (it -> first == val)
            return it -> second;
    return -1;
}

int main()
{
    ifstream cin("missing.in");
    ofstream cout("missing.out");

    powC1[0] = powC2[0] = 1;
    for (int i = 1; i < 50; ++ i) {
        powC1[i] = (1LL * powC1[i - 1] * C1) % MOD1;
        powC2[i] = (1LL * powC2[i - 1] * C2) % MOD2;
    }

    int Q;
    cin >> N >> Q;

    int n = 0, maxLen = 0;
    for (int i = 1; i <= N; ++ i) {
        cin >> str[++ n];
        if (str[n].size() > 40)
            -- n;
        else if (str[n].size() > maxLen)
            maxLen = str[n].size();
    }

    N = n;
    for (int i = 1; i <= N; ++ i)
        ord[i] = i;
    for (int i = maxLen - 1; i >= 0; -- i)
        radix(i);

    for (int i = 1; i <= N; ++ i) {
        const string &s = str[ord[i]];
        int sz = s.size();

        int h1Pref = 0, h1Suf = 0;
        int h2Pref = 0, h2Suf = 0;
        for (int j = 0; j < sz; ++ j) {
            h1Suf = (1LL * h1Suf * C1 + s[j] - 'a' + 1) % MOD1;
            h2Suf = (1LL * h2Suf * C2 + s[j] - 'a' + 1) % MOD2;
        }

        int val1, val2;
        for (int j = 0; j < sz; ++ j) {
            h1Suf = (h1Suf - 1LL * powC1[sz - j - 1] * (s[j] - 'a' + 1)) % MOD1;
            if (h1Suf < 0)
                h1Suf += MOD1;
            h2Suf = (h2Suf - 1LL * powC2[sz - j - 1] * (s[j] - 'a' + 1)) % MOD2;
            if (h2Suf < 0)
                h2Suf += MOD2;

            val1 = (1LL * h1Pref * powC1[sz - j - 1] + h1Suf) % MOD1;
            val2 = (1LL * h2Pref * powC2[sz - j - 1] + h2Suf) % MOD2;

            add(make_pair(val1, val2), ord[i]);

            h1Pref = (1LL * h1Pref * C1 + s[j] - 'a' + 1) % MOD1;
            h2Pref = (1LL * h2Pref * C2 + s[j] - 'a' + 1) % MOD2;
        }
    }

    string s;
    for (int i = 1; i <= Q; ++ i) {
        cin >> s;
        int h1 = 0;
        int h2 = 0;
        for (int j = 0; j < s.size(); ++ j) {
            h1 = (1LL * C1 * h1 + s[j] - 'a' + 1) % MOD1;
            h2 = (1LL * C2 * h2 + s[j] - 'a' + 1) % MOD2;
        }

        int who = doFind(make_pair(h1, h2));
        if (who == -1)
            cout << "-1\n";
        else
            cout << str[who] << '\n';
    }
    return 0;
}
