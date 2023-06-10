std::vector<std::pair<long long, long long>> prime_factorize(long long N) {
    std::vector<std::pair<long long, long long>> res;
    for (long long a = 2; a * a <= N; ++a) {
        if (N % a != 0) continue;
        long long ex = 0;
        while (N % a == 0) {
            ++ex;
            N /= a;
        }
        res.emplace_back(a, ex);
    }
    if (N != 1) res.emplace_back(N, 1);
    return res;
}