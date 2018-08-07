#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>

using namespace std;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
int expos[24];

typedef long long int lint;
vector <lint> nrs[200000];

void backtr(int pos, int divs, long long int nr, bool inv) {
    if (divs >= 200000)
        return ;

    //cout << "pos = " << pos << ' ' << divs << ' ' << nr << endl;
    nrs[divs].push_back(nr);
    if (pos == 22)
        return ;

    for (int i = 0; i < 60; ++ i) {
        expos[pos] = i;

        if (pos == 0)
            backtr(pos + 1, divs * (i + 1), nr, inv);
        else if (expos[pos] <= expos[pos - 1] || !inv)
            backtr(pos + 1, divs * (i + 1), nr, inv | (expos[pos] > expos[pos - 1]));

        if (nr >= 1000000000000000000LL / primes[pos])
            return ;
        nr *= primes[pos];
    }
}

multiset <int> allDivs;
int cntBigger(int nr) {
    int cnt = 0;
    for (multiset <int> :: reverse_iterator it = allDivs.rbegin(); it != allDivs.rend(); ++ it)
        if (*it > nr) {
            ++ cnt;
            if (cnt == 2)
                return cnt;
        }
    return cnt;
}

int main()
{
    backtr(0, 1, 1, 0);

    vector <pair <lint, int> > all;
    for (int i = 1; i < 200000; ++ i) {
        if (nrs[i].size() > 0) {
            sort(nrs[i].begin(), nrs[i].end());
            nrs[i].resize(unique(nrs[i].begin(), nrs[i].end()) - nrs[i].begin());
            int cnt = 0;
            //cout << i << ' ';
            for (auto it: nrs[i]) {
                ++ cnt;
                if (cnt <= 8)
                    //cout << it << ' ';
                    all.push_back(make_pair(it, i));

            }
            //cout <<"#" << endl;
        }
    }

    sort(all.begin(), all.end());

    vector <lint> real;
    for (auto it: all) {
        if (cntBigger(it.second) < 2)
            real.push_back(it.first);
        allDivs.insert(it.second);
    }

    /*for (auto it: real)
        cout << it << ' ';
    cout << endl;*/

    int K;
    cin >> K;

    if (K >= real.size())
        cout << "-1\n";
    else
        cout << real[K - 1] << '\n';
    return 0;
}
