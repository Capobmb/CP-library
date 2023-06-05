#include <bits/stdc++.h>
// using namespace std;


/* mexset: mexを対数オーダーで返す
    - bool insert   (ll x)     : xを追加する；xが追加された場合true, すでに含まれている場合false
    - bool contains (ll x)     : xが含まれている場合true, そうでない場合false
    - ll   mex      (ll x = 0) : x以上のmexを返す

    Reference : https://rsk0315.hatenablog.com/entry/2020/10/11/125049
*/
struct mexset {
private:
    std::set<std::pair<long long, long long>> s;
public:
    mexset() {
        s.emplace(LLONG_MIN, LLONG_MIN);
        s.emplace(LLONG_MAX, LLONG_MAX);
    }
    
    bool contains(long long x) const {
        auto it = std::prev(s.lower_bound(std::make_pair(x+1, x+1)));
        auto [l, u] = *it;
        return l <= x && x <= u;
    }

    bool insert(long long x) {
        auto nit = s.lower_bound(std::make_pair(x+1, x+1));
        auto it = std::prev(nit);
        auto [l, u] = *it;
        auto [nl, nu] = *nit;
        if (l <= x && x <= u) return false;
        if (u == x-1) {
            if (nl == x+1) {
                s.erase(it);
                s.erase(nit);
                s.emplace(l, nu);
            }
            else {
                s.erase(it);
                s.emplace(l, x);
            }
        }
        else {
            if (nl == x+1) {
                s.erase(nit);
                s.emplace(x, nu);
            }
            else {
                s.emplace(x, x);
            }
        }
        return true;
    }

    long long mex(long long x = 0) const {
        auto [l, u] = *std::prev(s.lower_bound(std::make_pair(x+1, x+1)));

        if (l <= x && x <= u) return u+1;
        return x;
    }
};