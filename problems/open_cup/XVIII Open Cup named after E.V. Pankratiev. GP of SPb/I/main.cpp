#include <bits/stdc++.h>

using namespace std;

int N, cnt;
bool ask(int i, int j) {
    //cout << "am " << i << ' ' << j << endl;
    ++cnt;
    assert(1 <= i && i <= N);
    assert(1 <= j && j <= N);
    cout << "? " << i << ' ' << j << endl;
    cout.flush();
    int ans;
    cin >> ans;
    return ans;
}

const int NMAX = 500 + 5;
int v[NMAX], aux[NMAX];

void srt(int l, int r) {
    if (r <= l)
        return;
    const int mid = (l + r) / 2;
    srt(l, mid);
    srt(mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid || j <= r) {
        if (i <= mid && (j > r || (j <= r && ask(v[i], v[j]))))
            aux[++k] = v[i++];
        else
            aux[++k] = v[j++];
    }
    for (int i = l; i <= r; ++i)
        v[i] = aux[i - l + 1];

    if (ask(v[r], v[l])) {
        cout << "! NO" << endl;
        cout << r - l + 1;
        for (int i = l; i <= r; ++i)
            cout << ' ' << v[i];
        cout << endl;
        exit(0);
    }
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; ++i)
        v[i] = i;
    srt(1, N);
    //cout << cnt << endl;

    cout << "! YES" << endl;
    for (int i = 1; i <= N; ++i)
        cout << v[i] << " \n"[i == N];
    cout.flush();
    return 0;
}
