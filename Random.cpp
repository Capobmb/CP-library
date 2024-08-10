#include <chrono>
#include <cassert>

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
    unsigned int rand_int(int r) {
        assert(r > 0);
        return rand_int() % r;
    }
    // random int between [l, r)
    unsigned int rand_int(int l, int r) { return l + rand_int(r - l); }
    double rand_prob() {
        static constexpr unsigned int _INF = 1U << 31;
        return (rand_int() & _INF) / (double)_INF;
    }
} RAND;
