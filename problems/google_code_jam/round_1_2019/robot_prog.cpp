#include <bits/stdc++.h>

using namespace std;

void normalize(string &str) {
    for (auto &ch: str) {
        if (ch == 'R') {
            ch = '0';
        } else if (ch == 'P') {
            ch = '1';
        } else {
            ch = '2';
        }
    }
}

const char reals[] = {'R', 'P', 'S'};

string solve() {
    int N;
    cin >> N;
    vector <string> strs(N);
    for (int i = 0; i < N; ++i) {
        cin >> strs[i];
        normalize(strs[i]);
    }
    vector <bool> out(N);
    vector <int> where(N);
    string winner;
    while (true) {
        int freq[3] = {0};
        for (int i = 0; i < N; ++i) {
            if (!out[i]) {
                const int ch = strs[i][where[i]] - '0';
                ++freq[ch];
            }
        }
        cerr << "got " << endl;
        for (int i = 0; i < 3; ++i) {
            cerr << freq[i] << ' ';
        }
        cerr << endl;
        int cnt = 0, who = -1;
        for (int i = 0; i < 3; ++i) {
            if (freq[i] > 0) {
                ++cnt;
                who = i;
            }
        }
        if (cnt == 0) {
            return winner;
        } else if (cnt == 3) {
            return "IMPOSSIBLE";
        } else if (cnt == 1) {
            winner += reals[(who + 1) % 3];
            return winner;
        } else if (cnt == 2) {
            // Find who to take
            if (freq[2] == 0) {
                who = 1;
            } else if (freq[1] == 0) {
                who = 0;
            } else if (freq[0] == 0) {
                who = 2;
            }
            winner += reals[who];
            for (int i = 0; i < N; ++i) {
                if (!out[i]) {
                    const int ch = strs[i][where[i]] - '0';
                    if (ch != who) {
                        out[i] = true;
                    }
                }
            }
        }
        // Increment
        for (int i = 0; i < N; ++i) {
            if (!out[i]) {
                ++where[i];
                if (where[i] == static_cast <int>(strs[i].size())) {
                    where[i] = 0;
                }
            }
        }
    }
}

int main() {
    //freopen("data.in", "r", stdin);
    int T = 0;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": " << solve() << '\n';
    }
    return 0;
}
