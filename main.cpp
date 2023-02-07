#include<iostream>
#include<cstring>


int main(int argc, char** argv) {
    int index_file = 1;


    if (argc < 2 || (std::strlen(argv[index_file]) > 20)) {
        std::cerr << "Error: \n";
        return -1;
    }

    std::cout << "Everything fine. File: " << argv[index_file] << std::endl;

}