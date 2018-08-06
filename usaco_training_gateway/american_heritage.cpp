/*
ID: andreip3
LANG: C++14
TASK: heritage
*/
#include <bits/stdc++.h>

using namespace std;

string in, pre, post;
void solve(int lIn, int rIn, int lPre, int rPre) {
    if (lIn > rIn)
        return ;
    const char lead = pre[lPre];
    const int where = find(in.begin() + lIn, in.begin() + rIn + 1, lead) - in.begin();
    const int cntLft = where - lIn;
    solve(lIn, where - 1, lPre + 1, lPre + cntLft);
    solve(where + 1, rIn, lPre + cntLft + 1, rPre);
    post += lead;
}

int main() {
    freopen("heritage.in", "r", stdin);
    freopen("heritage.out", "w", stdout);
    cin >> in >> pre;
    solve(0, in.size() - 1, 0, pre.size() - 1);
    cout << post << '\n';
    return 0;
}
