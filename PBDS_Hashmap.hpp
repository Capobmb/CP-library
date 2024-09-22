#include <bits/stdc++.h>
// ---------------------

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T, class U>
using hash_table = gp_hash_table<T, U, std::hash<T>>;
template <class T, class U>
bool count(hash_table<T, U>& mp, T&& key) {
    return mp.find(key) != mp.end();
}

struct llhash {
    long long seed;
    llhash()
        : seed(std::chrono::high_resolution_clock::now()
                   .time_since_epoch()
                   .count()) {}
    long long operator()(long long x) const { return x ^ seed; }
};
// using robust_hash_table = gp_hash_table<long long, long long, llhash>;
