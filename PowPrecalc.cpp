#include <vector>
template <long long base = 2, long long MOD = 998244353>
struct power_gen {
    std::vector<long long> v;
    power_gen(int Max) : v(Max) {
        v[0] = 1;
        for (int i = 1; i < Max; ++i) {
            v[i] = v[i - 1] * base % MOD;
        }
    }
    long long operator[](int x) const noexcept { return v[x]; }
};