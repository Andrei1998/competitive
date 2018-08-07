#include <iostream>
#include <map>

using namespace std;

typedef long long int lint;

map <lint, int> Map;

int desc[115];

void add(int nr) {
    for (int i = 2; i * i <= nr; ++ i)
        while (nr % i == 0)
            ++ desc[i], nr /= i;
    if (nr > 1)
        ++ desc[nr];
}

lint divs() {
    lint ans = 1;
    for (int i = 2; i < 115; ++ i)
        ans *= (1LL + desc[i]);
    return ans;
}

int main()
{
    Map[1] = 1;
    for (int i = 2; i <= 110; ++ i) {
        add(i);
        Map[divs()] = i;
    }

    ios_base :: sync_with_stdio(false);

    int T = 0;
    cin >> T;

    while (T --) {
        lint nr;
        cin >> nr;

        if (!Map.count(nr))
            cout << "nai\n";
        else
            cout << Map[nr] << '\n';
    }
    return 0;
}
