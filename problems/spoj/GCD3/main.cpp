#include <iostream>
#include <string>
#include <sstream>

using namespace std;

typedef long long int lint;

int main()
{
    ios_base :: sync_with_stdio(false);

    int T;
    cin >> T;

    string N, M;
    stringstream ss;
    while (T --) {
        int K;
        cin >> N >> M >> K;

        if (N.size() > 17)
            N = N.substr(N.size() - 17);
        if (M.size() > 17)
            M = M.substr(M.size() - 17);

        ss.clear();
        ss << N << ' ' << M;

        lint n, m;
        ss >> n >> m;

        int ans = 1;
        while (n % 2 == 0 && m % 2 == 0)
            n /= 2, m /= 2, ans <<= 1;
        cout << ans << '\n';
    }

    return 0;
}
