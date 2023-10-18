# Presentation 

This is an implementation of RISC-V emulator written in C++.
It's a single cycle processor, thus every instruction is executed sequentially.
The emulator reads binary files that contain RISC-V instructions only.

The current version supports user integer instructions on 32 bits registers (rv32ui), that is, the set of instructions for common operations like add, load and store.

## Requirements

- C++ compiler;
- CMake to configure the build-system that would eventually make the executable.

<!-- 
### Make your own bin files ###

The directory test/bin_files contains a set of binary files downloaded from https://github.com/riscv/riscv-tests, the official repository.
It's possible to add new files made by yourself.
All you need is to install the gcc version for RISC-V processors; 
instructions in the repository https://github.com/RISC-V/RISC-V-gnu-toolchain.
To work properly remember to edit the $RISCV environment variable with value /opt/riscv and make it  _writable_ (chmod ugo+w).
-->

## Build the project

Make bin and build directories, both with Debug and Release mode, by running

    mkdir build  bin
    cd bin
    mkdir Debug Release
    cd ../build
    mkdir Debug Release

Optionally, you can specify which generator cmake will use by the flag -G followed by the generator name, by default in Linux is Make and in Windows Visual Studio.  

Choose a mode (either Debug or Release), let's suppose Debug, and based on the generator choosen run one of the following commands:

### Make-like generators ###

The mode can be specified in the generate step:

    cmake ../.. -DCMAKE_BUILD_TYPE=Debug

### IDE generators ###

First generate the project:

    cmake -G "Unix Makefile" ../.. 

Then, in the build step, write

    cmake --build . --config Debug
    
For Release mode substitute Debug with Release.

VSCode offers a CMake extension  (https://github.com/microsoft/vscode-cmake-tools.git) that can be configured by editing settins.json file in .vscode directory.
To change default build directory as well as the generator, write

    "cmake.generator" : "Unix Makefile"
    "cmake.buildDirectory" : "${workspaceRoot}/build/${buildType}",

Complete overview of all available options at https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-settings.md#cmake-settings.

## Run the emulator ##

The emulator requires a binary file containing the instructions to execute.
By default, they're located at test/bin_files/ folder.
To launch the emulator

    riscv-emulator ../../test/bin_files/<name.bin>

**NOTE** 
Every test contains an invalid instruction to terminate the emulator, otherwise it will never end.
The illegal instruction runs an exception: attempt to write read only location.
To know whether the program terminates for this reason or not, use test/check_correctness.py.
For more info see test/README.md

