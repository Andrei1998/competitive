#include <iostream>
#include <set>

using namespace std;

set <int> Set;

int main()
{
    int n;
    cin >> n;

    while (n --) {
        int val;
        cin >> val;
        Set.insert(val);
    }

    cout << 15000 - Set.size() << '\n';
    return 0;
}
