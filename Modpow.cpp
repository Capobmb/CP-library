/// @return a^n mod MOD
constexpr long long modpow(long long a, long long n, long long MOD) {
    long long res = 1;
    a %= MOD;
    while(n > 0) {
        if(n & 1) res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}

/// @return a^n
long long powll(long long a, long long n) {
    long long res = 1;
    while(n > 0) {
        if(n & 1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}