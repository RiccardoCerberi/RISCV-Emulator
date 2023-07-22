#include "../include/emulator.hpp"

Emulator::Emulator(std::string const& file_name) : m_cpu(file_name) {}

void Emulator::runEmulator() {
    try {
        m_cpu.steps();
    } catch (const char* exc_text) {
        std::cout << exc_text << std::endl;
    }
}
