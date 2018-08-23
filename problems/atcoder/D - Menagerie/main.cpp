#include <iostream>
#include <string>

using namespace std;

int N;
string str;

const int NMAX = 100000 + 10 + 5;
bool type[NMAX];

int main()
{
    cin >> N;
    cin >> str;
    str = " " + str;

    str += str[1];

    for (int i = 0; i < 2; ++ i)
        for (int j = 0; j < 2; ++ j) {
            type[1] = i;
            type[2] = j;

            for (int k = 2; k <= N + 1; ++ k)
                if (type[k] == 0) {
                    if (str[k] == 'o')
                        type[k + 1] = type[k - 1];
                    else
                        type[k + 1] = type[k - 1] ^ 1;
                }
                else {
                    if (str[k] == 'o')
                        type[k + 1] = type[k - 1] ^ 1;
                    else
                        type[k + 1] = type[k - 1];
                }
            if (type[1] == type[N + 1] && type[2] == type[N + 2]) {
                for (int k = 1; k <= N; ++ k)
                    if (type[k] == 0)
                        cout << 'S';
                    else
                        cout << 'W';
                cout << '\n';
                return 0;
            }
        }

    cout << "-1\n";
    return 0;
}
