#include <iostream>
#include <cstring>

#include "emulator/emulator.hpp"

#define MAX_FILE_LENGTH 100

int main(int argc, char **argv)
{
    int index_file = 1;

    if (argc < 2 || (std::strlen(argv[index_file]) > MAX_FILE_LENGTH))
    {
        std::cerr << "Error: \n";
        return -1;
    }
    std::cout << "Everything fine. File: " << argv[index_file] << std::endl;

    std::string file_name(argv[index_file]);

    Emulator riscv_emulator(file_name);
    return 0;
}