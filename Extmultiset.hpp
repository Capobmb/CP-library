#include<set>
#include<cassert>

template <typename T>
struct ext_multiset {
    std::multiset<T> st;
    using iterator = typename std::multiset<T>::iterator;

    void clear() { st.clear(); }
    int count(const T& x) { return st.count(x); }
    bool contains(const T& x) { return st.find(x) != st.end(); }
    bool has_greater_equal(const T& x) { return st.lower_bound(x) != st.end(); }
    iterator greater_equal(const T& x) { return st.lower_bound(x); }
    bool has_greater(const T& x) { return st.upper_bound(x) != st.end(); }
    iterator greater(const T& x) { return st.upper_bound(x); }
    bool has_less_equal(const T& x) { return st.upper_bound(x) != st.begin(); }
    iterator less_equal(const T& x) { return std::prev(st.upper_bound(x)); }
    bool has_less(const T& x) { return st.lower_bound(x) != st.begin(); }
    iterator less(const T& x) { return std::prev(st.lower_bound(x)); }
    void insert(const T& x) { st.insert(x); }
    int size() const noexcept { return (int)st.size(); }
    template <typename... Args>
    void emplace(Args&&... args) {
        st.emplace(args...);
    }
    bool empty() const noexcept { return st.empty(); }
    void erase_all(const T& x) { st.erase(x); }

    /**
     * @brief Erase `x`, num times at most.
     */
    void erase_multiple(const T& x, int num) {
        iterator itr = st.find(x);
        while (num-- && itr != st.end()) {
            st.erase(itr);
            itr = st.find(x);
        }
    }
    void erase_one(const T& x) {
        iterator itr = st.find(x);
        if (itr == st.end()) return;
        st.erase(itr);
    }

    T get_min() {
        assert(!st.empty());
        return *st.begin();
    }
    T get_max() {
        assert(!st.empty());
        return *st.rbegin();
    }
    void pop_min() {
        assert(!st.empty());
        st.erase(st.begin());
    }
    void pop_max() {
        assert(!st.empty());
        st.erase(std::prev(st.end()));
    }
};