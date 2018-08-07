#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int lint;
const int NMAX = 200000 + 5;

int c[NMAX];
int who[NMAX];

vector <int> v1;
vector <int> v2;
vector <int> v12;

int main()
{
    ios_base :: sync_with_stdio(false);

    int N, M, K;
    cin >> N >> M >> K;

    for (int i = 1; i <= N; ++ i)
        cin >> c[i];

    int x;
    cin >> x;
    while (x --) {
        int where;
        cin >> where;
        who[where] += 1;
    }

    cin >> x;
    while (x --) {
        int where;
        cin >> where;
        who[where] += 2;
    }

    for (int i = 1; i <= N; ++ i)
        if (who[i] == 1)
            v1.push_back(c[i]);
        else if (who[i] == 2)
            v2.push_back(c[i]);
        else if (who[i] == 3)
            v12.push_back(c[i]);

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    sort(v12.begin(), v12.end());

    for (int i = 0; i <= K && i <= v12.size() && i <= M; ++ i) {
        ;
    }

    return 0;
}
