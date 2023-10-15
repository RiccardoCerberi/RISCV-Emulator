#pragma once

#include <bitset>
#include <cassert>
#include <cstdint>
#include <iostream>

#include "constants.hpp"

struct BitsManipulation {
    constexpr static uint8_t lastIndxRegData();
    static RegisterSize_t takeBits(
        InstructionSize_t, uint8_t beg,
        uint8_t last);  // Take bits from beg to last INCLUDED
    static RegisterSize_t extendSign(RegisterSize_t, uint8_t);
};
