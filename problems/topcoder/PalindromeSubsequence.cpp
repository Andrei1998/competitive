#include <bits/stdc++.h>

using namespace std;

class PalindromeSubsequence {
public:
    vector <int> optimalPartition(string str) {
        const int N = str.size();
        vector <int> ans(N, 1);

        string aux = str;
        reverse(aux.begin(), aux.end());

        if (aux != str) {
            for (int i = 0; i < N; ++ i)
                if (str[i] == 'b')
                    ans[i] = 2;
        }

        return ans;
    }
};

int main() {
    return 0;
}
