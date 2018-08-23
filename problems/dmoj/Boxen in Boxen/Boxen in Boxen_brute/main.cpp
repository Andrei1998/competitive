#include <iostream>
#include <algorithm>

#define lint long long int
using namespace std;

const int NMAX = 1e5 + 5;
const int MOD = 1000000000 + 7;

int N, F;

struct Box {
     int a, b;

     friend bool operator<(const Box &a, const Box &b) {
        if (a.a != b.a)
            return a.a < b.a;
        else
            return a.b < b.b;
     }
} boxes[NMAX];

lint getBest(int cnt) {
    lint best = F;

    lint val = F;
    for (int i = 1; i <= cnt; ++ i) {
        val = boxes[i].a * val - boxes[i].b;
        if (val > best)
            best = val;
    }

    return best;
}

int main()
{
    //ifstream cin("data.in");
    //ofstream cout("data.ok");

    cin >> N >> F;

    for (int i = 1; i <= N; ++ i)
        cin >> boxes[i].a >> boxes[i].b;

    for (int i = 1; i <= N; ++ i) {
        sort(boxes + 1, boxes + i + 1);

        lint ans = 0;
        do {
            lint aux = getBest(i);
            if (aux > ans)
                ans = aux;
        } while (next_permutation(boxes + 1, boxes + i + 1));

        cout << ans % MOD << '\n';
        cout << ans << endl;
        cout << endl;
    }

    //cin.close();
    //cout.close();
    return 0;
}
