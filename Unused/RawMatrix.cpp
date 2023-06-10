// vector をshared_ptr に置き換えたい

template <class T>
struct Matrix {
    T** dat;
    int row, col;

    Matrix(int row, int col) : Matrix(std::vector<std::vector<T>>(row, std::vector<T>(col, T()))) {}
    Matrix(const std::vector<std::vector<T>>& vec) : row(vec.size()) {
        assert(!vec.empty());
        col = vec.front().size();

        init_assign();

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                dat[i][j] = vec[i][j];
            }
        }
    }
    Matrix(const Matrix<T>& other) : row(other.row), col(other.col) {
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col ; ++j) {
                dat[i][j] = other.dat[i][j];
            }
        }
    }
    Matrix(Matrix<T>&& other) : row(other.row), col(other.col) {
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col ; ++j) {
                dat[i][j] = other.dat[i][j];
            }
        }
    }

    Matrix<T> prod(const Matrix<T> b) const {
        // 後でoperator* にしてもよい
        assert(col == b.row);

        Matrix<T> ret(row, b.col);
        for (int i = 0; i < row; ++i) {
            for (int k = 0; k < col; ++k) {
                for (int j = 0; j < b.col; ++j) {
                    ret.dat[i][j] += dat[i][k] * b.dat[k][j];
                }
            }
        }
        return ret;
    }
    std::vector<T> prod(const std::vector<T> v) const {
        int dim = v.size();
        assert(col == dim);
        std::vector<T> ret(dim);

        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < col; ++j) {
                ret[i] += dat[i][j] * v[j];
            }
        }
        return ret;
    }

    Matrix<T> pow(long long k) const {
        assert(row == col && 0 <= k);
        const int n = row;
        Matrix<T> ret(n, n), a(n, n);
        for (int i = 0; i < n; i++) ret.dat[i][i] = 1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) a.dat[i][j] = dat[i][j];
        while (k > 0) {
            if (k & 1) ret = ret.prod(a);
            a = a.prod(a);
            k >>= 1;
        }
        return ret;
    }

    void init_assign() {
        dat = new T*[row];
        for (int i = 0; i < row; ++i) {
            dat[i] = new T[col];
        }
    }

    ~Matrix() {
        for (int i = 0; i < row; ++i) {
            delete[] dat[i];
        }
        delete[] dat;
    }
};