#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

bool prime(int nr) {
    if (nr <= 1)
        return false;
    for (int i = 2; i * i <= nr; ++ i)
        if (nr % i == 0)
            return false;
    return true;
}

int main() {
    int N;
    cin >> N;
    if ((!prime(N) || N == 1) && N != 4)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}
