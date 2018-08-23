#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

int main() {
    int N;
    cin >> N;
    vector <int> a(N);
    for (int i = 0; i < N; ++ i)
        cin >> a[i];

    for (int cnt = 1; cnt <= 100; ++ cnt) {
        bool fine = true;
        for (int i = 0; i < N && fine; ++ i) {
            const int val = a[i];
            bool found = false;
            for (int j = 0; j <= cnt; ++ j)
                if ((100 * j + cnt / 2) / cnt == val)
                    found = true;
            if (!found)
                fine = false;
        }
        if (fine) {
            cout << cnt << endl;
            break;
        }
    }
    return 0;
}
