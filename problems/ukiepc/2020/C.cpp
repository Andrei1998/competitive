#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10000 + 5;

int v[NMAX];
int ans[NMAX];

int main() {
    int N;
    int pb;
    cin >> N >> pb;
    for (int i = 1; i <= N; ++i) {
        cin >> v[i];
    }
    int cnt_zeros = 0;
    int least_zero = N + 1;
    for (int i = 1; i <= N; ++i) {
        if (v[i] == 0) {
            ++cnt_zeros;
            least_zero = min(least_zero, i);
        }
    }

    int curent_pb = pb;
    if (least_zero > 1) {
        ans[1] = pb;
        for (int i = 2; i < least_zero; ++i) {
            if (v[i] < v[i - 1]) {
                --curent_pb;
            }
            ans[i] = curent_pb;
        }
    } else {
        curent_pb = 1;
    }
    if (curent_pb == 1) {
        for (int i = 1; i <= N; ++i) {
            cout << ans[i] << '\n';
        }
    } else {
        cout << "ambiguous" << endl;
    }
    return 0;
}