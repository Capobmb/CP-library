// included in snippet

#include <bits/stdc++.h>
using namespace std;


template<long long MOD = 998244353>
struct Bicoef {
    std::vector<long long> fac, finv, inv;
    Bicoef(int Max) : fac(Max), finv(Max), inv(Max) {
        assert(Max < MOD);
         fac[0] =  fac[1] = 1;
        finv[0] = finv[1] = 1;
                   inv[1] = 1;
        for (long long i = 2; i < Max; i++) {
            fac[i]  = fac[i-1] * i % MOD;
            inv[i]  = MOD - inv[MOD%i] * (MOD/i) % MOD;
            if(inv[i] == MOD) inv[i] = 0;
            finv[i] = finv[i-1] * inv[i] % MOD;
        }
    }
    inline long long com(int n, int k) const {
        if (n < k) return 0;
        if (n < 0 || k < 0) return 0;
        return fac[n] * finv[k] % MOD * finv[n-k] % MOD;
    }
    inline long long perm(int n, int k) const {
        if (n < k) return 0;
        if (n < 0 || k < 0) return 0;
        return fac[n] * finv[n-k] % MOD;
    }
    inline long long fact(int n) const { return fac[n]; }
};
// Bicoef<998244353> bf(n);

// --------------------------------------

// Constexpr version
// Note: Due to constexpr restriction, MAX <= 2^18 = 262144 ~ 2.6 x 10^5
template<long long MOD = 998244353, size_t MAX = 262144> // MAX must be 
struct Bicoef {    
    constexpr Bicoef() : fac(), finv(), inv() {
        static_assert(MAX < MOD);
        fac[0]  = fac[1]  = 1;
        finv[0] = finv[1] = 1;
                  inv[1]  = 1;
        for (size_t i = 2; i < MAX; i++) {
            fac[i]  = fac[i-1] * i % MOD;
            inv[i]  = MOD - inv[MOD%i] * (MOD/i) % MOD;
            if(inv[i] == MOD) inv[i] = 0;
            finv[i] = finv[i-1] * inv[i] % MOD;
        }
    }
    inline constexpr long long com(int n, int k) const {
        if (n < k) return 0;
        if (n < 0 || k < 0) return 0;
        return fac[n] * finv[k] % MOD * finv[n-k] % MOD;
    }
    inline constexpr long long perm(int n, int k) const {
        if (n < k) return 0;
        if (n < 0 || k < 0) return 0;
        return fac[n] * finv[n-k] % MOD;
    }
    inline constexpr long long fact(int n) const { return fac[n]; }
    
    long long fac[MAX];
    long long finv[MAX];
    long long inv[MAX];
};
// constexpr auto bf = Bicoef<998244353, 262144>(); // constexpr
// Bicoef<998244353, 2000010> bf; // 非constexpr