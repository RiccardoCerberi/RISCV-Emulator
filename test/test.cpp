#include <cstdint>
#include<iostream>
#include<cstdio>
#include<array>
#include<bitset>


int main() {
    uint8_t val = 128;
    std::bitset<64> val_ext{val};

    std::cout << val_ext << "\n";
    printf("%p", (uint64_t) val);
}