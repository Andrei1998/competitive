
// String Hasher
template <int B, int MOD>
struct Hasher {
    // Static array of powers of B
    static vector <int> pows;
    static void reserve(int newSz) {
        if (newSz > (int)pows.size()) {
            const int oldSz = pows.size();
            pows.reserve(newSz);
            for (int i = oldSz; i < newSz; ++i)
                pows[i] = ((1LL * B * pows[i - 1]) % MOD);
        }
    }
    static int getPow(int pw) {
        while (pw >= (int)pows.size())
            reserve(2 * pows.size());
        return pows[pw];
    }

    // Data members
    int h, sz;
    // Constructors
    Hasher(): h(0), sz(0) {}
    Hasher(int ch): h(ch), sz(1) {}
    Hasher(int _h, int _sz): h(_h), sz(_sz) {}

    // Pushes
    void push_back(int ch) { h = (1LL * h * B + ch) % MOD, ++sz; }
    void push_front(int ch) { h = (1LL * ch * getPow(sz) + h) % MOD, ++sz; }
    // Pops
    void pop_back(int ch) {
        --sz;
        h = (h - ch) % MOD;
        if (h < 0) h += MOD;
    }
    void pop_front(int ch) {
        --sz;
        h = (h - 1LL * getPow(sz) * ch) % MOD;
        if (h < 0) h += MOD;
    }
    // Push-pop
    void push_back_pop_front(int pushCh, int popCh) {
        h = ((h - 1LL * getPow(sz - 1) * popCh) * B + pushCh) % MOD;
        if (h < 0) h += MOD;
    }
    // Concatenation
    friend Hasher operator+(const Hasher &a, const Hasher &b) { return Hasher((1LL * a.h * getPow(b.sz) + b.h) % MOD, a.sz + b.sz); }
    // Comparison
    friend bool operator==(const Hasher &a, const Hasher &b) { return make_pair(a.h, a.sz) == make_pair(b.h, b.sz); }
};
template <int B, int MOD>
vector <int> Hasher <B, MOD> :: pows = {1};

typedef Hasher <263, 1000000000 + 7> H1;
typedef Hasher <277, 1000000000 + 9> H2;

/*
	You can give a hint towards the largest string that will be represented via:
	
	H1 :: reserve(MAX_STRING_SIZE);
	...
	
	This acts like an std::vector, meaning that if the hint is not accurate, size doubling will
	occur until the string at hand can safely be represented.
*/