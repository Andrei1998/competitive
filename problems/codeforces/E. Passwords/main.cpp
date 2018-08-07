#include <iostream>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>

using namespace std;

inline char cannonizeCharacter(char ch) {
    if (ch == '0')
        ch = 'o';
    else if (ch == '1')
        ch = 'i';
    else if (ch == '3')
        ch = 'e';
    else if (ch == '5')
        ch = 's';
    else if (ch == '7')
        ch = 't';
    if (islower(ch))
        ch = toupper(ch);
    return ch;
}

int labels[125];
map <char, int> MapLabels;

void precompute() {
    for (char ch = 'A'; ch <= 'Z'; ++ ch) {
        if (!MapLabels.count(cannonizeCharacter(ch)))
            MapLabels[cannonizeCharacter(ch)] = MapLabels.size() - 1;
        labels[ch] = MapLabels[cannonizeCharacter(ch)];
    }
    for (char ch = 'a'; ch <= 'z'; ++ ch) {
        if (!MapLabels.count(cannonizeCharacter(ch)))
            MapLabels[cannonizeCharacter(ch)] = MapLabels.size() - 1;
        labels[ch] = MapLabels[cannonizeCharacter(ch)];
    }
    for (char ch = '0'; ch <= '9'; ++ ch) {
        if (!MapLabels.count(cannonizeCharacter(ch)))
            MapLabels[cannonizeCharacter(ch)] = MapLabels.size() - 1;
        labels[ch] = MapLabels[cannonizeCharacter(ch)];
    }
}

const int LMAX = 20 + 2;
const int NMAX = 50 + 2;
const int STATESMAX = LMAX * NMAX;

struct Node {
    int father;
    int let;
    bool word;

    int alf[32];
    int fail;
} aho[STATESMAX];

int sz;

void addWord(const string &str) {
    int node = 1;
    for (auto it: str) {
        int ch = labels[it];
        if (aho[node].alf[ch] == 0) {
            aho[node].alf[ch] = ++ sz;
            aho[sz].father = node;
            aho[sz].let = ch;
        }
        node = aho[node].alf[ch];
    }
    aho[node].word = true;
}

queue <int> q;

void computeFails() {
    q.push(1);
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node != 1 && aho[node].father != 1) {
            int k = aho[aho[node].father].fail;
            while (k > 1 && !aho[k].alf[aho[node].let])
                k = aho[k].fail;

            if (aho[k].alf[aho[node].let])
                k = aho[k].alf[aho[node].let];
            aho[node].fail = k;
        }
        else
            aho[node].fail = 1;

        if (node != 1) {
            //aho[node].word |= aho[aho[node].father].word;
            aho[node].word |= aho[aho[node].fail].word;
        }

        for (int i = 0; i < 32; ++ i)
            if (aho[node].alf[i])
                q.push(aho[node].alf[i]);
            else {
                int k = aho[node].fail;
                while (k > 1 && !aho[k].alf[i])
                    k = aho[k].fail;
                if (aho[k].alf[i])
                    k = aho[k].alf[i];
                aho[node].alf[i] = k;
            }
    }
}

const int MOD = 1000000 + 3;

int dp[NMAX][STATESMAX][2][2][2];

void upd(int &where, int val) {
    where += val;
    if (where >= MOD)
        where -= MOD;
}

int main()
{
    //freopen("data.in", "r", stdin);
    precompute();

    sz = 1;

    /*addWord("abbb");
    addWord("bb");

    for (int i = 1; i <= 7; ++ i) {
        cout << "Node #" << i << " -> fail = " << aho[i].fail << endl;
        //for (int j = 0; j < 31; ++ j)
        //    if (aho[i].alf[j])
        //        cout << "Edge " << i << ' ' << aho[i].alf[j] << endl;
    }*/

    int A, B;
    int N;

    cin >> A >> B;
    cin >> N;

    string str;

    while (N --) {
        cin >> str;
        addWord(str);
    }

    computeFails();

    dp[0][1][0][0][0] = 1;
    for (int l = 0; l < B; ++ l)
        for (int state = 1; state <= sz; ++ state)
            if (!aho[state].word)
                for (int hasLower = 0; hasLower < 2; ++ hasLower)
                    for (int hasUpper = 0; hasUpper < 2; ++ hasUpper)
                        for (int hasDigit = 0; hasDigit < 2; ++ hasDigit) {
                            for (char ch = 'a'; ch <= 'z'; ++ ch)
                                upd(dp[l + 1][aho[state].alf[labels[ch]]][1][hasUpper][hasDigit], dp[l][state][hasLower][hasUpper][hasDigit]);
                            for (char ch = 'A'; ch <= 'Z'; ++ ch)
                                upd(dp[l + 1][aho[state].alf[labels[ch]]][hasLower][1][hasDigit], dp[l][state][hasLower][hasUpper][hasDigit]);
                            for (char ch = '0'; ch <= '9'; ++ ch)
                                upd(dp[l + 1][aho[state].alf[labels[ch]]][hasLower][hasUpper][1], dp[l][state][hasLower][hasUpper][hasDigit]);
                        }

    int ans = 0;
    for (int l = A; l <= B; ++ l)
        for (int state = 1; state <= sz; ++ state)
            if (!aho[state].word)
                upd(ans, dp[l][state][1][1][1]);
    cout << ans << '\n';
    return 0;
}
