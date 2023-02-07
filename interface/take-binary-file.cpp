#include"take-binary-file.hpp"


int openFile(std::string const& file_name) {
    std::ifstream input_file(file_name, std::ios::binary );
    uint64_t num;

    input_file.read((char*) &num, sizeof(uint64_t));
}