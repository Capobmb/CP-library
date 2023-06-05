#include<bits/stdc++.h>


using int128_t = __int128_t;
using uint128_t = __uint128_t;
std::ostream &operator<<(std::ostream &os, int128_t value) {
    std::ostream::sentry s(os);
    if (s) {
        uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = std::end(buffer);
        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0) {
            --d;
            *d = '-';
        }
        int len = std::end(buffer) - d;
        if (os.rdbuf()->sputn(d, len) != len) {
            os.setstate(std::ios_base::badbit);
        }
    }
    return os;
}
int128_t stoi128(std::string &s) {
    int128_t ret = 0;
    for (int i = 0; i < (int)s.length(); i++)
        if ('0' <= s[i] && s[i] <= '9') ret = 10 * ret + s[i] - '0';
    return ret;
}