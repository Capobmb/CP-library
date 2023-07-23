#include <utility>
#include <vector>

/**
 * @brief Solve max rectangle in histogram problem.
 * @param v All the element must be non-negative.
 */
template <typename T>
T max_rectangle(std::vector<T> v) {
    // push sentinel
    v.emplace_back();
    int n = (int)v.size();

    // (height, pos). height is strictly increasing after each loop.
    std::vector<std::pair<T, int>> st;
    st.reserve(n);

    T mxv{};
    for (int i = 0; i < n; i++) {
        if (st.empty() || st.back().first < v[i]) {
            st.emplace_back(v[i], i);
            continue;
        }

        int last = i;
        while (!st.empty() && st.back().first >= v[i]) {
            mxv = std::max(mxv, st.back().first * (i - st.back().second));
            last = st.back().second;
            st.pop_back();
        }
        st.emplace_back(v[i], last);
    }

    return mxv;
}