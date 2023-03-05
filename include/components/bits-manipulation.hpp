#pragma once

#include<cstdint>
#include<cassert>
#include<bitset>
#include<iostream>

/*
 * The BitsManipulation class has two functions: takeBits, which takes from 64 bits the ones in the range [begin,last],
 * and extendSign, which extends 64 bits number based on the bit in the second parameter position.
 */

struct BitsManipulation {
    static uint64_t takeBits(uint64_t , uint8_t , uint8_t );
    static uint64_t extendSign(uint64_t , uint8_t );
};