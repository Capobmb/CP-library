// included in snippet


#include <bits/stdc++.h>
using namespace std;

struct prime_sieve {
    int MAX;
    std::vector<int> sieve;

    prime_sieve(int _max) : MAX(_max), sieve(_max) {
        std::iota(sieve.begin(), sieve.end(), 0);
        for (int i = 2; i * i < MAX; i++) {
            if (sieve[i] != i) continue;
            for (int j = 2; i * j < MAX; j++) {
                if (sieve[i * j] == i * j) sieve[i * j] = i;
            }
        }
    }

    bool is_prime(int x) const { return sieve[x] == x; }

    std::vector<int> primes() const {
        std::vector<int> p;
        for(int i = 2; i < MAX; i++) {
            if(is_prime(i)) p.push_back(i);
        }
        return p;
    }

    std::vector<std::pair<int, int>> factorize(int n) const {
        std::vector<std::pair<int, int>> res;
        while (n != 1) {
            int p = sieve[n], ex = 0;
            while (sieve[n] == p) {
                n /= p;
                ++ex;
            }
            res.emplace_back(p, ex);
        }
        return res;
    }
};

// --------------------------------------
// constexpr バージョン
// Note : MAX < 2.6 x 10^5

/*
template<int MAX=1000010>
struct ER {
    int sieve[MAX];
    constexpr ER() : sieve() {
        for(int i=0; i<MAX; i++) sieve[i]=i;
        for(int i=2; i*i<MAX; i++) {
            if(sieve[i]!=i) continue;
            for(int j=2; i*j<MAX; j++) {
                if(sieve[i*j]==i*j) sieve[i*j]=i;
            }
        }
    }
    std::vector<std::pair<int,int>> factorize(int n) const {
//昇順で素因数分解を与える std::vector<std::pair<int,int>> res; while (n != 1) {
            int p = sieve[n], ex = 0;
            while(sieve[n] == p) {
                n /= p;
                ++ex;
            }
            res.emplace_back(p, ex);
        }
        return res;
    }
    constexpr bool is_prime(int n) const { return sieve[n] == n; }
};
*/

// constexpr auto er = ER<100010>();
// ER<2000010> er;