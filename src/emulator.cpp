#include "emulator.hpp"

Emulator::Emulator(std::string const& file_name) : m_cpu(file_name) {}

void Emulator::runEmulator() {
    m_cpu.steps();
}
