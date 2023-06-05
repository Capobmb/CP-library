#include <bits/stdc++.h>


// 経路圧縮(root) + Union-by-Size (merge)
struct UnionFind {
    UnionFind(int n) : parent(n), size(n, 1), edge(n, 0), comps(n) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int root(int x) {
        if (parent[x] == x) return x;
        return parent[x] = root(parent[x]);
    }
    /// @return マージがされたかどうか
    bool merge(int x, int y) {
        int rx = root(x), ry = root(y);
        if(rx == ry) {
            ++edge[rx];
            return false;
        }
        if(size[rx] < size[ry]) std::swap(rx,ry);

        size[rx] += size[ry];
        edge[rx] += edge[ry] + 1;
        parent[ry] = rx;
        --comps;

        return true;
    }
    bool is_same(int x, int y) { return root(x) == root(y); }
    /// @return xの含まれる連結成分の頂点数
    int vertices(int x) { return size[root(x)]; }
    /// @return xの含まれる連結成分内の辺の数
    int edges(int x) {return edge[root(x)]; }
    /// @return 連結成分の数
    int components() const { return comps; }
    std::vector<std::vector<int>> get_components() {
        int n = parent.size();
        std::vector<int> root_buf(n);
        for(int i = 0; i < n; i++) root_buf[i] = root(i);
        std::vector<std::vector<int>> result;
        for(int i = 0; i < n; i++) result[root_buf[i]].push_back(i);

        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

private :
    std::vector<int> parent, size, edge;
    int comps;
};


// --------------------------------------------------------------------

// 注意：UnionFindを更新したら一応KruskalのほうのUnionFindも更新させておくこと！
// クラスカル別に書けるしせんでよさそう！

/*
// 軽量版？古いからいらんかも
struct UnionFind {
public:
    UnionFind(int N) { // constructor
        parent.resize(N);
        for(int i = 0; i < N; i++) parent[i] = i;
        Size.assign(N, 1);
        comps = N;
    }
    int root(int x) { // 再帰的にxの根を求め、その過程で経路圧縮も行う
        if (parent[x] == x) return x;
        // xを親のrootにつなぎ直す
        return parent[x] = root(parent[x]);
    }
    void merge(int x, int y) { // xとyの木を併合,事前にroot(x)とroot(y)も呼び出す
        int rx = root(x);
        int ry = root(y);
        if(rx == ry) return;
        // でかい方の木に統合
        if(Size[rx]<Size[ry]) swap(rx,ry);
        Size[rx] += Size[ry];
        parent[ry] = rx;
        comps--;
    }
    bool is_same(int x, int y) { return root(x)==root(y); }
    // xの含まれる素集合のサイズ
    int unionsize(int x) { return Size[root(x)]; }

    int comps() { return comps; }
private :
    vector<int> parent; // parent[i]: iの(直接の)親
    vector<int> Size; // Size[i]: iが根である素集合の要素数
    int comps = 0;
};
*/