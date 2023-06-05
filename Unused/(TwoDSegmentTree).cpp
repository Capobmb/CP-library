#include<bits/stdc++.h>
using ll = long long;
using namespace std;

// 使い方よく分からん... minをmaxにかえてます
struct twodsegtree {
    ll H, W;
    vector<vector<ll>> dat;
    twodsegtree(){}
    twodsegtree(vector<vector<ll>> &f) {
        H = W = 1;
        while(H < (ll)f.size()) H <<= 1;
        while(W < (ll)f[0].size()) W <<= 1;
        dat.assign(2*H-1,vector<ll>(2*W-1,0));
        init(f);
    }
    void init(vector<vector<ll>> &f) {
        for (ll i = 0; i < (ll)f.size(); i++)
            for (ll j = 0; j < (ll)f[0].size(); j++)
                dat[i+H-1][j+W-1] = f[i][j];
        for (ll i = 2*H-2; i > H-2; i--)
            for (ll j = W-2; j >= 0; j--)
                dat[i][j] = max(dat[i][2*j+1], dat[i][2*j+2]);
        for (ll i = H-2; i >= 0; i--)
            for (ll j = 0; j < 2*W-1; j++)
                dat[i][j] = max(dat[2*i+1][j], dat[2*i+2][j]);
    }
    ll minimum(ll li, ll lj, ll ri, ll rj) { return minimum_h(li,lj,ri,rj,0,H,0); }
    ll minimum_h(ll li, ll lj, ll ri, ll rj, ll si, ll ti, ll k) {
        if(ri <= si or ti <= li) return 0;
        if(li <= si and ti <= ri) return minimum_w(lj,rj,0,W,k,0);
        const ll mi = (si+ti)/2;
        return max(minimum_h(li,lj,ri,rj,si,mi,2*k+1), minimum_h(li,lj,ri,rj,mi,ti,2*k+2));
    }
    ll minimum_w(ll lj, ll rj, ll sj, ll tj, ll i, ll k) {
        if(rj <= sj or tj <= lj) return 0;
        if(lj <= sj and tj <= rj) return dat[i][k];
        const ll mj = (sj+tj)/2;
        return max(minimum_w(lj,rj,sj,mj,i,2*k+1),minimum_w(lj,rj,mj,tj,i,2*k+2));
    }
};