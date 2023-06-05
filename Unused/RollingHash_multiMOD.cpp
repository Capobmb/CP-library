#include <bits/stdc++.h>
using namespace std;

// 構築 in O(N) time, O(N) space
template <int mod_size = 2, int base = 9973>
struct rolling_hash {
    int n;
    vector<long long> hs[mod_size], pw[mod_size];
    static constexpr long long mods[] = {999999937LL, 1000000007LL, 1000000009LL, 998244353LL};

    rolling_hash(){}
    rolling_hash(const string &s) {
        n = s.size();
        for (int i = 0; i < mod_size; i++) {
            hs[i].assign(n+1,0);
            pw[i].assign(n+1,0);
            hs[i][0] = 0;
            pw[i][0] = 1;
            for (int j = 0; j < n; j++) {
                pw[i][j+1] = pw[i][j]*base%mods[i];
                hs[i][j+1] = (hs[i][j]*base+s[j])%mods[i];
            }
        }
    }
    // get hash of S[l:r] in mods[i] in O(1)
    inline long long gethash(int l, int r, int i) const {
        assert(0 <= i && i < mod_size);
        long long res = (hs[i][r]-hs[i][l]*pw[i][r-l])%mods[i];
        if (res < 0) res += mods[i];
        return res;
    }
    // get hashes of S[l:r] in all mods in O(1)
    inline vector<long long> gethash_all(int l, int r) const {
        vector<long long> res(mod_size);
        for(int i = 0; i < mod_size; i++) res[i] = gethash(l, r, i);
        return res;
    }
    // return S[l1:r1] == S[l2:r2] in O(1)
    inline bool is_same(int l1, int r1, int l2, int r2) const {
        bool res=true;
        for(int i = 0; i < mod_size; i++) res &= gethash(l1, r1, i) == gethash(l2, r2, i);
        return res;
    }
    // get length of LCP of S[l1:r1] and S[l2:r2] in O(logN)
    int getLCP(int l1, int r1, int l2, int r2) const {
        int len = std::min(r1 - l1, r2 - l2);
        int ok = -1, ng = len + 1;
        while(ng - ok > 1) {
            int mid = (ok + ng) / 2;
            (is_same(l1, l1 + mid, l2, l2 + mid) ? ok : ng) = mid;
        }
        return ok;
    }
};

