#include <bits/stdc++.h>
using namespace std;

/*
    LCA(G, root): 木 G に対する根を root として Lowest Common Ancestor を求める構造体
    前処理: O(nlogn)時間, O(nlogn)空間

    get_lca(u,v): u と v の LCA を求める。計算量 O(logn)
    get_dist(u,v): u と v の距離を求める。計算量 O(logn)
    is_on_path(u,v,a): u-v パス上に 点a があるか判定する。計算量 O(logn)
*/

struct LCA {
    
  public:
    // コンストラクタ(隣接リストG, 根root=0 を指定)
    LCA(const vector<vector<int>> &G, int root = 0) : n(G.size()) {
        K = 1;
        while ((1 << K) < n) K++;

        parent.assign(K, vector<int>(n, -1));
        dist.assign(n, -1);

        dfs(G, root, -1, 0);

        // ダブリング用テーブルの構築
        for (int k = 0; k + 1 < K; k++) {
            for (int v = 0; v < n; v++) {
                if (parent[k][v] < 0) {
                    parent[k + 1][v] = -1;
                } else {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
    }

    int get_lca(int u, int v) {
        // u の方が深いとする
        if (dist[u] < dist[v]) swap(u, v); 

        // LCA までの距離を同じにするために uを遡らせる
        for (int k = 0; k < K; k++) {
            if ((dist[u] - dist[v]) >> k & 1) {
                u = parent[k][u];
            }
        }
        // 二分探索で LCA を求める
        if (u == v) return u;
        for (int k = K - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
    
    int get_dist(int u, int v) {
        return dist[u] + dist[v] - 2 * dist[get_lca(u, v)];
    }
    bool is_on_path(int u, int v, int a) {
        return get_dist(u, a) + get_dist(a, v) == get_dist(u, v);
    }

  private:
    // dfsをして根からの距離と1つ先の頂点を求める
    void dfs(const vector<vector<int>> &G, int now, int p, int d) { // グラフG, 今の頂点now, vの親p, 根からの距離d
        parent[0][now] = p;
        dist[now] = d;
        for (auto to : G[now]) {
            if (to != p) dfs(G, to, now, d + 1);
        }
    }

    vector<vector<int>> parent;  // parent[k][u]:= u の 2^k 先の親
    vector<int> dist;            // root からの距離
    int n, K;                    // 頂点数, N以上最小の2べきの指数
};