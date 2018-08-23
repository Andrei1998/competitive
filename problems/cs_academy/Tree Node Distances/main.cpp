#include <iostream>

using namespace std;

bool raisse(int node) {
    if (node == 1)
        cout << "F A" << endl;
    else
        cout << "F B" << endl;
    bool ans;
    cin >> ans;
    return ans;
}

void reset(int node) {
    if (node == 1)
        cout << "R A" << endl;
    else
        cout << "R B" << endl;
}

bool check() {
    cout << "E" << endl;
    bool ans;
    cin >> ans;
    return ans;
}

int da, db;
int hitroota, hitrootb;

void goUp(int d) {
    da = 0, db = 0, hitroota = hitrootb = 0;
    for (int i = 0; i < d; ++ i) {
        if (!hitroota) {
            if (!raisse(1))
                 hitroota = 1;
            else
                ++da;
        }
        if (!hitrootb) {
            if (!raisse(2))
                 hitrootb = 1;
            else
                ++db;
        }
    }
}

int main() {
    for (int d = 1; ; d <<= 1) {
        if (d > 1)
            reset(1), reset(2);
        goUp(d);

        if (hitroota) {
            while (!check())
                raisse(2), ++db;
            goto end;
        }
        else if (hitrootb) {
            while (!check())
                raisse(1), ++da;
            goto end;
        }
        else {
            //Try to raise B
            if (check())
                goto end;
            for (int i = 0; i < d; ++ i) {
                raisse(2), ++ db;
                if (check())
                    goto end;
            }

            //Try to raise A
            reset(1), reset(2), goUp(d);

            if (check())
                goto end;
            for (int i = 0; i < d; ++ i) {
                raisse(1), ++ da;
                if (check())
                    goto end;
            }
        }
    }

    end:
    reset(1), reset(2);

    int ans = 0;
    if (db > da) {
        for (int i = 0; i < db - da; ++ i)
            raisse(2), ++ ans;
    }
    else {
         for (int i = 0; i < da - db; ++ i)
            raisse(1), ++ ans;
    }

    while (!check()) {
        ans += 2;
        raisse(1);
        raisse(2);
    }

    cout << "A " << ans << endl;
    return 0;
}
