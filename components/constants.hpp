#ifndef CONSTANT_HPP
#define CONSTANT_HPP


#include <cstdint>
#include <cstdlib>


enum class dram_costants : uint64_t {
    dram_base = 0x80000000,
    dram_size = 128 * 1024 * 1024 
};

enum class registers : size_t {
    number_of_registers = 32,
    zero_register_value =  0,
    sp = 2
};

enum class data_size : size_t
{
    byte = sizeof(uint8_t),
    half_word = sizeof(uint16_t),
    word = sizeof(uint8_t),
    double_word = sizeof(uint8_t)
};

#endif