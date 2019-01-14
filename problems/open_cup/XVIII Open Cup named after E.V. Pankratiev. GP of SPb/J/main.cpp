#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2 * 100000 + 5;
typedef long long int lint;

int N;
int a[NMAX], b[NMAX];

lint cnt_at_most(lint bound) {
    lint ans = 0;
    int j = N;
    for (int i = 1; i <= N && j; ++i) {
        while (j >= 1 && a[i] + b[j] > bound)
            --j;
        ans += j;
    }
    return ans;
}

lint number_at(lint pos) {
    lint l = 0;
    lint r = 2E9 + 15;
    lint ans = r + 1;
    while (l <= r) {
        const lint mid = (l + r) / 2;
        if (cnt_at_most(mid) >= pos) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return ans;
}

void numbers_between(vector <lint> &ans, lint from, lint to) {
    int i = N + 1, j = N;
    for (int k = 1; k <= N; ++k) {
        while (i - 1 >= 1 && a[k] + b[i - 1] >= from)
            --i;
        while (j >= 1 && a[k] + b[j] > to)
            --j;
        for (int p = i; p <= j; ++p)
            ans.push_back(a[k] + b[p]);
    }
}

int main() {
    //freopen("data.in", "r", stdin);
    ios_base :: sync_with_stdio(false);

    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> a[i];
    for (int i = 1; i <= N; ++i)
        cin >> b[i];
    sort(a + 1, a + N + 1);
    sort(b + 1, b + N + 1);

    const lint ord1 = N * (N - 1LL) / 2 + 1;
    const lint ord2 = N * (N + 1LL) / 2;

    const lint n1 = number_at(ord1);
    const lint n2 = number_at(ord2);

    if (n1 == n2) {
        for (lint i = ord1; i <= ord2; ++i)
            cout << n1 << " \n"[i == ord2];
        return 0;
    }

    vector <lint> ans;
    numbers_between(ans, n1 + 1, n2 - 1);

    const lint actual_pos_n1 = cnt_at_most(n1);
    for (lint i = ord1; i <= actual_pos_n1; ++i)
        ans.push_back(n1);
    while (ans.size() < N)
        ans.push_back(n2);
    assert(ans.size() == N);
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " \n"[i + 1 == ans.size()];
    return 0;
}
