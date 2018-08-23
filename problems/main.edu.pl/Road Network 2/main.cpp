#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

class InputReader {
public:
    InputReader() {
        input_file = stdin;
        cursor = 0;
        fread(buffer, SIZE, 1, input_file);
    }
    inline InputReader &operator >>(int &n) {
        while(buffer[cursor] < '0' || buffer[cursor] > '9') {
            advance();
        }
        n = 0;
        while('0' <= buffer[cursor] && buffer[cursor] <= '9') {
            n = n * 10 + buffer[cursor] - '0';
            advance();
        }
        return *this;
    }
private:
    FILE *input_file;
    static const int SIZE = 1 << 17;
    int cursor;
    char buffer[SIZE];
    inline void advance() {
        ++ cursor;
        if(cursor == SIZE) {
            cursor = 0;
            fread(buffer, SIZE, 1, input_file);
        }
    }
};

const int NMAX = 2000000 + 5;

set <pair <int, int> > Set;

int main()
{
    InputReader cin;
    int n;
    cin >> n;

    int sum = 0;
    for (int i = 1; i <= n; ++ i) {
        int d;
        cin >> d;
        Set.insert(make_pair(d, i));

        sum += d;
        if (sum > 2 * n - 2) {
            cout << "BRAK\n";
            return 0;
        }
    }

    if (sum < 2 * n - 2) {
        cout << "BRAK\n";
        return 0;
    }

    for (int i = 1; i < n; ++ i) {
        pair <int, int> beg = *Set.begin(), end = *Set.rbegin();
        Set.erase(beg);
        Set.erase(end);

        cout << beg.second << ' ' << end.second << '\n';

        -- end.first;
        Set.insert(end);
    }
    return 0;
}
