#include<vector>

struct dynamic_bitset {
    static constexpr int bit_size = 64;
    std::vector<unsigned long long> dat;

    dynamic_bitset(int bits) {
    }
    // count
    // shift operators
    // or, and , xor operators
    // 端っこの扱いがだるすぎる！オワリ
};

#include<bitset>
int main() {
    std::bitset<64> b;
}