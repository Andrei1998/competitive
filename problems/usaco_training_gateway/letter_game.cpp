/*
ID: andreip3
LANG: C++14
TASK: lgame
*/
#include <bits/stdc++.h>

using namespace std;

int scores[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1,
                  7, 6, 3, 5, 2, 3, 5, 7, 2,
                  1, 2, 4, 6, 6, 7, 5, 7};

string target;
map <char, int> label;

bool valid(const string &str) {
    for (auto it: str)
        if (!label.count(it))
            return false;
    return true;
}
vector <int> getFreq(const string &str) {
    vector <int> v(label.size());
    for (auto it: str)
        ++ v[label[it]];
    return v;
}
bool included(const vector <int> &freq1, const vector <int> &freq2) {
    for (int i = 0; i < label.size(); ++ i)
        if (freq1[i] > freq2[i])
            return false;
    return true;
}

vector <vector <int> > usefull;
vector <string> usefullStr;
vector <int> usefullCost;

int best;
vector <string> sols;

void solve(const vector <int> &freq, int cost, string str, int start) {
    if (cost > best) {
        best = cost;
        sols = {str};
    }
    else if (cost == best)
        sols.push_back(str);
    for (int i = start; i < usefull.size(); ++ i)
        if (included(usefull[i], freq)) {
            vector <int> freq2 = freq;
            for (int j = 0; j < label.size(); ++ j)
                freq2[j] -= usefull[i][j];
            solve(freq2, cost + usefullCost[i], str + " " + usefullStr[i], i);
        }
}

int main() {
    ifstream cin("lgame.in");
    ofstream cout("lgame.out");
    cin >> target;
    for (auto it: target)
        if (!label.count(it))
            label[it] = label.size() - 1;
    const vector <int> frTarget = getFreq(target);

    ifstream din("lgame.dict");

    string d;
    while (din >> d) {
        if (d == ".")
            break;
        if (valid(d)) {
            vector <int> freqD = getFreq(d);
            if (included(freqD, frTarget)) {
                usefull.push_back(freqD);
                usefullStr.push_back(d);
                usefullCost.push_back(0);
                for (auto it: d)
                    usefullCost.back() += scores[it - 'a'];
            }
        }
    }

    solve(frTarget, 0, "", 0);
    cout << best << '\n';
    for (auto it: sols)
        cout << it.substr(1) << '\n';
    return 0;
}
