#include <bits/stdc++.h>
using namespace std;

/* Rerooting: 全方位木 DP
    問題ごとに以下を書き換える
    - 型DPと単位元
    - 型DPに対する二項演算 merge
    - まとめたDPを用いてその頂点を根とする(新たな)部分木のDPを計算して返す add_root
    計算量: O(N)

    Reference : https://algo-logic.info/tree-dp/
*/
struct Rerooting {
    /* start 問題ごとに書き換え */
    struct DP {  // DP の型
        long long dp;
        DP(long long dp_) : dp(dp_) {}
    };
    // グラフの定義
    struct Edge {
        int to;
        Edge (int _to) : to(_to) {} // (modified)
    };
    const DP identity = DP(-1);  // 単位元(末端の値は add_root(identity) になるので注意)
    function<DP(DP, DP)> merge = [](DP dp_cum, DP d) -> DP {
        return DP(max(dp_cum.dp, d.dp));
    };
    function<DP(DP)> add_root = [](DP d) -> DP {
        return DP(d.dp + 1);
    };

    /* end 問題ごとに書き換え */
    using Graph = vector<vector<Edge>>;

    vector<vector<DP>> dp;  // dp[v][i]: vから出るi番目の有向辺に対応する部分木のDP
    vector<DP> ans;         // ans[v]: 頂点vを根とする木の答え
    Graph G;

    Rerooting(int N) : G(N) {
        dp.resize(N);
        ans.assign(N, identity);
    }

    void add_edge(int a, int b) {
        // G[a].push_back({b}); // (modified)
        G[a].emplace_back(b);
    }
    void build() {
        dfs(0);            // 普通に木DP
        bfs(0, identity);  // 残りの部分木に対応するDPを計算
    }

    DP dfs(int v, int p = -1) {  // 頂点v, 親p
        DP dp_cum = identity;
        int deg = G[v].size();
        dp[v] = vector<DP>(deg, identity);
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to; // u : vの子
            if (u == p) continue;
            dp[v][i] = dfs(u, v);
            dp_cum = merge(dp_cum, dp[v][i]);
        }
        return add_root(dp_cum);
    }
    void bfs(int v, const DP& dp_p, int p = -1) {  // bfs だが、実装が楽なので中身は dfs になっている
        int deg = G[v].size();
        for (int i = 0; i < deg; i++) {  // 前のbfsで計算した有向辺に対応する部分木のDPを保存
            if (G[v][i].to == p) dp[v][i] = dp_p;
        }
        // 累積merge用の配列 (1-indexed)
        // dp_l[i] : 左からi番目までの有向辺たちのdpのmerge和
        // dp_r[i] : 左からi番目よりも右側 (=左からi+1番目以降の)有向辺たちのdpのmerge和
        vector<DP> dp_l(deg + 1, identity), dp_r(deg + 1, identity);
        for (int i = 0; i < deg; i++) {
            dp_l[i + 1] = merge(dp_l[i], dp[v][i]);
        }
        for (int i = deg - 1; i >= 0; i--) {
            dp_r[i] = merge(dp_r[i + 1], dp[v][i]);
        }

        ans[v] = add_root(dp_l[deg]);  // 頂点 v の答え

        for (int i = 0; i < deg; i++) {  // 一つ隣の頂点に対しても同様に計算
            int u = G[v][i].to;
            if (u == p) continue;
            bfs(u, add_root(merge(dp_l[i], dp_r[i + 1])), v);
        }
    }
};


// Sample code
// 問題：木の全ての頂点i に対し、その頂点から最も遠い頂点を求める

int main() {
    int N;
    cin >> N;
    Rerooting reroot(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        reroot.add_edge(u, v);
        reroot.add_edge(v, u);
    }
    reroot.build();

    for (int i = 0; i < N; i++) {
        cout << "頂点" << i + 1 << ": " << reroot.ans[i].dp << endl;
    }
}