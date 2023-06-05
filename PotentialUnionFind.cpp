#include <bits/stdc++.h>

template<class Weight>
struct potential_unionfind {
    std::vector<int> par;
    std::vector<int> rank;
    std::vector<Weight> diff_weight; // 親との重みの差分

    // e : (和の)単位元
    potential_unionfind(int n = 1, Weight e = 0) : par(n), rank(n), diff_weight(n, e) {
        std::iota(par.begin(), par.end(), Weight(0));
    }

    int root(int x) {
        if (par[x] == x) return x;

        int r = root(par[x]);
        diff_weight[x] += diff_weight[par[x]];
        return par[x] = r;
    }

    // return weight[x] which is weight compared to root's weight(0)
    Weight weight(int x) {
        root(x);
        return diff_weight[x];
    }

    // weight[y] = weight[x] + w となるように x, y をmerge
    // ただし情報が矛盾していないことを前提とする
    bool merge(int x, int y, Weight w) {
        w += weight(x); w -= weight(y);
        x = root(x); y = root(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) std::swap(x, y), w = -w;
        if (rank[x] == rank[y]) ++rank[x];
        par[y] = x;
        diff_weight[y] = w;
        return true;
    }

    // return weight(y) - weight(x) 
    Weight diff(int x, int y) {
        return weight(y) - weight(x);
    }

    bool is_same(int x, int y) {
        return root(x) == root(y);
    }
};

// verified : D - people on a line