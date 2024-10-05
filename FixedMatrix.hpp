#include <cstddef>
#include <vector>
#include <cassert>

template <class T, size_t N>
struct FixedMatrix {
    T dat[N][N];

    FixedMatrix() {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                dat[i][j] = T();
    }

    static FixedMatrix identity() {
        FixedMatrix ret;
        for (size_t i = 0; i < N; ++i)
            ret.dat[i][i] = T(1);
        return ret;
    }

    T* operator[](size_t i) { return dat[i]; }
    const T* operator[](size_t i) const { return dat[i]; }

    FixedMatrix prod(const FixedMatrix& b) const {
        FixedMatrix ret;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < N; ++k) {
                const T aik = dat[i][k];
                for (size_t j = 0; j < N; ++j) {
                    ret.dat[i][j] += aik * b.dat[k][j];
                }
            }
        }
        return ret;
    }

    std::vector<T> prod(const std::vector<T>& v) const {
        assert(v.size() == N);
        std::vector<T> ret(N);
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                ret[i] += dat[i][j] * v[j];
            }
        }
        return ret;
    }

    FixedMatrix pow(long long k) const {
        assert(k >= 0);
        FixedMatrix ret = identity();
        FixedMatrix a = *this;
        while (k > 0) {
            if (k & 1) ret = ret.prod(a);
            a = a.prod(a);
            k >>= 1;
        }
        return ret;
    }

    // vectorからFixedMatrixへの変換コンストラクタ
    FixedMatrix(const std::vector<std::vector<T>>& vec) {
        assert(vec.size() == N && vec[0].size() == N);
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                dat[i][j] = vec[i][j];
    }

    // FixedMatrixからvectorへの変換
    std::vector<std::vector<T>> to_vector() const {
        std::vector<std::vector<T>> ret(N, std::vector<T>(N));
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                ret[i][j] = dat[i][j];
        return ret;
    }
};