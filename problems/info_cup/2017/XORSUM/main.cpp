#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 1000000 + 5;
const int BITS = 30;
typedef long long int lint;

int N;
int v[NMAX];

int bit;
int getVal(int nr) {
    return (nr & ((1 << (bit + 1)) - 1));
}
bool cmp(const int &a, const int &b) {
    return getVal(a) < getVal(b);
}

int getVal(int nr, int bit) {
    return (nr & ((1 << bit) - 1));
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];

    vector <int> v1;
    vector <int> v2;
    v1.reserve(N);
    v2.reserve(N);

    int ans = 0;
    for (bit = 0; bit < BITS; ++ bit) {
        //sort(v + 1, v + N + 1, cmp);
        v1.clear(), v2.clear();
        for (int i = 1; i <= N; ++ i)
            if (v[i] & (1 << bit))
                v2.push_back(v[i]);
            else
                v1.push_back(v[i]);

        merge(v1.begin(), v1.end(),
              v2.begin(), v2.end(),
              v + 1, cmp);

        int border = 0;
        while (border + 1 <= N && !(v[border + 1] & (1 << bit)))
            ++ border;

        lint ones = 0;

        //0 - 0
        for (int i = 1, j = border + 1; i <= border; ++ i) {
            if (j < i)
                j = i;
            while (j - 1 >= i && getVal(v[i], bit) + getVal(v[j - 1], bit) >= (1 << bit))
                -- j;
            ones += (border - j + 1);
        }

        //1 - 1
        for (int i = border + 1, j = N + 1; i <= N; ++ i) {
            if (j < i)
                j = i;
            while (j - 1 >= i && getVal(v[i], bit) + getVal(v[j - 1], bit) >= (1 << bit))
                -- j;
            ones += (N - j + 1);
        }

        //0 - 1
        for (int i = 1, j = N + 1; i <= border; ++ i) {
            while (j - 1 > border && getVal(v[i], bit) + getVal(v[j - 1], bit) >= (1 << bit))
                -- j;

            ones += (j - border - 1);
        }

        //Update ans
        if (ones & 1)
            ans ^= (1 << bit);
    }

    cout << ans << '\n';
    return 0;
}
