// included in snippet

#include <bits/stdc++.h>
using namespace std;

auto dijkstra = [&](int start, auto& dist, const auto& edges) { // dist, edgesはキャプチャに含めても良い
    dist[start] = 0; // 初期位置の距離の初期化
    using pq_elem = std::pair<int, int>; // priority_queueに入れる型
    std::priority_queue<pq_elem, std::vector<pq_elem>, std::greater<pq_elem>> pq;
    pq.emplace(0, start); // 初期位置をpriority_queueへ入れる

    while(pq.size()) {
        auto [d, now] = pq.top(); pq.pop(); // pqから要素を取り出す
        if(d > dist[now]) continue;
        for(auto [to, cost] : edges) { // edgesから要素の取り出し
            if(dist[to] > d + cost) {
                dist[to] = d + cost;
                pq.emplace(dist[to], to); // pqへ要素を入れる
            }
        }
    }
};

/*
using ll = long long;
template<class T> using V = vector<T>;
template<class T, class U> using P = pair<T,U>;
template<typename T> using posteriority_queue = priority_queue<T,vector<T>,greater<T>>;

void dijkstra(int n_, int start_, const vector<vector<P<int,int>>>& edge_, vector<int>& dist_) {
    dist_.assign(n_,INF);
    dist_[start_]=0;
    posteriority_queue<P<int,int>> pq; // {距離,頂点番号}
    pq.push({0,start_});
    while(!pq.empty()) {
        auto [d_from, from] = pq.top();
        pq.pop();
        if(dist_[from]<d_from) continue;
        for(auto [to, cost] : edge_[from]) {
            if(chmin(dist_[to], dist_[from]+cost)) {
                chmin(dist_[to], dist_[from]+cost))
                pq.push({dist_[to],to});
            }
        }
    }
}
*/