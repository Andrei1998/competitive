#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 31+ 5;
typedef long long int lint;

int N;
int d[NMAX];

int main()
{
    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> d[i];

    int from = 1;
    int to = 2;
    int temp = 3;
    lint ans = 0;

    for (int i = N; i; -- i) {
        if (d[i] == to) {
            ans += (1LL << (i - 1));
            swap(from, temp);
        }
        else if (d[i] == from)
            swap(to, temp);
        else {
            cout << "-1\n";
            return 0;
        }
    }

    cout << ans << '\n';
    return 0;
}
