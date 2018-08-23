#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector <int> allCh;
void getChanges(int nr) {
    int val = 1;
    while (val <= nr) {
        allCh.push_back(val);
        val = nr / (nr / val) + 1;
    }
    allCh.push_back(val);
}

vector <pair <int, int> > v;

bool works(int M) {
    for (int i = 0; i < v.size(); ++ i)
        for (int j = i + 1; j < v.size(); ++ j)
            if (v[i].second != v[j].second) {
                if (v[i].first / M == v[j].first / M)
                    return false;
            }
            else {
                if (v[i].first / M != v[j].first / M)
                    return false;
            }
    return true;
}

int main()
{

    int N;
    cin >> N;
    for (int i = 0; i < N; ++ i) {
        int a, c;
        cin >> a >> c;
        v.push_back({a - 1, c});
        getChanges(a - 1);
    }


    sort(allCh.begin(), allCh.end());
    allCh.resize(unique(allCh.begin(), allCh.end()) - allCh.begin());

    allCh.push_back(2E9 + 5);

    int ans = 0;
    for (int i = 0; i + 1 < allCh.size(); ++ i)
        if (works(allCh[i]))
            ans += allCh[i + 1] - allCh[i];

    if (ans <= 1E9 + 15)
        cout << ans << '\n';
    else
        cout << "-1\n";
    return 0;
}
