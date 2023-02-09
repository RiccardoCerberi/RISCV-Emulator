#include <iostream>
#include <cstring>
#include<vector>

#include "include/emulator/emulator.hpp"

#define MAX_FILE_LENGTH 100

int main(int argc, char **argv)
{
    int index_file = 1;

    if (argc < 2 || (std::strlen(argv[index_file]) > MAX_FILE_LENGTH))
    {
        std::cerr << "Error: \n";
        return -1;
    }
    std::string bin_file{ argv[index_file]};
    std::cout << "Everything fine. File provided: " << bin_file << std::endl;

    Emulator riscv_emulator(bin_file);
    return 0;
}

