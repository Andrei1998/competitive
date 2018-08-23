#include <iostream>
#include <set>
#include <map>

using namespace std;

set <pair <int, int> > lista;
map <int, int> Map;

int main()
{
    int q = 0;
    cin >> q;

    int ind1 = -1;
    int ind2 = 0;

    while (q --) {
        char ch;
        cin >> ch;
        int val;
        cin >> val;

        if (ch == 'E') {
            lista.insert(make_pair(++ ind2, val));
            Map[val] = ind2;
        }
        else if (ch == 'F') {
            lista.insert(make_pair(-- ind1, val));
            Map[val] = ind1;
        }
        else
            lista.erase(make_pair(Map[val], val));
    }

    for (auto it: lista)
        cout << it.second << '\n';
    return 0;
}
