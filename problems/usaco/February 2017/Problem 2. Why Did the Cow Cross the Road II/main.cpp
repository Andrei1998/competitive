#include <fstream>
#include <vector>

using namespace std;

const int NMAX = 100000 + 5;

inline int lsb(int node) {
    return node & (-node);
}

int N;
int aib[NMAX];

void add(int where, int val) {
    for (; where <= N; where += lsb(where))
        aib[where] = max(aib[where], val);
}

int query(int where) {
    int ans = 0;
    for (; where; where -= lsb(where))
        ans = max(ans, aib[where]);
    return ans;
}

int a[NMAX];
int b[NMAX];
int where[NMAX];

int main()
{
    ifstream cin("nocross.in");
    ofstream cout("nocross.out");

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> a[i];
    for (int i = 1; i <= N; ++ i) {
        cin >> b[i];
        where[b[i]] = i;
    }

    int ans = 1;
    vector <pair <int, int> > upds;
    for (int i = 1; i <= N; ++ i) {
        upds.clear();
        for (int j = -4; j <= 4; ++ j) {
            int val = a[i] + j;
            if (1 <= val && val <= N) {
                int aux = query(where[val] - 1) + 1;
                upds.push_back(make_pair(where[val], aux));
                if (aux > ans)
                    ans = aux;
            }
        }

        for (auto it: upds)
            add(it.first, it.second);
    }

    cout << ans << '\n';
    return 0;
}
