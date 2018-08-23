#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 100000 + 5;

int N;
int v[NMAX];

int main()
{
    ios_base :: sync_with_stdio(false);

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    sort(v + 1, v + N + 1);

    //Erase first line and last column while possible
    int lin = 1, col = N;
    while (col - 1 >= 1 && v[col - 1] >= lin + 1) {
        ++ lin;
        -- col;
    }

    //Game was reduced to 2 piles linked together
    int len1 = v[col] - lin;
    int len2 = 0;

    while (col - 1 >= 1 && v[col - 1] == lin) {
        ++ len2;
        -- col;
    }

    //Solve each of the 2 games separately
    bool win1 = (len1 & 1) ^ 1;
    bool win2 = (len2 & 1) ^ 1;

    //Link piles together and print result
    bool win = (!win1 || !win2);
    if (win)
        cout << "First\n";
    else
        cout << "Second\n";
    return 0;
}
