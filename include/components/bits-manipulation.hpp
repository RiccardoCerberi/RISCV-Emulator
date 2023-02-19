#pragma once

#include<cstdint>
#include<cassert>
#include<bitset>
#include<iostream>


struct BitsManipulation {
    static uint64_t takeBits(uint64_t const, uint8_t const, uint8_t const);
    static uint64_t extendSign(uint64_t const, uint8_t const);
};