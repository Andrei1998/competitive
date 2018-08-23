#include <iostream>
#include <string>

using namespace std;

int n;
string str;



int main()
{
    while (1) {
        cin >> str;
        if (str[0] == '-')
            return 0;

        n = str.size();
        str = " " + str;
    }
    return 0;
}
