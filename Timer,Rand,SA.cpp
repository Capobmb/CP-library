#include<bits/stdc++.h>


// ---------------
// std::mt19937 rand_engine(std::random_device{}());

std::mt19937 rand_engine(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

std::uniform_real_distribution<double> distribution(36.0, 37.0);
// double r = distribution(rand_engine);

// double get_time() { return double(clock()) / CLOCKS_PER_SEC; }


unsigned int rand_int() { 
    // xor shift 128
    static unsigned int x = 123456789;
    static unsigned int y = 362436069;
    static unsigned int z = 521288629;
    // static unsigned int w = 88675123;
    static unsigned int w = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() & std::numeric_limits<int>::max();
    unsigned int t;

    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
double rand_prob() { 
    static constexpr unsigned int _INF = 1U << 31;
    return (rand_int() & _INF) / (double)_INF;
}

struct Rand {
    Rand(){}
    // xor shift 128
    unsigned int rand_int() { 
        static unsigned int x = 123456789;
        static unsigned int y = 362436069;
        static unsigned int z = 521288629;
        // static unsigned int w = 88675123;
        static unsigned int w = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() & std::numeric_limits<int>::max();
        unsigned int t;

        t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    unsigned int rand_int(int r) {
        assert(r > 0);
        return rand_int() % r;
    }
    // random int between [l, r)
    unsigned int rand_int(int l, int r) {
        return l + rand_int(r - l);
    }
    double rand_prob() { 
        static constexpr unsigned int _INF = 1U << 31;
        return (rand_int() & _INF) / (double)_INF;
    }
} RAND;

struct Timer {
    static constexpr int64_t CYCLES_PER_SEC = 
    #ifdef LOCAL
        1100000000LL;
    #else
        2800000000LL; // コードテストでは3e9 (3GHz)
    #endif
    static constexpr double TIME_LIMIT = 4.8;
	int64_t start;
	Timer() { reset(); }
	void reset() { start = getCycle(); }
	void plus(double a) { start -= (a * CYCLES_PER_SEC); }
	double get() { return (double)(getCycle() - start) / CYCLES_PER_SEC; }
    bool time_check() { return get() < TIME_LIMIT; }
	inline int64_t getCycle() {
		uint32_t low, high;
		__asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
		return ((int64_t)low) | ((int64_t)high << 32);
	}
} TIMER;


void SA() {
    // 温度のパラメータ よしなに決める
    double start_temp = 100, end_temp = 2;

    // 開始時刻, 焼きなましに使う時間
    double start_time = timer.get(), TIME_COURSE = 1.9;

    int howmuchiter = 0;
    auto oldscore = 0;
    while(++howmuchiter, timer.get() - start_time <= TIME_COURSE) {
            double now_time = timer.get();
            if(now_time - start_time > TIME_COURSE) break;

            auto newscore = 0;
        
            // いろいろなもので温度を設定
            double temp = start_temp + (end_temp - start_temp) * ((now_time - start_time) / TIME_COURSE);

            double prob = exp( (newscore - oldscore) / temp );
        
            if(prob > rand_prob()) {
                // 採用
                oldscore = newscore;
            }
    }
}