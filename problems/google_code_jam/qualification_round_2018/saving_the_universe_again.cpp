#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000 + 5;

int getCost(const string &program) {
    int damage = 0;
    int charged = 1;
    for (const char ch: program)
        if (ch == 'C') {
            charged *= 2;
            if (charged > INF)
                charged = INF;
        }
        else {
            damage += charged;
            if (damage > INF)
                damage = INF;
        }
    return damage;
}

string test() {
    int shield;
    string program;
    cin >> shield >> program;    
    
    int ans = 0;
    while (getCost(program) > shield) {
        bool changed = false;
        for (int i = program.size() - 1; i && !changed; -- i)
            if (program[i] == 'S' && program[i - 1] == 'C') {
                swap(program[i], program[i - 1]);
                changed = true;
                ++ ans;
            }

        if (!changed)
            break;
    }

    if (getCost(program) > shield)
        return "IMPOSSIBLE";
    else {
        stringstream ss;
        ss << ans;
        return ss.str(); 
    }
}

int main() {
    int T = 0;
    cin >> T;
    for (int i = 1; i <= T; ++ i)
        cout << "Case #" << i << ": " << test() << '\n';
    return 0;
}
