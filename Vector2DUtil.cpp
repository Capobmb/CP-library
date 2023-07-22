#include <algorithm>
#include <vector>

template <typename T>
std::vector<std::vector<T>> transposed(const std::vector<std::vector<T>>& v) {
    size_t n = v.size(), m = v.front().size();
    std::vector<std::vector<T>> ret(m, std::vector<T>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ret[i][j] = v[j][i];
        }
    }
    return ret;
}

template <typename T>
std::vector<std::vector<T>> clockwise_rotated(
    const std::vector<std::vector<T>>& v) {
    size_t n = v.size(), m = v.front().size();
    std::vector<std::vector<T>> ret(m, std::vector<T>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ret[i][j] = v[n - j - 1][i];
        }
    }

    return ret;
}

template <typename T>
std::vector<std::vector<T>> counterclockwise_rotated(
    const std::vector<std::vector<T>>& v) {
    size_t n = v.size(), m = v.front().size();
    std::vector<std::vector<T>> ret(m, std::vector<T>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ret[i][j] = v[j][m - i - 1];
        }
    }

    return ret;
}

template <typename T>
std::vector<std::vector<T>> trimmed(const std::vector<std::vector<T>>& v,
                                    T&& t = T{}) {
    auto w = v;
    for (int rot_num = 0; rot_num < 4; rot_num++) {
        while (!w.empty() && std::all_of(w.back().begin(), w.back().end(),
                                         [&t](T u) { return u == t; })) {
            // trim bottom line
            w.pop_back();
        }

        w = clockwise_rotated(w);
    }
    return w;
}