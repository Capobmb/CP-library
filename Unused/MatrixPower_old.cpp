template <class T>
std::vector<std::vector<T>> prod(const std::vector<std::vector<T>>& a, const
std::vector<std::vector<T>>& b) {
    const int n = a.size();
    std::vector<std::vector<T>> ret(n, std::vector<T>(n));
    for(int i=0; i<n; i++) {
        for(int k=0; k<n; k++) {
            for(int j=0; j<n; j++) {
                ret[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return ret;
}
template <class T>
std::vector<std::vector<T>> matrixpow(std::vector<std::vector<T>> a, long
long k) {
    const int n = a.size();
    std::vector<std::vector<T>> ret(n, std::vector<T>(n));
    for(int i = 0; i < n; i++) ret[i][i] = 1;
    while (k > 0) {
        if(k & 1) ret = prod(ret, a);
        a = prod(a, a);
        k >>= 1;
    }
    return ret;
}