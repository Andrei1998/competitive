#include <iostream>

using namespace std;

typedef long long int lint;

lint N;

void doPrint(lint sum) {
    lint aux = sum + N / sum - 1;
    if (aux > 0 && aux % 2 == 0) {
        lint y = aux / 2;
        lint x = sum - y;

        if (x > 0 && x < y)
            cout << x << ' ' << y << '\n';
    }
}

int main()
{
    cin >> N;
    N *= 2;

    for (int i = 1; 1LL * i * i <= N; ++ i)
        if (N % i == 0) {
            doPrint(i);
            if (i != N / i)
                doPrint(N / i);
        }
    return 0;
}
