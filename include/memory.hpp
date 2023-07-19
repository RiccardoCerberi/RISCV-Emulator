#pragma once

#include <bitset>

#if __GNUC__ >= 13
#include<format>
#endif
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

#include "bits-manipulation.hpp"
#include "constants.hpp"

/*
write means a direct access to memory location where load means a sequential
access. RAM supports the first operation, ROM only the second one.
*/
using Mem_t = std::vector<std::byte>;

// maybe inline, test later
uint64_t readFromMemory(Mem_t &, uint64_t, Address_t, DataSize_t);
void writeToMemory(Mem_t &, uint64_t base, Address_t, uint64_t, DataSize_t);
std::ostream& operator<<(std::ostream& os, std::byte b);

class DRAM {
public:
    DRAM() : m_dram{kdram_size, std::byte{0}} {}
    void write(Address_t, uint64_t, DataSize_t);
    uint64_t read(Address_t, DataSize_t);
private:
    void loader(std::string const&);
private:
    Mem_t m_dram;
};

class SystemInterface {
public:
    SystemInterface(std::string const &);
    uint64_t loadData(Address_t, DataSize_t);
    void storeData(Address_t, uint64_t, DataSize_t);
    uint32_t getLastInstruction() { return m_last_instruction; }
#ifdef DEB_BIN_INS
private:
    void printCode();
#endif
private:
    void loadCode(std::string const&);
    bool checkLimit(Address_t);
private:
    DRAM m_memory;
    uint32_t m_last_instruction;
};
