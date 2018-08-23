#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <set>

using namespace std;

string to_str(int nr) {
    string str = "";
    do {
        str += (char)(nr % 10 + '0');
        nr /= 10;
    } while (nr);

    reverse(str.begin(), str.end());

    return str;
}

int len(int nr) {
    int ans = 0;
    do {
        ++ ans;
        nr /= 10;
    } while (nr);

    return ans;
}

int v[100];
int sz;

string get_string() {
    string ans = "";
    for (int i = 1; i <= sz; ++ i)
        ans += to_str(v[i]);
    return ans;
}

set <string> printed;
bool done;

void backtr(int nr, int digits) {
    if (digits < 0)
        return ;
    if (nr < 0)
        return ;

    if (!digits) {
        if (nr == 0) {
            string str = get_string();
            if (!printed.count(str)) {
                printed.insert(str);
               // cout << "str = " << str << endl;
                if (printed.size() == 300000)
                    done = true;
                //cout << printed.size() << '\n';
            }
        }
        return ;
    }

    for (int val = 0; val <= 100; ++ val) {
        v[++ sz] = val;
        backtr(nr - val, digits - len(val));
        if (done)
            return ;
        -- sz;
    }
}

int main()
{
    backtr(120, 8);

    return 0;
}
