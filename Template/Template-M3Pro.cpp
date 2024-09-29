#if !defined(__clang__) && defined(__GNUC__)
#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#ifdef ONLINE_JUDGE
#pragma GCC target("avx2,fma,popcnt,bmi,bmi2")
#endif
#elif defined(__clang__)
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <vector>
#else
#error "We don't know this compiler lol"
#endif
#if __has_include(<atcoder/all>)
    #include <atcoder/all>
    using namespace atcoder;
    std::ostream &operator<<(std::ostream &os, const modint998244353 &a) {return os<<a.val();}
    std::ostream &operator<<(std::ostream &os, const modint1000000007 &a) {return os<<a.val();}
    std::istream &operator>>(std::istream &is, modint998244353 &a) {long long t; is>>t; a=t; return is;}
    std::istream &operator>>(std::istream &is, modint1000000007 &a) {long long t; is>>t; a=t; return is;}
#endif
using namespace std;
// # Type Aliases
using ll = long long;
using ull = unsigned long long;
using ld = long double;
template<class T> using V = vector<T>;
template<class T, class U> using P = pair<T,U>;
template<class T> using max_heap = priority_queue<T>;
template<class T> using min_heap = priority_queue<T,vector<T>,greater<T>>;
// # Repeat Macros
#define OVERLOADER(_1,_2,_3,NAME,...) NAME
#define REP2(i,a,b) for (ll i = (a); i < (ll)(b); ++i)
#define REP(i,n) REP2(i,0,n)
#define rep(...) OVERLOADER(__VA_ARGS__,REP2,REP)(__VA_ARGS__)
#define repd(i,a,b) for (ll i = (ll)(b)-1; i >= (ll)(a); --i)
// # Abbreviation Macros
#define pb push_back
#define eb emplace_back
#define ALL(a) begin(a),end(a)
#define RALL(a) a.rbegin(),a.rend()
// # Fast IO and IO Settings
struct IO_Setting{IO_Setting(){cin.tie(nullptr);ios_base::sync_with_stdio(false);cout<<fixed<<setprecision(15);cerr<<fixed<<setprecision(3);}}io_setting;
// # Input Overloads
template<class T,class U> istream& operator>>(istream& is,P<T,U>&p){return is>>p.first>>p.second;}
template<class T> istream& operator>>(istream& is,V<T>&v){for(T& e:v) is>>e; return is;}
// # Output Overloads
template<class T,class U> ostream& operator<<(ostream& os,const P<T,U>& p){return os<<p.first<<' '<<p.second;}
template<class T> ostream& operator<<(ostream& os,const V<T>& v) {int ss=v.size(); rep(ii,ss) {os<<v[ii]<<(ii+1==ss?"":" ");} return os;}
// # Function Definition
template<class T> T sq(T x) { return x*x; }
template<class T, class U> inline bool chmin(T &a, U b) { if(a>b) {a=b; return 1;} return 0;}
template<class T, class U> inline bool chmax(T &a, U b) { if(a<b) {a=b; return 1;} return 0;}
ll max (ll lhs, ll rhs) {return std::max<ll>(lhs, rhs);}
ll min (ll lhs, ll rhs) {return std::min<ll>(lhs, rhs);}
ll ceil_div(ll a, ll b) { return a / b + ((a ^ b) >= 0 && a % b); }
ll floor_div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
template<class Container> Container reversed(const Container& v) {return Container(v.rbegin(), v.rend());}
template<class Container> Container sorted(const Container& v, bool rev=false) {Container r = v; rev ? sort(r.rbegin(), r.rend()) : sort(r.begin(), r.end()); return r;}
template<class T>void uniqify(V<T>& v){v.erase(unique(ALL(v)),v.end());}
template<class T>V<T> compress(V<T>& v){V<T>vals=v;sort(ALL(vals));uniqify(vals);rep(i,v.size())v[i]=lower_bound(ALL(vals),v[i])-vals.begin();return vals;}
template<class T>V<T> sum_array(const V<T>& v) {int n=v.size(); V<T> sum(n+1); rep(i,n) sum[i+1]=sum[i]+v[i]; return sum;}
template<class T>inline void drop(T&& x) { cout << x << endl; exit(0); }
inline void yesno(bool f) { cout << (f ? "Yes" : "No") << '\n'; }
// # Constant Definition
constexpr char ENDL = '\n';
constexpr ll INF = (1LL<<30)-1; // 問題毎にfit
constexpr ll INFLL = (1LL<<62)-1; // 問題毎にfit
const ld PI = acos(static_cast<long double>(-1));
constexpr int dy[]={0, 1, 0, -1};
constexpr int dx[]={1, 0, -1, 0};
// constexpr int dy[]={0, 1, 1, 1, 0, -1, -1, -1};
// constexpr int dx[]={1, 1, 0, -1, -1, -1, 0, 1};
// # Debug Macro
#ifdef LOCAL
    // #include "CP-library/debug_print.hpp"
    // #define debug(...) debug_impl(__LINE__, __VA_ARGS__)
    // #define debug_impl(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
    #include "cpp-dump/cpp-dump.hpp"
    #define dump(...) cpp_dump(__VA_ARGS__)
    #if __has_include(<atcoder/modint>)
        #include <atcoder/modint>
        namespace cpp_dump::_detail {
        template <int m> inline std::string export_var( const atcoder::static_modint<m> &mint, const std::string &indent, std::size_t last_line_length, std::size_t current_depth, bool fail_on_newline, const export_command &command ) { return export_var(mint.val(), indent, last_line_length, current_depth, fail_on_newline, command); }
        template <int m> inline std::string export_var( const atcoder::dynamic_modint<m> &mint, const std::string &indent, std::size_t last_line_length, std::size_t current_depth, bool fail_on_newline, const export_command &command) { return export_var(mint.val(), indent, last_line_length, current_depth, fail_on_newline, command); }
        }  // namespace cpp_dump::_detail
    #endif // __has_include(<atcoder/modint>)
    namespace cp = cpp_dump;
    CPP_DUMP_SET_OPTION_GLOBAL(max_line_width, 100);
    CPP_DUMP_SET_OPTION_GLOBAL(log_label_func, cp::log_label::line());
    // CPP_DUMP_DEFINE_EXPORT_OBJECT(Type, properties..., methods...);
    #define INLOCALDO(...) do { __VA__ARGS__ } while (false)
#else
    #define debug(...)
    #define dump(...)
    #define INLOCAL(...)
#endif
// using mint = modint1000000007;
// using mint = modint998244353;

int main() {
}