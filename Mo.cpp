#include<bits/stdc++.h>


/*
    Mo(n) : 区間長nのMo を構築
    mo.push(l, r) : [l, r) というクエリを追加する
    mo.run(add,del,calc) : add(x), del(x), calc() というラムダ式を渡すと、サイズqのvector resが返ってくる。
*/
struct Mo {
    int n, q, width;
    std::vector<int> l, r;

    explicit Mo(int n) : n(n) {}
    // push [l, r)
    void push(int _l, int _r) {
        l.push_back(_l); r.push_back(_r);
    }

    template<typename F, typename G, typename H>
    auto run(const F& add, const G& del, const H& calc) -> std::vector<decltype(calc())> {
        q = l.size();
        assert(0 < q);

        using T = decltype(calc());
        std::vector<T> res(q);
        width = std::max<int>(1, n / std::sqrt(q));
        std::vector<int> que(q);
        std::iota(que.begin(), que.end(), 0);
        std::sort(que.begin(), que.end(), [&](int i, int j) {
            int i_d = l[i] / width, j_d = l[j] / width;
            if (i_d != j_d) return i_d < j_d;
            return (i_d & 1) ? r[i] > r[j] : r[i] < r[j];
        });

        int nl = 0, nr = 0;
        for(int i : que) {
            while (l[i] < nl) add(--nl);
            while (nr < r[i]) add(nr++);
            while (nl < l[i]) del(nl++);
            while (r[i] < nr) del(--nr);

            res[i] = calc();
        }

        return res;
    }
};