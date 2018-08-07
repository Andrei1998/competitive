#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;

    int cntS = 0;
    while (cntS + 1 < s.size() && s[cntS + 1] == s[0])
        ++ cntS;
    int cntT = 0;
    while (cntT + 1 < t.size() && t[cntT + 1] == t[0])
        ++ cntT;

    bool ok = true;
    if (s[0] != t[0] || cntS < cntT)
        ok = false;

    int i = 0;
    int j = 0;

    int cnt = 0;
    while (j < t.size() && i < s.size())
        if (s[i] == t[j])
            ++ i, ++ j;
        else {
            ++ j;
            ++ cnt;
        }

    if (!(i == s.size() && s.size() + cnt <= t.size()))
        ok = false;
    if (ok)
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}
