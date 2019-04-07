#include <bits/stdc++.h>

using namespace std;

int N, B, F;

string query(const string &str) {
    assert(F-- > 0);
    string actual = str;
    actual.resize(N);
    cout << actual << endl;
    string ans;
    cin >> ans;
    for (int i = N; i < str.size(); ++i) {
        ans += str[i];
    }
    return ans;
}

struct Interv {
    int l, r, bad;
    Interv(): l(-1), r(-1), bad(-1) {}
    Interv(int _l, int _r, int _bad): l(_l), r(_r), bad(_bad) {}
};

const int SZ = 1024;

void solve() {
    cin >> N >> B >> F; F = 5;
    
    // Prepare initial query
    string q(SZ, '?');
    for (int i = 0, h = 0; i < SZ; i += 16, h ^= 1) {
        for (int j = 0; j < 16; ++j) {
            q[i + j] = '0' + h;
        }
    }

    // Ask initial query
    const string ans_ = query(q);
    
    // Prepare initial intervals
    vector <Interv> intervs;
    for (int i = 0, h = 0, ptr = 0; i < SZ; i += 16, h ^= 1) {
        int cnt = 0;
        while (ptr < SZ && ans_[ptr] == '0' + h) {
            ++ptr, ++cnt;
        }
        intervs.emplace_back(i, i + 15, 16 - cnt);
    }

    while (true) {
        // If all intervals are singletons
        if (intervs[0].l == intervs[0].r) {
            break;
        }

        // Prepare query
        string q(SZ, '?');
        for (auto interv: intervs) {
            const int &l = interv.l, &r = interv.r, &bad = interv.bad;
            const int mid = (l + r) / 2;
            for (int i = l; i <= mid; ++i) {
                q[i] = '0';
            }
            for (int i = mid + 1; i <= r; ++i) {
                q[i] = '1';
            }
        }

        // Ask query
        const string ans = query(q);
        vector <Interv> new_intervs;
        
        // Split
        int ptr = 0;
        for (auto interv: intervs) {
            const int &l = interv.l, &r = interv.r, &bad = interv.bad;
            const int mid = (l + r) / 2;
            int freq[2] = {0};
            const int half = (r - l + 1) / 2;
            int cnt = 2 * half - bad;
            while (cnt--) {
                ++freq[ans[ptr++] - '0'];
            }
            new_intervs.emplace_back(l, mid, half - freq[0]);
            new_intervs.emplace_back(mid + 1, r, half - freq[1]);
        }
        intervs = move(new_intervs);
    }

    // Print
    vector <int> ans;
     for (auto interv: intervs) {
        const int &l = interv.l, &r = interv.r, &bad = interv.bad;
        if (bad == 1) {
            ans.push_back(l);
        }
    }
    assert(ans.size() == B);
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i];
        if (i + 1 < ans.size()) {
            cout << " ";
        } else {
            cout << endl; 
        }
    }
    int verdict; cin >> verdict;
    assert(verdict == 1);
}

int main() {
    //freopen("data.in", "r", stdin);
    int T = 0;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}