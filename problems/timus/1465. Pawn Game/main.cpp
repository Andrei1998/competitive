#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int mex(vector <int> &v) {
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for (int i = 0; i < v.size(); ++ i)
        if (v[i] != i)
            return i;
    return v.size();
}

const int NMAX = 200 + 5;
const int PER = 34;
int sp[NMAX];

void brute_sp() {
    sp[0] = 0;
    sp[1] = 1;
    sp[2] = 1;

    for (int i = 3; i <= 200; ++ i) {
        vector <int> v;
        v.push_back(sp[i - 2]);
        for (int st = 0; st <= i - 3; ++ st)
            v.push_back(sp[st] ^ sp[i - st - 3]);
        sp[i] = mex(v);

    }
}

int main()
{
    brute_sp();

    int n;
    cin >> n;

    if (n > 200)
        n -= ((n - 200) / PER + 1) * PER;

    if (!sp[n])
        cout << "Black\n";
    else
        cout << "White\n";
    return 0;
}
