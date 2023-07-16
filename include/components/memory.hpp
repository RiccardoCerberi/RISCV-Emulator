#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include<bitset>
#include "constants.hpp"
#include "bits-manipulation.hpp"


/*
 * Memory is divided in four parts: ROM from [0x10...0 to 0x10...0+kROMSIZE),
 * RAM from 0x10...0+kROMSIZE to 0x10...0+kROMSIZE + kRAMSIZE and so on for UART 
*/


/*
write means a direct access to memory location where load means a sequential access.
RAM supports the first operation, ROM only the second one.
*/

class ROM {
    public:
        ROM() : m_rom{krom_size, std::byte{0}} {}
        bool storeBlock(Address_t, std::vector<std::byte> const&);
        uint64_t read(Address_t, DataSize_t); // by default it accepts the size of an instruction
    private:
        std::vector<std::byte> m_rom;
};

class RAM
{
public:
    void write(Address_t, uint64_t, DataSize_t);
    uint64_t read(Address_t, DataSize_t);
private:
    std::vector<uint8_t> m_ram;
};
