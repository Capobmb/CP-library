#include<bits/stdc++.h>

// --------------


/*
const long long RANDOM = std::chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    long long operator()(long long x) const { return x ^ RANDOM; }
};
*/

#include <ext/pb_ds/assoc_container.hpp>
template<class T, class U>using hash_table =  __gnu_pbds::gp_hash_table<T, U>;

// CodeForces に出す場合かつ整数型がkeyの場合、下もコピペ
struct chash {
    long long seed;
    chash() : seed(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {}
    long long operator()(long long x) const { return x ^ seed; }
};
using robust_hash_table = __gnu_pbds::gp_hash_table<long long, long long, chash>;
