#ifndef TAKE_BINARY_FILE_HPP
#define TAKE_BINARY_FILE_HPP

#include <fstream>
#include <iostream>
#include<cassert>

#include "../components/DRAM.hpp"
#include "../components/cpu.hpp"

/*
 *   It reads the binary file that contains the instructions for the riscv
 * emulator
 */

class Emulator{
public:
    Emulator(std::string const&);
    void runEmulator();
private:
    DRAM m_dram;
    CPU m_cpu;
};


#endif
