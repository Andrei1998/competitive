// String Hasher
template <int B, int MOD>
struct Hasher {
    // Static hash function
    template <typename iter_type>
    static int hash(iter_type begin, iter_type end) {
        int h = 0;
        for (iter_type it = begin; it != end; ++it)
            h = (1LL * h * B + *it) % MOD;
        return h;
    }
    // Data members
    vector <int> pows, h;
    // Constructor
    template <typename iter_type>
    Hasher(iter_type begin, iter_type end) {
        const int sz = end - begin + 1;
        pows.resize(sz), h.resize(sz);
        pows[0] = 1, h[0] = 0;
        for (iter_type it = begin; it != end; ++it) {
            pows[it - begin + 1] = (1LL * pows[it - begin] * B) % MOD;
            h[it - begin + 1] = (1LL * h[it - begin] * B + (*it)) % MOD;
        }
    }
    // Continuous subsequence hash query[l, r]
    int hash(const int l, const int r) {
        int res = (h[r + 1] - 1LL * h[l] * pows[r - l + 1]) % MOD;
        if (res < 0)
            res += MOD;
        return res;
    }
};

typedef Hasher <263, 1000000000 + 7> H1;
typedef Hasher <277, 1000000000 + 9> H2;
