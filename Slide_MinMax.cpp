#include<bits/stdc++.h>

/**
* @brief Slide minimum algorithm
* @param a vector with typename T
* @param len length of ranges that acquires minimum value
* @return vector of indices which attains { min{a[0], ... , a[len-1]}, min{a[1], ... , a[len]}, min{a[n-len], ... , a[n-1]} }
*/
template<typename T>
std::vector<int> range_min(const std::vector<T>& a, int len) {
    const int n = a.size();
    assert(1 <= len && len <= n);
    std::vector<int> ret(n - len + 1);
    std::deque<int> que;

    for(int i = 0; i < n; ++i) {
        // 不等式判定に等号を入れないと最小indexを、等号を入れると最大indexを返す
        while(!que.empty() && a[que.back()] > a[i])
            que.pop_back();
        que.push_back(i);

        if(i - len + 1 >= 0) {
            if(que.front() < i - len + 1) que.pop_front();
            ret[i - len + 1] = que.front();
        }
    }
    return ret;
}


/**
* @brief Slide maximum algorithm
* @param a vector with typename T
* @param len length of ranges that acquires maximum value
* @return vector of indices which attains { max{a[0], ... , a[len-1]}, max{a[1], ... , a[len]}, max{a[n-len], ... , a[n-1]} }
*/
template<typename T>
std::vector<int> range_max(const std::vector<T>& a, int len) {
    const int n = a.size();
    assert(1 <= len && len <= n);
    std::vector<int> ret(n - len + 1);
    std::deque<int> que;

    for(int i = 0; i < n; ++i) {
        // 不等式判定に等号を入れないと最小indexを、等号を入れると最大indexを返す
        while(!que.empty() && a[que.back()] < a[i])
            que.pop_back();
        que.push_back(i);

        if(i - len + 1 >= 0) {
            if(que.front() < i - len + 1) que.pop_front();
            ret[i - len + 1] = que.front();
        }
    }
    return ret;
}