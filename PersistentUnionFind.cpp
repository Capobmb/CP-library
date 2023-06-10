#include<bits/stdc++.h>
using namespace std;
// ^-^-------------------

class persistent_union_find {
    template <typename T>
    struct persistent_array {
        struct node;
        using np = node*;
        struct node {
            T data;
            np ch[20] = {};
        };
        np root = nullptr;
        persistent_array() {}
        np get_root() { return root; }
        void destructive_set(int idx, T val, np& t) {
            if (!t) t = new node();
            if (idx == 0) {
                t->data = val;
            } else {
                destructive_set(idx / 20, val, t->ch[idx % 20]);
            }
        }
        np set(int idx, T val, const np& t) {
            np res = new node();
            if (t) {
                memcpy(res->ch, t->ch, sizeof(t->ch));
                res->data = t->data;
            }
            if (idx == 0) {
                res->data = val;
            } else {
                res->ch[idx % 20] = set(idx / 20, val, res->ch[idx % 20]);
            }
            return res;
        }
        T get(int idx, np t) {
            if (!t) return {0, 0};
            if (idx == 0) {
                return t->data;
            } else {
                return get(idx / 20, t->ch[idx % 20]);
            }
        }
    };
    // size, edges. 自由に増やせる
    // size: x がroot のとき -size (< 0), そうでないなら root >= 0
    using PA = persistent_array<pair<int, int>>;
    PA data;

   public:
    using np = PA::np;
    persistent_union_find() {}
    np init(int n) {
        np res = data.get_root();
        for (int i = 0; i < n; i++) data.destructive_set(i, {-1, 0}, res);
        return res;
    }
    pair<bool, np> unite(int x, int y, np t) {
        x = root(x, t);
        y = root(y, t);
        if (x == y) {
            // x の data を更新する。
            auto [nsize, nedge] = data.get(x, t);
            np res = data.set(x, {nsize, nedge + 1}, t);
            return {false, res};
        }
        // -size(x) > -size(y) <=> size(x) < size(y)
        if (data.get(x, t).first > data.get(y, t).first) swap(x, y);
        // size(x) > size(y)
        // x に -size を割り当ててから、y に x を割り当てる。
        auto [xsize, xedge] = data.get(x, t);
        auto [ysize, yedge] = data.get(y, t);
        np res1 = data.set(x, {xsize + ysize, xedge + yedge + 1}, t);
        np res2 = data.set(y, {x, xedge + yedge + 1}, res1);
        return {true, res2};
    }
    int root(int x, np t) {
        if (data.get(x, t).first < 0)
            return x;
        int res = root(data.get(x, t).first, t);
        return res;
    }
    inline bool same(int x, int y, np t) { return root(x, t) == root(y, t); }
    inline pair<int, int> sizeedge(int x, np t) {
        auto [sz, ed] = data.get(root(x, t), t);
        return {-sz, ed};
    }
};
using PUF = persistent_union_find;
using np = PUF::np;