// included in snippet

// 返り値 : gcd(a, b)
// 副作用 : (x, y) を ax + by = gcd(a, b) を満たす (x, y) にする
constexpr long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extGCD(b, a%b, y, x);
    y -= a/b * x;
    return d;
}