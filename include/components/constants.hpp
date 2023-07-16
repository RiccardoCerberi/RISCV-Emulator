#pragma once

#include <cstdint>
#include <cstdlib>
#include<array>

using RegisterSize_t = uint64_t;
using Address_t = uint64_t;

constexpr uint64_t krom_base = 0x1000000;
constexpr uint64_t krom_size = 1024;

constexpr uint64_t kram_base = krom_base + krom_size;
constexpr uint64_t kram_size = 1024*1024;

constexpr uint8_t ktot_registers = 32;
constexpr uint16_t kcsrs_size = 4096;

constexpr uint8_t klast_opcode_digit = 6;

enum register_index : size_t { kzero_register = 0, kra = 1, ksp = 2 };

using reg_type = std::array<uint64_t, ktot_registers>;
using csrs_t = std::array<uint64_t, kcsrs_size>;

enum DataSize_t 
{
    kbyte = 8,
    khalf_word = 16,
    kword = 32,
    kdouble_word = 64
};
