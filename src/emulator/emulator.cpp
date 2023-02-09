#include "../../include/emulator/emulator.hpp"

/*
    I could have written the DRAM constructor to set the instructions in memory, but I prefer to use this method
    because I'll be able to change it to interact with the operative system
*/

Emulator::Emulator(std::string const &file_name)
{
    std::ifstream input_file(file_name, std::ios::binary);

    assert(("Error in opening the file", input_file.is_open() == true));

    uint64_t address_tostore_instruction = kdram_base;
    uint64_t current_instruction;

    while (
        input_file.read(reinterpret_cast<char *>(&current_instruction), data_size::kword))
    {
        m_dram.store(address_tostore_instruction, current_instruction, data_size::kword);
        address_tostore_instruction += data_size::kword;
    }
#ifdef DEBUG
    m_dram.setLastInstructionAddress(address_tostore_instruction - data_size::kword);
#endif
}
