#include<bits/stdc++.h>
#include<atcoder/all>

/* inversion_number
    返り値：v の転倒数
    注意：v は座標圧縮済みである必要がある i.e. 0 <= v[i] < v.size() である必要がある
    計算量 : O(LlogL) ; L=v.size()
*/
template<typename T>
long long inversion_number(const std::vector<T>& v) {
    int n = v.size();
    long long ret = 0;
    atcoder::fenwick_tree<long long> fw(n);
    for(int i = 0; i < n; i++) {
        ret += fw.sum(v[i] + 1, n);
        fw.add(v[i], 1LL);
    }
    return ret;
}