#include <bits/stdc++.h>


template <class T>
struct Matrix {
    template<class value_type> using V = std::vector<value_type>;
    int row, col;
    V<V<T>> dat;

    /**
     * @brief Construct a new Matrix row * col.
     */
    Matrix(int row, int col) : Matrix(V<V<T>>(row, V<T>(col, T()))) {}
    /**
     * @brief Construct a new Matrix from 2D vector
     */
    Matrix(const V<V<T>>& vec) : row(vec.size()), dat(vec) {
        assert(!vec.empty());
        col = vec.front().size();
    }

    V<T>& operator[](int i) {return dat[i];}

    /**
     * @return THIS * b
     */
    Matrix<T> prod(Matrix<T> b) {
        // global な operator* にしようか
        // vector のほうも
        assert(col == b.row);

        Matrix<T> ret(row, b.col);
        for (int i = 0; i < row; ++i) {
            for (int k = 0; k < col; ++k) {
                for (int j = 0; j < b.col; ++j) {
                    ret[i][j] += dat[i][k] * b[k][j];
                }
            }
        }
        return ret;
    }
    /**
     * @return THIS * b
     */
    V<T> prod(V<T> v) {
        int dim = v.size();
        assert(col == dim);
        V<T> ret(dim);

        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < col; ++j) {
                ret[i] += dat[i][j] * v[j];
            }
        }
        return ret;
    }

    /**
     * @return THIS ^ k
     */
    Matrix<T> pow(long long k) const {
        assert(row == col && 0 <= k);
        const int n = row;
        Matrix<T> ret(n, n), a(dat);
        for (int i = 0; i < n; i++) ret[i][i] = 1;
        while (k > 0) {
            if (k & 1) ret = ret.prod(a);
            a = a.prod(a);
            k >>= 1;
        }
        return ret;
    }
};