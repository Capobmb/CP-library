#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 配列を破壊的に座標圧縮する
 * @return vector<T> vals: 値を昇順に格納した配列. vals[i] = 座圧したi番目の値
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