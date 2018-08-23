#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector <pair <int, int> > sol;

const int NMAX = 19;

int n;
int k[NMAX + 1];

//Add a cycle of length nr (of given index)
void add(int index, int nr) {
    vector <pair <int, int> > aux;
    aux.reserve((sol.size() + 1) * nr - 1);

    if ((sol.size() + 1) % 2 == 0) { //If the length so far is even
        for (int i = 0; i < (sol.size() + 1) / 2; ++ i) {
            for (int j = 2; j <= nr; ++ j)
                aux.push_back(make_pair(index, 1));
            aux.push_back(sol[2 * i]);

            for (int j = nr; j >= 2; -- j)
                aux.push_back(make_pair(index, -1));

            if (2 * i + 1 < sol.size())
                aux.push_back(sol[2 * i + 1]);
        }
    }
    else { //Otherwise
        for (int i = 0; i < sol.size(); ++ i)
            aux.push_back(sol[i]);
        for (int j = 2; j <= nr; ++ j)
            aux.push_back(make_pair(index, 1));

        for (int i = sol.size() - 1; i >= 0; i -= 2) {
            aux.push_back(make_pair(sol[i].first, sol[i].second * (-1)));
            for (int j = nr; j >= 3; -- j)
                aux.push_back(make_pair(index, -1));
            aux.push_back(make_pair(sol[i - 1].first, sol[i - 1].second * (-1)));
            for (int j = 2; j < nr; ++ j)
                aux.push_back(make_pair(index, 1));
        }
    }

    sol = aux;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> k[i];

    sol.resize(k[1] - 1);
    for (int i = 0; i < k[1] - 1; ++ i)
        sol[i] = make_pair(1, 1);

    for (int i = 2; i <= n; ++ i)
        add(i, k[i]);

    //Simulate the process too (needed to find last move)
    int v[NMAX];
    for (int i = 1; i <= n; ++ i)
        v[i] = 1;

    for (int i = 0; i < sol.size(); ++ i) {
        //for (int j = 1; j <= n; ++ j)
        //    cout << v[j] << ' ';
        //cout << endl;

        v[sol[i].first] += sol[i].second;
        cout << sol[i].first << ' ' << sol[i].second << '\n';
    }

    //Print last move
    for (int i = 1; i <= n; ++ i)
        if (v[i] != 1) {
            if (v[i] == 2)
                cout << i << " -1\n";
            else
                cout << i << " 1\n";
        }

    //for (int j = 1; j <= n; ++ j)
    //    cout << v[j] << ' ';
    //cout << endl;
    return 0;
}
