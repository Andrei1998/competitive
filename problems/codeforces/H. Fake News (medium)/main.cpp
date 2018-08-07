#include <iostream>
#include <string>

using namespace std;

int dp[400];
string str;

char chr;
int getDp() {
    int N = str.size() - 1;
    for (int i = 1; i <= N; ++ i) {
        if (str[i] == 'a')
            dp[i] = 1;
        else {
            dp[i] = 0;
            for (int j = 1; j < i; ++ j)
                if (str[j] + 1 == str[i])
                    dp[i] += dp[j];
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; ++ i)
        if (str[i] == chr)
            ans += dp[i];
    return ans;
}

int freq[1 << 20];

void backtr(char ch) {
    if (str.size() - 1 == 2 * (chr - 'a' + 1)) {
        //if (getDp() == 113)
        //    cout << str << ' ' << getDp() << '\n';
        ++ freq[getDp()];
        return ;
    }

    if (str.size() - 1 == 2 * (chr - 'a' + 1) - 1) {
        str += ch;
        backtr(ch + 1);
        str.pop_back();
    }
    else {
        str += ch;
        str += (ch + 1);
        backtr(ch + 1);
        str.pop_back();
        str.pop_back();

        str += (ch + 1);
        str += ch;
        backtr(ch + 1);
        str.pop_back();
        str.pop_back();
    }
}

int main()
{
    for (chr = 'a'; chr <= 's'; ++ chr) {
        str = " a";
        backtr('a');
    }

    for (int i = 2; ; i += 2)
        if (!freq[i]) {
            cout << i << endl;
            return 1;
        }
    return 0;
}
