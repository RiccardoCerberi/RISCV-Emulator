#include "../include/bits-manipulation.hpp"

// last is included
uint64_t BitsManipulation::takeBits(uint64_t const is, uint8_t const beg, uint8_t const last) {
    assert(last >= beg);
    return (is >> beg) & (static_cast<uint64_t>(-1) >> (63-last+beg));
}

// It extends a 64 bit sequence in sign based on the bit in the sign_pos.
// NOTE: sign_pos refers to bit position counting from zero
uint64_t BitsManipulation::extendSign(uint64_t const imm, uint8_t const sign_pos) {
    if (imm >> sign_pos == 1) 
        return -((1 << (sign_pos+1)) -imm);
    return imm;
}

uint64_t BitsManipulation::takeVacantBit(uint64_t const n) {
    return n & ((uint64_t) 1 << 63);
}
