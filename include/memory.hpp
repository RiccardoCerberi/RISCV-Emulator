#pragma once

#include<cmath>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

#include "bits-manipulation.hpp"
#include "constants.hpp"

/*
 * Memory is divided in four parts: ROM from [0x10...0 to 0x10...0+kROMSIZE),
 * RAM from 0x10...0+kROMSIZE to 0x10...0+kROMSIZE + kRAMSIZE and so on for UART
 */

/*
write means a direct access to memory location where load means a sequential
access. RAM supports the first operation, ROM only the second one.
*/

using Mem_t = std::vector<std::byte>;

// maybe inline, test later
uint64_t readFromMemory(Mem_t &, uint64_t, Address_t, DataSize_t);
void writeToMemory(Mem_t &, uint64_t base, Address_t, uint64_t, DataSize_t);

class ROM {
public:
    ROM() : m_rom{krom_size, std::byte{0}} {}
    void storeBlock(Address_t, std::vector<std::byte> const &);
    uint64_t read(Address_t, DataSize_t);
private:
    Mem_t m_rom;
};

class RAM {
public:
    RAM() : m_ram{kram_size, std::byte{0}} {}
    void write(Address_t, uint64_t, DataSize_t);
    uint64_t read(Address_t, DataSize_t);

private:
    Mem_t m_ram;
};

class MemorySystem {
public:
    MemorySystem(std::string const &);
    uint64_t load(Address_t, DataSize_t);
    void store(Address_t, uint64_t, DataSize_t);
private:
    RAM m_ram;
    ROM m_rom;
};