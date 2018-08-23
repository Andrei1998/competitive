#include <iostream>
#include <string>

using namespace std;


int main()
{
    string str;
    cin >> str;
    long long int ans = 0;
    for (int i = 0; i < str.size(); ++ i)
        if (str[i] == 'U')
            ans += str.size() - i - 1 + 2 * i;
        else
            ans += 2 * (str.size() - i - 1) + i;
    cout << ans << '\n';
    return 0;
}
