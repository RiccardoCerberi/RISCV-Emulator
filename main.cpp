#include <cstring>
#include <iostream>

#include "include/emulator.hpp"

constexpr size_t max_len 100

int main(int argc, char **argv) {
    int index_file = 1;

    if (argc < 2) {
        std::cerr << "Error: no file provided\n";
        return -1;
    }

    if (std::strlen(argv[index_file]) > max_len) {
        std::cerr << "Error: file length exceeds the limit: " << max_len
                  << std::endl;
        return -1;
    }

    std::string bin_file{argv[index_file]};
    std::cout << "File provided: " << bin_file << std::endl;

    Emulator riscv_emulator(bin_file);

    riscv_emulator.runEmulator();

    return 0;
}
