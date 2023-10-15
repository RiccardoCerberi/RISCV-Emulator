#pragma once

#include <bitset>

#if __GNUC__ >= 13
#include <format>
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

using Mem_t = std::vector<std::byte>;

RegisterSize_t readFromMemory(Mem_t &, RegisterSize_t, Address_t, DataSize_t);
void writeToMemory(Mem_t &, Address_t base, Address_t, RegisterSize_t,
                   DataSize_t);
std::ostream &operator<<(std::ostream &os, std::byte b);

class DRAM {
public:
    DRAM() : m_dram{kdram_size, std::byte{0}} {}
    void write(Address_t, RegisterSize_t, DataSize_t);
    RegisterSize_t read(Address_t, DataSize_t);

private:
    Mem_t m_dram;
};

class SystemInterface {
public:
    SystemInterface(std::string const &);
    RegisterSize_t readData(Address_t, DataSize_t);
    void writeData(Address_t, RegisterSize_t, DataSize_t);
    RegisterSize_t getLastInstruction() { return m_last_instruction; }
#ifdef DEB_BIN_INS
private:
    void printCode();
#endif
private:
    void loadCode(std::string const &);
    bool checkLimit(Address_t);
    bool validWrite(Address_t);

private:
    DRAM m_memory;
    Address_t m_last_instruction;
};
