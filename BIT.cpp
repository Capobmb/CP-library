// included in snippet


#include <bits/stdc++.h>

template <class T>
class BIT {
   public:
    BIT(int n) : bit(n + 1), size(n) {}

    // a[p] += x
    void add(int p, T x) {
        assert(0 <= p && p < size);
        ++p;
        for (; p <= size; p += p & -p) bit[p] += x;
    }

    // sum[l, r) = a[l] + ... + a[r-1]
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= size);
        return internal_sum(r) - internal_sum(l);
    }

    // sum[0, r) = a[0] + ... a[r-1] >= x となる最小のrを与える
    // sum[0, n) < x の場合は r = n+1 を返す。
    // 要件: 各項は非負
    int lower_bound(T x) const {
        int ind = 0, p = 1;  // p : size以上最小の2べき
        while (p < size) p <<= 1;
        for (int len = p; len > 0; len >>= 1) {
            if (ind + len <= size &&
                bit[ind + len] < x) {  // 和がx未満の区間を採用
                x -= bit[ind + len];
                ind += len;
            }
        }
        return ind + 1;
    }

   private:
    std::vector<T> bit;
    int size;
    // sum[0, r) = a[0] + ... + a[r-1]
    T internal_sum(int r) const {
        T res{};
        for (; r > 0; r -= r & -r) res += bit[r];
        return res;
    }
};