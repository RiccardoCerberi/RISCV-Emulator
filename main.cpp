#include <iostream>
#include <cstring>
#include<vector>

#include "include/emulator.hpp"

#define MAX_FILE_LENGTH 100

int main(int argc, char **argv) {
    int index_file = 1;

    if (argc < 2) {
        std::cerr << "Error: no file provided\n";
        return -1;
    }

    if (std::strlen(argv[index_file]) > MAX_FILE_LENGTH) {
        std::cerr << "Error: file length exceeds the limit: "<< MAX_FILE_LENGTH << std::endl;
        return -1;
    }

    std::string bin_file{argv[index_file]};
    std::cout << "File provided: " << bin_file << std::endl;

    Emulator riscv_emulator(bin_file);

    riscv_emulator.runEmulator();

    return 0;
}

