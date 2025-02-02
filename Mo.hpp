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
    template<typename AL, typename AR, typename DL, typename DR, typename C>
    auto run(const AL& add_left, const AR& add_right, const DL& del_left, const DR& del_right, const C& calc) -> std::vector<decltype(calc())> {
        q = l.size();
        assert(0 < q);

        using T = decltype(calc());
        std::vector<T> res(q);
        // If all points (l, r) are interval i.e. l <= r
        //   the total moves are at most N^2 / 2W + QW + O(N)
        //   From AM-GM inequality W ~ sqrt(N^2 / 2Q) = N / sqrt(2Q) minimizes the total cost
        // Otherwise, the total moves are at most N^2 / W + QW + O(N)
        //   In this case, W ~ sqrt(N^2 / Q) = N / sqrt(Q)
        // Here we assume the first case is dominant.
        // Set the width to ensure it is at least 1.
        // Note: If the given points can be assumed to be randomly distributed
        //   a more efficient time complexity can be achieved
        //   ref: https://nyaannyaan.github.io/library/misc/mo.hpp.html
        width = std::max<int>(1, static_cast<double>(n) / std::sqrt(2.0 * q));
        std::vector<int> que(q);
        std::iota(que.begin(), que.end(), 0);
        std::sort(que.begin(), que.end(), [&](int i, int j) {
            int i_d = l[i] / width, j_d = l[j] / width;
            if (i_d != j_d) return i_d < j_d;
            return (i_d & 1) ? r[i] > r[j] : r[i] < r[j];
        });

        int nl = 0, nr = 0;
        for(int i : que) {
            while (l[i] < nl) add_left(--nl);
            while (nr < r[i]) add_right(nr++);
            while (nl < l[i]) del_left(nl++);
            while (r[i] < nr) del_right(--nr);

            res[i] = calc();
        }

        return res;
    }

    template<typename A, typename D, typename C>
    auto run(const A& add, const D& del, const C& calc) -> std::vector<decltype(calc())> {
        return run(add, add, del, del, calc);
    }
};