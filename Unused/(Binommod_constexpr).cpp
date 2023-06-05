#include<bits/stdc++.h>
using namespace std;

// (ある部分を使うためにはそれより上を全てコピー)

// extended Euclidean Algorithm
// ax + by = gcd(a, b)
// return : gcd(a, b)
template<typename Integer = int_fast64_t>
constexpr Integer extgcd(Integer a, Integer b, Integer &x, Integer &y){
    Integer u = 0, v = 1, q = 0;
    x = v = 1;
    y = u = 0;

    while(b){
        q = a / b;
        x ^= u ^= x ^= u;
        u = u - q * x;
        y ^= v ^= y ^= v;
        v = v - q * y;
        a ^= b ^= a ^= b;
        b = b - q * a;
    }

    return a;
}

// mod inverse(設計が変わるかもしれません)
// return : val^(-1) mod MOD
template<uint_fast64_t MOD, typename Integer = int_fast64_t>
constexpr Integer modinv(Integer val){
    int_fast64_t ret = 0, tmp = 0;

    extgcd<int_fast64_t>(static_cast<int_fast64_t>(val), static_cast<int_fast64_t>(MOD), ret, tmp);

    return static_cast<Integer>(ret > 0 ? ret % MOD : (MOD - (-ret % MOD)));
}

// const expression factorial mod MOD
template<std::size_t N, std::uint_fast64_t MOD>
struct Fact {
    std::uint_fast64_t val[N + 1];

    constexpr Fact() : val() {
        val[0] = 1;
        for (std::size_t i = 1; i <= N; ++i) val[i] = val[i - 1] * i % MOD;
    }
};

// const expression factorial inverse mod MOD
template<std::size_t N, std::uint_fast64_t MOD, std::uint_fast64_t F>
struct IFact {
    std::uint_fast64_t val[N + 1];

    constexpr IFact() : val() {
        val[N] = F;
        for (std::size_t i = N; i; --i) val[i - 1] = val[i] * i % MOD;
    }
};

// const expression binomial mod MOD
// MOD を問題毎に変更する
constexpr std::uint_fast64_t MOD = 1000000007, maxN = 200000; // maxN must be < 262144
constexpr auto fact = Fact<maxN, MOD>();
constexpr auto ifact = IFact<maxN, MOD, modinv<MOD>(fact.val[maxN])>();
constexpr std::uint_fast64_t binommod(std::uint_fast64_t n, std::uint_fast64_t r){
    if(r < 0 || r > n)return 0;
    return fact.val[n] * (ifact.val[r] * ifact.val[n - r] % MOD) % MOD;
}