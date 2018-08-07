#include <iostream>
#include <algorithm>

#define int long long int
using namespace std;

signed main()
{
    int s, c;
    cin >> s >> c;

    int ans = min(s, c / 2);

    s -= ans;
    c -= 2 * ans;
    ans += c / 4;

    cout << ans << '\n';
    return 0;
}
