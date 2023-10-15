#pragma once

#include <cassert>
#include <fstream>
#include <iostream>

#include "cpu.hpp"

class Emulator {
public:
    Emulator(std::string const&);
    void runEmulator();

private:
    CPU m_cpu;
};
