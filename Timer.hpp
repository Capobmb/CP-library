#include <chrono>
#include <cstdint>

struct Timer {
    static constexpr int64_t CYCLES_PER_SEC =
#ifdef LOCAL
        1100000000LL;
#else
        2800000000LL;  // コードテストでは3e9 (3GHz)
#endif
    static constexpr double TIME_LIMIT = 4.8;
    int64_t start;
    Timer() { reset(); }
    void reset() { start = getCycle(); }
    void plus(double a) { start -= (a * CYCLES_PER_SEC); }
    double get() { return (double)(getCycle() - start) / CYCLES_PER_SEC; }
    bool time_check() { return get() < TIME_LIMIT; }
    inline int64_t getCycle() {
#ifdef LOCAL
        return std::chrono::high_resolution_clock::now()
            .time_since_epoch()
            .count();
#elif defined(__x86_64__)
        uint32_t low, high;
        __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
        return ((int64_t)low) | ((int64_t)high << 32);
#else
#error "Cycle counter not available or not configured"
#endif
    }
} TIMER;
