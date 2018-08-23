/*
ID: andreip3
LANG: C++14
TASK: shopping
*/

#include <bits/stdc++.h>

using namespace std;

typedef pair <map <int, int>, int> Offer;

int S;
set <Offer> initOffers;

vector <pair <vector <int>, int> > offers;

map <vector <int>, int> memo;
int solve(vector <int> vect) {
    int zero = 0;
    for (int i = 0; i < vect.size(); ++ i)
        if (vect[i] < 0)
            return 1E9 + 15;
        else if (vect[i] == 0)
            ++ zero;
    if (zero == vect.size())
        return 0;
    if (memo.count(vect))
        return memo[vect];

    int ans = 1E9 + 15;
    for (const auto &off: offers) {
        for (int i = 0; i < vect.size(); ++ i)
            vect[i] -= off.first[i];
        ans = min(ans, solve(vect) + off.second);
        for (int i = 0; i < vect.size(); ++ i)
            vect[i] += off.first[i];
    }

    memo[vect] = ans;
    return ans;
}

int main() {
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);

    cin >> S;
    for (int i = 0; i < S; ++ i) {
        Offer o;
        int cnt;
        cin >> cnt;
        while (cnt --) {
            int a, b;
            cin >> a >> b;
            o.first[a] += b;
        }
        cin >> o.second;
        initOffers.insert(o);
    }

    map <int, int> whichPosInVect;

    int B = 0;
    cin >> B;
    vector <int> all;
    for (int i = 1; i <= B; ++ i) {
        int c, k, p;
        cin >> c >> k >> p;
        whichPosInVect[c] = whichPosInVect.size() - 1;
        Offer o;
        o.first[c] = 1;
        o.second = p;
        initOffers.insert(o);
        all.push_back(k);
    }

    for (const auto &off: initOffers) {
        bool ok = true;
        for (auto it: off.first)
            if (!whichPosInVect.count(it.first)) {
                ok = false;
                break;
            }

        if (ok) {
            pair <vector <int>, int> p;
            p.second = off.second;
            p.first.resize(all.size());

            for (auto it: off.first)
                p.first[whichPosInVect[it.first]] = it.second;

            offers.push_back(p);
        }
    }
    cout << solve(all) << '\n';
    return 0;
}
