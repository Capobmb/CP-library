#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UnionFind {
public:
    UnionFind(int N) { // constructor
        Par.resize(N);
        for(int i = 0; i < N; i++) Par[i] = i;
        Size.assign(N, 1);
        Density = N;
    }
    int root(int x) { // 再帰的にxの根を求め、その過程で経路圧縮も行う
        if (Par[x] == x) return x;
        // xを親のrootにつなぎ直す
        return Par[x] = root(Par[x]);
    }
    void merge(int x, int y) { // xとyの木を併合,事前にroot(x)とroot(y)も呼び出す
        int rx = root(x);
        int ry = root(y);
        if(rx == ry) return;
        // でかい方の木に統合
        if(Size[rx]<Size[ry]) swap(rx,ry);
        Size[rx] += Size[ry];
        Par[ry] = rx;
        Density--;
    }
    bool is_same(int x, int y) { return root(x)==root(y); }
    // xの含まれる素集合のサイズ
    int unionsize(int x) { return Size[root(x)]; }

    int density() { return Density; }
private :
    vector<int> Par; // Par[i]: iの(直接の)親
    vector<int> Size; // Size[i]: iが根である素集合の要素数
    int Density = 0;
};
// Kruskal法を用いて 最小全域木のコスト和を返す
// MST_sum ( 辺集合 edges (u, v, cost), 頂点数 n )
ll MST_sum(vector<tuple<int,int,int>>& edges, int n) {
    UnionFind uf(n);
    sort(edges.begin(), edges.end(), [](const auto& x, const auto& y){
        return get<2>(x) < get<2>(y);
    });
    int edge_cnt = 0;
    ll sum = 0;
    for (auto [u, v, cost] : edges) {
        if(edge_cnt == n-1) break; // 不要かもしれない
        if(!uf.is_same(u, v)) {
            uf.merge(u, v);
            sum += cost;
            edge_cnt++;
        }
    }
    return sum;
}
// Kruskal法を用いて 最小全域木を構成する辺集合を返す
// MST_edges ( 辺集合 edges (u, v, cost), 頂点数 n )
vector<tuple<int,int,int>> MST_edges(vector<tuple<int,int,int>>& edges, int n) {
    UnionFind uf(n);
    sort(edges.begin(), edges.end(), [](const auto& x, const auto& y){
        return get<2>(x) < get<2>(y);
    });
    vector<tuple<int,int,int>> ret;
    int edge_cnt = 0;
    for (auto [u, v, cost] : edges) {
        if(edge_cnt == n-1) break; // 不要かも知れない
        if(!uf.is_same(u, v)) {
            uf.merge(u, v);
            ret.emplace_back(u, v, cost);
            edge_cnt++;
        }
    }
    return ret;
}