#include <bits/stdc++.h>

using namespace std;

//#define MOCK

string mock;
void build_mock() {
    string str = "ABCDE";
    vector <string> strings;
    do {
        strings.push_back(str);
    } while (next_permutation(str.begin(), str.end()));
    mt19937 gen;
    shuffle(strings.begin(), strings.end(), gen);
    cerr << "MISSING is " << strings.back() << endl;
    strings.pop_back();
    for (const auto &it: strings) {
        mock += it;
    }
}

int asks;
char ask(int lin, int col) {
    ++asks;
    assert(asks <= 150);
    cout << 5 * lin + col + 1 << endl;
    char ch;
#ifndef MOCK
    cin >> ch;
#else
    ch = mock[5 * lin + col];
#endif // MOCK
    return ch;
}

void solve() {
    const int N = 119;
    vector <bool> out(N);
    vector <string> answers(N, "?????");
    vector <bool> used(5);
    string res;
    for (int round = 0, nec = 24; round < 5; ++round) {
        // Query all
        int freq[5] = {0};
        for (int i = 0; i < N; ++i) {
            if (!out[i]) {
                answers[i][round] = ask(i, round);
                ++freq[answers[i][round] - 'A'];
            }
        }
        // Find missing letter
        int who = -1;
        for (int i = 0; i < 5; ++i) {
            if (!used[i] && freq[i] < nec) {
                who = i;
            }
        }
        assert(who != -1);
        used[who] = true;
        res += (who + 'A');
        for (int i = 0; i < N; ++i) {
            if (!out[i]) {
                if (answers[i][round] != res[round]) {
                    out[i] = true;
                }
            }
        }
        if (round < 4) {
            nec /= (4 - round);
        }
    }
    cout << res << endl;
    string ver;
    cin >> ver;
    assert(ver == "Y");
}

int main() {
    int T = 1, F = 150;
#ifdef MOCK
    build_mock();
    //cerr << mock << endl;
#else
    cin >> T >> F;
#endif // MOCK
    for (int t = 1; t <= T; ++t) {
        asks = 0;
        solve();
    }
    return 0;
}
