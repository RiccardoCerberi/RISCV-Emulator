#include "bits-manipulation.hpp"

// bits are indexed from zero

constexpr uint8_t BitsManipulation::lastIndx()   {
    return sizeof(RegisterSize_t) * 8 -1;
}

RegisterSize_t BitsManipulation::takeBits(InstructionSize_t const is, uint8_t const beg, uint8_t const last) {
    assert(last >= beg);
    return (is >> beg) & (static_cast<RegisterSize_t>(-1) >> (lastIndx()-last+beg));
}

RegisterSize_t BitsManipulation::extendSign(RegisterSize_t const imm, uint8_t const sign_pos) {
    assert(sign_pos <= lastIndx());
    if ((imm >> sign_pos == 1) && (sign_pos < lastIndx())) 
        return - ((1 << (sign_pos+1)) - imm);
    return imm;
}
