/*
ID: andreip3
PROG: spin
LANG: C++11
*/

#include <fstream>
#include <bitset>

using namespace std;

int speed[5];
bitset <360> bits[5];

int main()
{
    ifstream cin("spin.in");
    ofstream cout("spin.out");

    for (int i = 0; i < 5; ++ i) {
        cin >> speed[i];

        int w = 0;
        cin >> w;

        while (w --) {
            int a, b;
            cin >> a >> b;
            for (int j = 0; j <= b; ++ j)
                bits[i][(a + j) % 360] = 1;
        }
    }

    for (int t = 0; t < 360000; ++ t) {
        bitset <360> b = bits[0];
        for (int i = 1; i < 5; ++ i)
            b &= bits[i];

        if (b.any()) {
            cout << t << '\n';
            return 0;
        }
        for (int i = 0; i < 5; ++ i)
            bits[i] = (bits[i] << speed[i]) | (bits[i] >> (360 - speed[i]));
    }

    cout << "none\n";
    return 0;
}
