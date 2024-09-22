#include<bits/stdc++.h>


// ---------------
// std::mt19937 rand_engine(std::random_device{}());

std::mt19937 rand_engine(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

std::uniform_real_distribution<double> distribution(36.0, 37.0);
// double r = distribution(rand_engine);

// double get_time() { return double(clock()) / CLOCKS_PER_SEC; }


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