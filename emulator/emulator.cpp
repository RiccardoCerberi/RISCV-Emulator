#include "emulator.hpp"

Emulator::Emulator(std::string const& file_name) {
    std::ifstream input_file(file_name, std::ios::binary);

    assert(("Error in opening the file", input_file.is_open() == true));

    uint64_t address_tostore_current_instruction = DRAM_BASE;
    size_t word = sizeof(uint32_t);
    uint64_t current_instruction;
    while (
        input_file.read(reinterpret_cast<char*>(&current_instruction), word)) {
        m_dram.store(address_tostore_current_instruction, current_instruction, word);
    }
}
