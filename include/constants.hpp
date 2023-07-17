#pragma once

#include <cstdint>
#include <cstdlib>
#include<array>

using RegisterSize_t = uint64_t;
using Address_t = uint64_t;
using Instruction_t = uint32_t;

// krom base set at 0x80...0 
// to work with test
constexpr uint64_t krom_base = 0x80000000;
constexpr uint64_t krom_size = 1024;
constexpr uint64_t krom_end = krom_base + krom_size;

// in test there's no distinction between rom and ram therefore 
//  beginning of ram (equivalent to end of rom)
// should be set dynamically based on last instruction address
constexpr uint64_t kram_base = krom_end;
constexpr uint64_t kram_size = 1024*1024;
constexpr uint64_t kram_end = kram_base + kram_size;

constexpr uint8_t ktot_registers = 32;
constexpr uint16_t kcsrs_size = 4096;

constexpr uint8_t klast_opcode_digit = 6;

enum register_index : size_t { kzero_register = 0, kra = 1, ksp = 2 };

using reg_type = std::array<RegisterSize_t, ktot_registers>;
using csrs_t = std::array<uint64_t, kcsrs_size>;

// Data size in byte
enum DataSize_t 
{
    kbyte = 1,
    khalf_word = 2,
    kword = 4,
    kdouble_word = 8
};
