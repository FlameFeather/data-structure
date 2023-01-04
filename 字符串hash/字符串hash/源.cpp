struct string_hash
{
    static constexpr int p[2] = { 223333333, 773333333 };
    static constexpr int mod[2] = { 1000000033, 1000002233 };
    long long n;
    vector<vector<long long> > h, rh, pw;

    string_hash(string s) : n(s.size()), h(2, vector<long long>(n + 1)), rh(2, vector<long long>(n + 1)), pw(h) {
        pw[0][0] = pw[1][0] = 1;
        for (int i = 1; i <= n; ++i) pw[0][i] = pw[0][i - 1] * p[0] % mod[0], pw[1][i] = pw[1][i - 1] * p[1] % mod[1];
        for (int i = 1; i <= n; ++i) h[0][i] = (h[0][i - 1] * p[0] + s[i - 1]) % mod[0], h[1][i] = (h[1][i - 1] * p[1] + s[i - 1]) % mod[1];
        for (int i = n - 1; i >= 0; --i) rh[0][i] = (rh[0][i + 1] * p[0] + s[i]) % mod[0], rh[1][i] = (rh[1][i + 1] * p[1] + s[i]) % mod[1];
    }

    long long get(int i, int j)//ÕýÐò
    {
        i--, j--;
        assert(0 <= i && i <= j && j < n);
        return (((h[0][j + 1] - h[0][i] * pw[0][j - i + 1] % mod[0] + mod[0]) % mod[0]) << 30)
            + (h[1][j + 1] - h[1][i] * pw[1][j - i + 1] % mod[1] + mod[1]) % mod[1];
    }

    long long get_r(int i, int j)//ÄæÐò
    {
        i--, j--;
        assert(0 <= i && i <= j && j < n);
        return (((rh[0][i] - rh[0][j + 1] * pw[0][j - i + 1] % mod[0] + mod[0]) % mod[0]) << 30)
            + (rh[1][i] - rh[1][j + 1] * pw[1][j - i + 1] % mod[1] + mod[1]) % mod[1];
    }

};
