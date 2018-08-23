#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    int val = 0;
    ifstream cin("start.in");
    cin >> val;
    ++ val;
    cin.close();

    ofstream cc("start.in");
    cc << val << endl;
    cc.close();

    srand(val);
    ofstream cout("data.in");

    int n = 4;
    int f = 6;

    cout << n << ' ' << f << '\n';
    for (int i = 1; i <= n; ++ i)
        cout << 1 + rand() % 10000 << ' ' << 1 + rand() % 10000 << '\n';

    cout.close();
    return 0;
}
