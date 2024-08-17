#include <cassert>
#include <chrono>
#include <limits>

struct Rand {
    Rand() {}
    // xor shift 128
    unsigned int rand_int() {
        static unsigned int x = 123456789;
        static unsigned int y = 362436069;
        static unsigned int z = 521288629;
        // static unsigned int w = 88675123;
        static unsigned int w =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count() &
            std::numeric_limits<int>::max();
        unsigned int t;

        t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    unsigned long long rand_ll() {
        const unsigned int upper = rand_int();
        const unsigned int lower = rand_int();
        return (static_cast<unsigned long long>(upper) << 32) | lower;
    }
    unsigned int rand_int(int r) {
        assert(r > 0);
        return rand_int() % r;
    }
    unsigned long long rand_ll(unsigned long long r) {
        assert(r > 0);
        return rand_ll() % r;
    }
    // random int between [l, r)
    unsigned int rand_int(int l, int r) {
        assert(l < r);
        return l + rand_int(r - l);
    }
    // random long long between [l, r)
    unsigned long long rand_ll(unsigned long long l, unsigned long long r) {
        assert(l < r);
        return l + rand_ll(r - l);
    }
    // random double between [0, 1)
    double rand_prob() {
        static constexpr unsigned int _INF = std::numeric_limits<unsigned int>::max();
        return static_cast<double>(rand_int()) / _INF;
    }
} RAND;
