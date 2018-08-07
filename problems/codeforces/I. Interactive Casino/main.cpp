#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>

using namespace std;

typedef long long int lint;

bool popcount[1 << 20];

lint x[200 + 5];
lint prec[1 << 20];

vector <pair <lint, int> > all;

void doStuff() {
    for (int i = 2; i <= 40; ++ i) {
        x[i] = 487237LL * x[i - 1] + 1011807;
        x[i] &= ((1 << 20) - 1);
    }

    for (int i = 1; i <= 40; ++ i)
        if (popcount[x[i]])
            prec[x[1]] |= (1LL << i);
    all.push_back(make_pair(prec[x[1]], x[1]));
}

void doAllStuff() {
    for (int i = 2; i <= 200; ++ i) {
        x[i] = 487237LL * x[i - 1] + 1011807;
        x[i] &= ((1 << 20) - 1);
    }
}

int money;

bool ask() {
    cout << "1" << endl;
    int val;
    cin >> val;
    if (val == money - 1) {
        money = val;
        return 0;
    }
    else {
        money = val;
        return 1;
    }
}

int main()
{
    for (int i = 1; i < (1 << 20); ++ i)
        popcount[i] = popcount[i - (i & (-i))] ^ 1;

    all.reserve(1 << 20);
    for (x[1] = 0; x[1] < (1 << 20); ++ x[1])
        doStuff();
    sort(all.begin(), all.end());

    cin >> money;

    lint mask = 0;
    for (int i = 1; i <= 40; ++ i)
        if (ask())
            mask += (1LL << i);

    x[1] = lower_bound(all.begin(), all.end(), make_pair(mask, -1)) -> second;
    doAllStuff();

    int cnt = 41;
    while (popcount[x[cnt]] == 0) {
        ask();
        ++ cnt;
    }

    cout << 200 - money << endl;
    return 0;
}
