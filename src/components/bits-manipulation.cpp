#include "../../include/components/bits-manipulation.hpp"

// remember to remove DEBUG flag
#define DEBUG
// last is included
uint64_t BitsManipulation::takeBits(uint64_t const is, uint8_t const beg, uint8_t const last) {
    assert(last > beg);
    return (is >> beg) & (static_cast<uint64_t>(-1) >> (sizeof(is) * 8 - 1 + beg - last));
}

// It extends a 32 bit sequence in sign based on the bit in the sign_pos.
// Let's suppose the two parameters are 00101 and 2.
// The first thing to do is the xor with 00100 because ^(0,x) = x and ^(1, 1) = 0 and ^(1,0) = 1; in this example: ^= 00001
// Then, by summing 11100 (-1 << sign_pos), I'll get 11101 as expected.
uint64_t BitsManipulation::extendSign(uint64_t const imm, uint8_t const sign_pos) {
    return ((imm ^ (1 << sign_pos)) +(static_cast<uint64_t>(-1) << sign_pos));
}