#ifndef TAKE_BINARY_FILE_HPP
#define TAKE_BINARY_FILE_HPP

#include <fstream>
#include <iostream>
#include <iterator>

#include "DRAM.hpp"

/*
 *   It reads the binary file that contains the instructions for the riscv
 * emulator
 */

int openFile(std::string const&);

#endif
