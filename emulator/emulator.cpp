#include "emulator.hpp"

/*
    I could have written the DRAM constructor to set the instructions in memory, but I prefer to use this method
    because I'll be able to change it to interact with the operative system
*/

Emulator::Emulator(std::string const &file_name)
{
    std::ifstream input_file(file_name, std::ios::binary);

    assert(("Error in opening the file", input_file.is_open() == true));

    uint64_t address_tostore_instruction = DRAM_BASE;
    size_t word = sizeof(uint32_t);
    uint64_t current_instruction;
    while (
        input_file.read(reinterpret_cast<char *>(&current_instruction), word))
    {
        m_dram.store(address_tostore_instruction, current_instruction, word);
        address_tostore_instruction += word;
    }
#ifdef DEBUG
    m_dram.setLastInstructionAddress(address_tostore_instruction - word);
#endif
}
