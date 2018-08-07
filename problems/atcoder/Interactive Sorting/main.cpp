#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int N;
map <vector <vector <int> >, int> MapMin;
map <vector <vector <int> >, pair <int, int> > MapMove;

int facts[] = {1, 1, 2, 6, 24, 120, 720, 5040};

void solve(const vector <vector <int> > &v) {
    if (MapMin.count(v))
        return ;

    if (v.size() == 1) {
        MapMin[v] = 0;
        return ;
    }

    int maxI = N, maxJ = N;
    if (v.size() == facts[N])
        maxI = 1, maxJ = 2;

    int bestCost = 1E9;
    pair <int, int> bestPair;
    for (int i = 0; i < maxI; ++ i)
        for (int j = i + 1; j < maxJ; ++ j) {
            vector <vector <int> > smaller;
            vector <vector <int> > bigger;

            for (auto perm: v)
                if (perm[i] < perm[j])
                    smaller.push_back(perm);
                else
                    bigger.push_back(perm);

            if (smaller == v || bigger == v)
                continue;

            solve(smaller);
            solve(bigger);

            int minMoves = max(MapMin[smaller], MapMin[bigger]);
            if (minMoves < bestCost) {
                bestCost = minMoves;
                bestPair = make_pair(i, j);
            }
        }

    MapMin[v] = 1 + bestCost;
    MapMove[v] = bestPair;
}

bool cmp(char A, char B) {
    cout << "? " << A << ' ' << B << endl;
    char ans;
    cin >> ans;
    return (ans == '<');
}

void mergeSort(vector <char> &v) {
    if (v.size() <= 1)
        return ;

    vector <char> lft;
    vector <char> rgt;

    int i;
    for (i = 0; i <= (v.size() - 1) / 2; ++ i)
        lft.push_back(v[i]);
    for (; i < v.size(); ++ i)
        rgt.push_back(v[i]);

    mergeSort(lft);
    mergeSort(rgt);

    merge(lft.begin(), lft.end(),
          rgt.begin(), rgt.end(),
          v.begin(), cmp);
}

int main()
{
    int Q;
    cin >> N >> Q;

    if (N <= 6) {
        vector <int> p(N);
        for (int i = 0; i < N; ++ i)
            p[i] = i;
        vector <vector <int> > perms;

        do {
            perms.push_back(p);
        } while (next_permutation(p.begin(), p.end()));

        solve(perms);
        //cout << "We will use at most " << MapMin[perms] << endl;

        while (perms.size() > 1) {
            pair <int, int> p = MapMove[perms];
            vector <vector <int> > smaller;
            vector <vector <int> > bigger;
            for (auto perm: perms)
                if (perm[p.first] < perm[p.second])
                    smaller.push_back(perm);
                else
                    bigger.push_back(perm);

            cout << "? " << (char)(p.first + 'A') << ' ' << (char)(p.second + 'A') << endl;
            char ans;
            cin >> ans;
            if (ans == '<')
                perms = smaller;
            else
                perms = bigger;
        }

        vector <int> v = perms[0];
        vector <int> x(N);
        for (int i = 0; i < N; ++ i)
            x[v[i]] = i;

        cout << "! ";
        for (int i = 0; i < N; ++ i)
            cout << (char)(x[i] + 'A');
        cout << endl;
    }
    else {
        vector <char> p;
        for (int i = 0; i < N; ++ i)
            p.push_back((char)('A' + i));
        mergeSort(p);

        cout << "! ";
        for (int i = 0; i < N; ++ i)
            cout << p[i];
        cout << endl;
    }
    return 0;
}
