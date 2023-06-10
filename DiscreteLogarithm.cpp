#include<bits/stdc++.h>

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

/**
 * @brief Discrete Logarithmic Function utilizing Baby-step Giant-step Algorithm. Time Complexity = O(√p).
 * @param p Prime
 * @return Minimum X such that a^x = b mod p <=> x = log_a(b) mod p. If not found -1.
 */
long long discrete_log(long long a, long long b, long long p) {
    long long r = sqrt(p) + 1;

    std::unordered_map<long long, long long> table;
    long long ap = 1;
    for(int i = 0; i < r; i++) {
        if(!table.count(ap)) table[ap] = i;
        ap = ap * a % p;
    }

    const long long gamma = modpow(modpow(a, r, p), p-2, p);
    long long gp = 1;
    for(long long i = 0; i < r; i++) {
        if(table.count(gp * b % p)) {
            return i * r + table[gp * b % p];
        }
        gp = gp * gamma % p;
    }
    return -1;
}