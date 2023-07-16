#pragma once

#include <fstream>
#include <iostream>
#include<cassert>

#include "cpu.hpp"

class Emulator{
public:
    Emulator(std::string const&);
    void runEmulator();
private:
    CPU m_cpu;
};

