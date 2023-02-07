#include "take-binary-file.hpp"

int openFile(std::string const& file_name) {
    std::ifstream input_file(file_name, std::ios::binary);

    if (input_file.open() == false) {
        std::cerr << "Error in opening file: " << file_name << std::endl;
        // TODO:  change it to return an exception
        return -1
    }

    std::array<uint64_t, DRAM_SIZE> buffer;
    size_t i = 0;
    while (
        input_file.read(reinterpret_cast<char*>(&buffer[i]), sizeof(uint8_t))) {
        ++i;
    }
    setInstructionsMemory(buffer);
}
