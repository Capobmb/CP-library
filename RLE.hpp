#include <utility>
#include <vector>

template <class Container>
std::vector<std::pair<typename Container::value_type, int>> RLE_encoding(
    const Container& v) {
    using T = typename Container::value_type;
    const int N = (int)v.size();
    std::vector<std::pair<T, int>> ret;
    for (int l = 0; l < N;) {
        int r = l + 1;
        for (; r < N && v[l] == v[r]; r++) {
        };
        ret.push_back({v[l], r - l});
        l = r;
    }
    return ret;
}

template <class T>
std::vector<T> RLE_decoding(const std::vector<std::pair<T, int>>& v) {
    std::vector<T> ret;
    for (const auto& [x, c] : v) {
        ret.insert(ret.end(), c, x);
    }
    return ret;
}
