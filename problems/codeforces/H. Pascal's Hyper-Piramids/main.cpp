#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

typedef long long int lint;

map <vector <int>, lint> Map;

int D, H;
void computeState(vector <int> state) {
    vector <int> aux;
    for (int i = 0; i < D; ++ i)
        if (state[i] > 0) {
            aux = state;
            aux[i] --;
            sort(aux.begin(), aux.end());
            Map[state] += Map[aux];
        }
}

queue <vector <int> > q;

int main()
{
    cin >> D >> H;

    -- H;

    vector <int> node(D, 0);
    q.push(node);
    Map[node] = 1;

    vector <lint> ans;
    while (!q.empty()) {
        node = q.front();
        q.pop();

        int sum = 0;
        for (int i = 0; i < D; ++ i)
            sum += node[i];

        if (sum == H)
            ans.push_back(Map[node]);
        else {
            vector <int> aux;
            for (int i = 0; i < D; ++ i) {
                aux = node;
                ++ aux[i];
                sort(aux.begin(), aux.end());

                if (!Map.count(aux)) {
                    q.push(aux);
                    computeState(aux);
                }
            }
        }
    }

    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    for (auto it: ans)
        cout << it << '\n';
    return 0;
}
