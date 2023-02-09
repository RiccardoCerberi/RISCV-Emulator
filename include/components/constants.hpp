#ifndef CONSTANT_HPP
#define CONSTANT_HPP


#include <cstdint>
#include <cstdlib>

constexpr uint64_t kdram_base = 0x80000000;
constexpr uint32_t kdram_size = 128 * 1024 * 1024;

constexpr uint8_t ktot_registers = 32;

enum register_index {
    kzero_register =  0,
    ksp = 2
};

enum data_size : size_t
{
    kbyte = sizeof(uint8_t),
    khalf_word = sizeof(uint16_t),
    kword = sizeof(uint8_t),
    kdouble_word = sizeof(uint8_t)
};

#endif