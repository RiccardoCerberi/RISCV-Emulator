#pragma once

#include<cstdint>
#include<cassert>


struct BitsManipulation {
    static uint32_t takeBits(uint32_t, uint8_t const, uint8_t const);
    static uint64_t extendSign(uint32_t const, uint8_t const);
};