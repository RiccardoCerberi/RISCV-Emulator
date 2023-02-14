#pragma once

#include <cstdint>
#include <cstdlib>
#include<array>

constexpr uint64_t kdram_base = 0x80000000;
constexpr uint32_t kdram_size = 128 * 1024 * 1024;

constexpr uint8_t ktot_registers = 32;
constexpr uint16_t kcsrs_size = 4096;

enum register_index : size_t { kzero_register = 0, kra = 1, ksp = 2 };

using reg_type = std::array<uint64_t, ktot_registers>;
using csrs_t = std::array<uint64_t, kcsrs_size>;

enum data_size : size_t {
    kbyte = sizeof(uint8_t),
    khalf_word = sizeof(uint16_t),
    kword = sizeof(uint32_t),
    kdouble_word = sizeof(uint64_t)
};
