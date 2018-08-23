#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

class OutputWriter {
public:
    OutputWriter(const char *file_name) {
        out = fopen(file_name, "w");
        cursor = 0;
    }

    ~OutputWriter() {
        flush();
        fclose(out);
    }

    OutputWriter& operator<<(int nr) {
        int digits[10];
        int cnt = 0;
        do {
            digits[cnt ++] = nr % 10;
            nr /= 10;
        } while (nr);
        for (int i = cnt - 1; i >= 0; -- i)
            add(digits[i] + '0');
        return (*this);
    }

    OutputWriter& operator<<(char ch) {
        add(ch);
        return (*this);
    }

    void add(char ch) {
        if (cursor == SIZE)
            flush();
        buffer[cursor ++] = ch;
    }

    void flush() {
        fwrite(buffer, 1, cursor, out);
        cursor = 0;
    }
private:
    FILE *out;
    static const int SIZE = (1 << 17);
    int cursor;
    char buffer[SIZE];
};

const int DIGITS = 250;
const long long int BASE = 1000000000000000000LL;

class BigInteger {
public:
    long long int v[DIGITS];

    BigInteger(long long int c = 0) {
        memset(v, 0, sizeof v);
        v[0] = 1;
        v[1] = c;
    }

    friend BigInteger operator+(const BigInteger &a, const BigInteger &b) {
        BigInteger ans;
        ans.v[0] = max(a.v[0], b.v[0]);

        long long int tr = 0;
        for (int i = 1; i <= ans.v[0]; ++ i) {
            ans.v[i] = a.v[i] + b.v[i] + tr;
            if (ans.v[i] >= BASE) {
                tr = 1;
                ans.v[i] -= BASE;
            }
            else
                tr = 0;
        }

        if (tr)
            ans.v[++ ans.v[0]] = tr;
        return ans;
    }

    friend BigInteger operator-(const BigInteger &a, const BigInteger &b) {
        BigInteger ans;
        ans.v[0] = a.v[0];

        long long int tr = 0;
        for (int i = 1; i <= ans.v[0]; ++ i) {
            ans.v[i] = a.v[i] - b.v[i] - tr;
            if (ans.v[i] < 0) {
                tr = 1;
                ans.v[i] += BASE;
            }
            else
                tr = 0;
        }

        while (ans.v[0] > 1 && !ans.v[ans.v[0]])
            -- ans.v[0];
        return ans;
    }

    friend bool operator<(const BigInteger &a, const BigInteger &b) {
        if (a.v[0] != b.v[0])
            return a.v[0] < b.v[0];

        for (int i = a.v[0]; i; -- i)
            if (a.v[i] != b.v[i])
                return a.v[i] < b.v[i];
        return false;
    }
};

istream& operator>>(istream &f, BigInteger &b) {
    string str;
    f >> str;

    reverse(str.begin(), str.end());

    b.v[0] = 0;
    for (int start = 0; start < str.size(); start += 18) {
        int finish = min((int)str.size() - 1, start + 17);
        long long int nr = 0;
        for (int i = finish; i >= start; -- i) {
            nr *= 10;
            nr += str[i] - '0';
        }

        b.v[++ b.v[0]] = nr;
    }

    return f;
}

typedef BigInteger lint;

struct Treap {
    int key, pr;

    lint val;
    lint sumVal;

    Treap *left, *right;
    Treap(int _key = 0, int _pr = 0, lint _val = 0, lint _sumVal = 0, Treap *_left = NULL, Treap *_right = NULL):
        key(_key), pr(_pr), val(_val), sumVal(_sumVal), left(_left), right(_right) {}
} *nil, *root;

void computeDp(Treap *t) {
    if (t != nil)
        t -> sumVal = t -> left -> sumVal + t -> right -> sumVal + t -> val;
}

pair <Treap*, Treap*> split(Treap *t, lint val) {
    if (t == nil)
        return make_pair(nil, nil);

    pair <Treap*, Treap*> aux;
    if (val < t -> left -> sumVal + t -> val) {
        aux = split(t -> left, val);
        t -> left = aux.second;
        aux.second = t;
    }
    else {
        aux = split(t -> right, val - (t -> left -> sumVal + t -> val));
        t -> right = aux.first;
        aux.first = t;
    }
    computeDp(t);
    return aux;
}

Treap* join(Treap *l, Treap *r) {
    if (l == nil)
        return r;
    if (r == nil)
        return l;

    if (l -> pr > r -> pr) {
        l -> right = join(l -> right, r);
        computeDp(l);
        return l;
    }
    else {
        r -> left = join(l, r -> left);
        computeDp(r);
        return r;
    }
}

Treap* insert(Treap *t, int key, int pr, lint val) {
    pair <Treap*, Treap*> aux = split(t, val - 1);

    t = new Treap(key, pr, val, val, nil, nil);
    t = join(aux.first, t);
    t = join(t, aux.second);
    return t;
}

/*void dump(Treap *t) {
    if (t == nil)
        return ;
    dump(t -> left);
    cout << t -> key << ' ';
    dump(t -> right);
}

void Print(Treap *t) {
    cout << "Printing: ";
    dump(t);
    cout << "#" << endl;
}*/

const int NMAX = 70000 + 5;

int N;
lint v[NMAX];

int p[NMAX];
int cnt;
void dfs(Treap *t) {
    if (t == nil)
        return ;

    dfs(t -> left);
    p[t -> key] = ++ cnt;
    dfs(t -> right);
}

int main()
{
    ifstream cin("input");
    OutputWriter cout("output");

    auto now = system_clock::now();
    auto duration = now.time_since_epoch();
    srand(duration_cast<milliseconds>(duration).count());
    nil = new Treap(-1, -1);
    nil -> left = nil -> right = nil;
    root = nil;

    cin >> N;
    for (int i = 1; i <= N; ++ i)
        cin >> v[i];
    for (int i = N; i; -- i)
        v[i] = v[i] - v[i - 1];

    /*for (int i = 1; i <= N; ++ i)
        cout << v[i] << ' ';
    cout << endl;*/

    for (int i = 1; i <= N; ++ i)
        root = insert(root, i, rand(), v[i]);

    dfs(root);
    for (int i = 1; i <= N; ++ i)
        cout << p[i] << " \n"[i == N];
    return 0;
}
