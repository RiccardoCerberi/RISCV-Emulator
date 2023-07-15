#include "../../include/emulator/emulator.hpp"

/*
    I could have written the DRAM constructor to set the instructions in memory, but I prefer to use this method
    because I'll be able to change it to interact with the operative system
*/

Emulator::Emulator(std::string const &file_name) : m_cpu(file_name)
{}


// entry point for the program
void Emulator::runEmulator() {
    m_cpu.steps();
}
