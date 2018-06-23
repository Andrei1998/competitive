#include <bits/stdc++.h>

using namespace std;

bool full(const set <pair <int, int> > &s, int x, int y) {
    for (int i = -1; i <= 1; ++ i)
        for (int j = -1; j <= 1; ++ j)
            if (!s.count({x + i, y + j}))
                return false;
    return true;
}

void test() {
    int A;
    cin >> A;
    set <pair <int, int> > Set;
    
    int x = 200, y = 200;
    while (1) {
        if (!full(Set, x, y)) {
            cout << x << ' ' << y << endl;
            int actX, actY;
            cin >> actX >> actY;
            if (actX == 0 && actY == 0)
                break;
            else if (actX == -1 && actY == -1)
                break;
            else
                Set.insert({actX, actY});
        }
        else
            x += 3;
    }
}

int main() {
    int T = 0;
    cin >> T;
    while (T --)
        test();
    return 0;
}
