#include <bits/stdc++.h>

using namespace std;

vector <int> v;

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < 3 * N; ++ i) {
        int val;
        cin >> val;
        v.push_back(val);
    }

    sort(v.begin(), v.end());


    long long int ans = 0;

    int st = 0;
    int dr = 3 * N - 1;

    while (st <= dr) {
        ++ st;
        dr --;
        ans += v[dr --];
    }

    cout << ans << '\n';
    return 0;
}
