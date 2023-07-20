#pragma once

#include <cstdint>
#include <cstdlib>
#include<array>

using Address_t = uint32_t;
using InstructionSize_t = uint32_t;
using RegisterSize_t = uint32_t;
using CSRRegisterSize_t = uint32_t;

constexpr uint64_t kdram_base = 0x80000000;
constexpr uint64_t kdram_size = 1024*1024;

constexpr uint8_t ktot_registers = 32;
constexpr uint16_t kcsrs_size = 4096;

constexpr uint8_t klast_opcode_digit = 6;
constexpr uint8_t kopcode_len = 7;
using reg_type = std::array<RegisterSize_t, ktot_registers>;

enum register_index : size_t { kzero_register = 0, kra = 1, ksp = 2 };

// Data size in byte
enum DataSize_t 
{
    kbyte = 1,
    khalf_word = 2,
    kword = 4,
    kdouble_word = 8
};

