#include<bits/stdc++.h>



// (0, 0) は (0, -1) と同じ偏角となる
// 偏角 -pi/2 ~ 3pi/2 でsort
template<typename T>
std::vector<std::pair<T, T>> argsort(std::vector<std::pair<T, T>>& v) {
    static_assert(std::is_integral_v<T>, "Non-integral type vectors should not be argsorted.");
    using ll = long long;
    // 左半平面, 右半平面, y軸負, y軸正
    std::vector<std::pair<T,T>> l, r, zn, zp;
    for(auto&& p : v) {
        if(p.first < 0) l.push_back(p);
        else if(p.first > 0) r.push_back(p);
        else {
            if(p.second > 0) zp.push_back(p);
            else zn.push_back(p);
        }
    }
    // y1/x1 < y2/x2 <=> y1*x2 < y2*x1
    std::sort(std::begin(r), std::end(r), [](auto l, auto r) {
        return (ll)l.second * r.first < (ll)l.first * r.second;
    });
    // y1/x1 < y2/x2 <=> y1*x2 < y2*x1
    std::sort(std::begin(l), std::end(l), [](auto l, auto r) {
        return (ll)l.second * r.first < (ll)l.first * r.second;
    });

    auto res = v;
    auto itr = std::begin(res);
    itr = std::copy(std::begin(zn), std::end(zn), itr);
    itr = std::copy(std::begin(r), std::end(r), itr);
    itr = std::copy(std::begin(zp), std::end(zp), itr);
    std::copy(std::begin(l), std::end(l), itr);

    return res;
}