#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

lint read() {
    lint nr;
    cin >> nr;
    nr *= 1000000000;

    if (cin.peek() == '.') {
        char aux;
        cin >> aux;
        string nr2;
        cin >> nr2;
        stringstream ss;
        ss << setiosflags(ios :: left);
        ss << setfill('0') << setw(9) << nr2;
        lint nr3;
        ss >> nr3;
        nr += nr3;
    }

    return nr;
}

int main() {
    lint x, y;
    x = read(), y = read();
    cout << x / y << endl;
    return 0;
}
