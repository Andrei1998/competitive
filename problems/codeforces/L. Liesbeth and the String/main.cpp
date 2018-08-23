#include <iostream>
//#include <string>
//#include <deque>

using namespace std;

/*void perform(deque <char> &str) {
    if (str.front() == 'a') {
        str.push_back('b');
        str.push_back('c');
    }
    else if (str.front() == 'b')
        str.push_back('a');
    else {
        str.push_back('a');
        str.push_back('a');
        str.push_back('a');
    }
    str.pop_front();
    str.pop_front();
}

int go(string str) {
    deque <char> dq;
    for (auto it: str)
        dq.push_back(it);

    int cnt = 0;
    while (dq.size() != 1 || dq.front() != 'a') {
        for (auto it: dq)
            cout << it;
        cout << ' ' << dq.size() << endl;
        perform(dq);
        ++ cnt;
    }
    return cnt;
}

int apply(int nr) {
    if (nr % 2 == 0)
        return nr / 2;
    else
        return nr + (nr + 1) / 2;
}*/

long long int solve(long long int nr) {
    if (nr == 1)
        return 0;
    else if (nr % 2 == 0)
        return nr + solve(nr / 2);
    else
        return nr + solve(nr + (nr + 1) / 2) + 1;
}

int main()
{
    //cout << go("aaaaaaa") << '\n';
    //for (int i = 1; i <= 20; ++ i)
    //    cout << i << ' ' << apply(i) << endl;

    int nr;
    cin >> nr;
    cout << solve(nr) << '\n';
    return 0;
}
