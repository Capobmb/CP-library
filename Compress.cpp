#include <bits/stdc++.h>
using namespace std;

/* compress
    X を座標圧縮して書き換える（副作用）
    返り値: ソート済みの値を格納した配列vals ; vals[i] = 座圧したi番目の値
    計算量: O(nlogn)
*/
template <typename T>
vector<T> compress(vector<T> &X) {
    vector<T> vals = X;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < (int)X.size(); i++) {
        X[i] = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
    }
    return vals;
}