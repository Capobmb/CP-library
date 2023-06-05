// https://judge.yosupo.jp/submission/132915

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,fma,popcnt,bmi,bmi2")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using V = vector<T>;
#define OVERLOADER(_1,_2,_3,NAME,...) NAME
#define REP2(i,a,b) for (ll i = (a); i < (ll)(b); ++i)
#define REP(i,n) REP2(i,0,n)
#define rep(...) OVERLOADER(__VA_ARGS__,REP2,REP)(__VA_ARGS__)
#define ALL(a) begin(a),end(a)
template<class T>void uniqify(V<T>& v){v.erase(unique(ALL(v)),v.end());}
constexpr char ENDL = '\n';
struct IO_Setting{IO_Setting(){cin.tie(nullptr);ios_base::sync_with_stdio(false);cout<<fixed<<setprecision(15);cerr<<fixed<<setprecision(3);}}io_setting;
#ifdef LOCAL
    void debug_out() { cerr << endl; }
    template <class Head, class... Tail> void debug_out(Head H, Tail... T) { cerr << ", " << H; debug_out(T...); }
    #define debug(...) cerr << "Line " << __LINE__ << " : " << #__VA_ARGS__ << " ,,", debug_out(__VA_ARGS__)
#else
    #define debug(...) (void(0))
#endif

template<typename T, bool(*comp)(T, T), T(*e)(), T(*xub)()>
struct LiChaoTree {
    struct Line {
        T a, b; // 傾き,切片
        Line (T _a, T _b) : a(_a), b(_b) {}
        T operator()(T x) const { return a * x + b; }   
    };
    int n;                    // セグ木の最下層サイズ
    std::vector<T> x;         // x座標
    std::vector<Line> dat;    // セグ木のノード 1-indexed. dat[n+i] = x[i].

    LiChaoTree () {}
    // max(x) < xub() , comp(max(a) * xub() + max(b), e()) = false.
    template<typename S>
    LiChaoTree (const std::vector<S>& _x) {
        n = 1;
        while(n < (int)_x.size()) n <<= 1;
        x.assign(n, xub());
        for(int i = 0; i < (int)_x.size(); ++i) x[i] = _x[i];
        dat.assign(2 * n, {0, e()});
    }

    // y = ax+b を追加
    void add_line(T a, T b) {
        add_line(a, b, 1, 0, n);
    }

    // y = ax+b を 区間 [x[l], x[r]) に追加
    void add_segment_at(T a, T b, int l, int r) {
        int nl = n + l, nr = n + r; // ノード番号
        int sz = 1;                 // 今見てるノードの幅
        // l, r は x[l], x[r] に対応. cf.非再帰セグ木
        while(l < r) {
            if (nl & 1) {
                add_line(a, b, nl, l, l + sz);
                ++nl;
                l += sz;
            }
            if (nr & 1) {
                add_line(a, b, nr - 1, r - sz, r);
                --nr;
                r -= sz;
            }
            nl >>= 1, nr >>= 1;
            sz <<= 1;
        }
    }

    // y = ax+b を 区間 [lval, rval) に追加 ;余計な定数倍アリ
    void add_segment(T a, T b, int lval, int rval) {
        add_segment_at(a, b,
            std::lower_bound(x.begin(), x.end(), lval) - x.begin(),
            std::lower_bound(x.begin(), x.end(), rval) - x.begin()
        );
    }

    // x[i] での最小値
    T query_at(int index) const {
        const auto xt = x[index];
        index += n;
        T res = e();
        while(index > 0) {  // note:ここはforloopにできます
            chval(res, dat[index](xt));
            index >>= 1;
        }
        return res;
    }
    // x = val での最小値 ;余計な定数倍アリ
    T query(T val) const {
        return query_at(std::lower_bound(x.begin(), x.end(), val) - x.begin());
    }

  private:
    void chval(T& a, T b) const { // chminみたいな
        if(comp(b, a)) a = b;
    }
    // y = ax+b を ノード番号 nnode (左端l, 右端r）に追加
    void add_line(T a, T b, int nnode, int l, int r) {
        Line B(a, b);
        while(nnode < 2 * n) {  // ノードが存在する限りトップダウンに更新を実行する
            int m = (l + r) >> 1;
            const auto& A = dat[nnode];

            bool ld = comp(B(x[l]), A(x[l]));
            bool md = comp(B(x[m]), A(x[m]));
            bool rd = comp(B(x[r-1]), A(x[r-1]));

            if(md) {
                std::swap(dat[nnode], B);
                ld = !ld, md = !md, rd = !rd;
            }
            if(ld == rd) return;

            if(ld) { // 左側
                nnode = (nnode << 1);
                r = m;
            }
            else {   // 右側
                nnode = (nnode << 1) + 1;
                l = m;
            }
        }
    }
};

using T = long long;
bool comp(T a, T b) {return a < b;}
constexpr T e() {return 1LL<<62;}
constexpr T xub() {return 1LL<<31;}

int main() {
    int n,q; cin>>n>>q;
    V<ll> a(n), b(n), l(n), r(n);
    V<ll> x;
    rep(i, n){
        cin>>l[i]>>r[i]>>a[i]>>b[i];
        x.push_back(l[i]), x.push_back(r[i]);
    }

    V<tuple<ll,ll,ll,ll,ll>> que;
    rep(i, q) {
        int t; cin>>t;
        if(t) {
            ll p; cin>>p;
            que.emplace_back(t,p,0,0,0);
            x.push_back(p);
        }
        else {
            ll tl,tr,ta,tb; cin>>tl>>tr>>ta>>tb;
            que.emplace_back(t,tl,tr,ta,tb);
            x.push_back(tl);
            x.push_back(tr);
        }
    }

    sort(ALL(x)); uniqify(x);

    LiChaoTree<T, comp, e, xub> lct(x);
    rep(i, n) {
        lct.add_segment(a[i], b[i], l[i], r[i]);
    }
    for(auto [t,tl,tr,ta,tb] : que) {
        if(t) {
            auto ans = lct.query(tl);
            if(ans == e()) cout << "INFINITY";
            else cout << ans;
            cout << ENDL;
        }
        else {
            lct.add_segment(ta, tb, tl, tr);
        }
    }
}