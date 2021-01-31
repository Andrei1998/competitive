#include <bits/stdc++.h>

using namespace std;

string from_ll(long long int nr) {
    string str;
    do {
        str += (char)('0' + nr % 10);
        nr /= 10;
    } while (nr > 0);
    reverse(str.begin(), str.end());
    return str;
}

bool is_paly(const long long int nr) {
    string str = from_ll(nr);
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

long long int to_ll(const string& str) {
    long long int ans = 0;
    for (int i = 0; i < str.size(); ++i) {
        ans *= 10;
        ans += (str[i] - '0');
    }
    return ans;
}

vector<long long int> sol;
void solve(const long long int nr) {
    // Done.
    if (nr == 0) return;
    if (nr <= 9) {
        sol.push_back(nr);
        return;
    }
    string str = from_ll(nr);
    const int n = str.size();
    string subtr;
    if (str[0] == '1' && str[n - 1] == '0') {
        for (int i = 0; i + 1 < n; ++i) {
            subtr += '9';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            subtr += '0';
        }
        for (int i = 0; i <= n - i - 1; ++i) {
            subtr[i] = subtr[n - i - 1] = str[i];
            if (to_ll(subtr) > nr) {
                assert(str[i] != '0');
                subtr[i] = str[i] - 1;
                subtr[n - i - 1] = str[i] - 1;
                for (int j = i + 1; j < n - i - 1; ++j) {
                    subtr[j] = '9';
                }
                break;
            }
        }
    }
    sol.push_back(to_ll(subtr));
    solve(nr - to_ll(subtr));
}

int main() {
    long long int nr;
    cin >> nr;
    solve(nr);
    cout << sol.size() << endl;
    long long int sum = 0;
    for (int i = 0; i < sol.size(); ++i) {
        sum += sol[i];
        assert(is_paly(sol[i]));
        cout << sol[i] << endl;
    }
    assert(sum == nr);
    return 0;
}