# Presentation #
This is an implementation in C++ of RISC-V emulator.
It's a single cycle, thus every instruction is executed sequentially.
The current version supports rv32ui instructions, that is, user integer instructions on 32 bits registers.

## Requirements:  ##
- Cmake to configure the buildsystem which makes the executable file;
- RISC-V gnu compiler:  go to https://github.com/riscv-collab/riscv-gnu-toolchain and install all required packages. 
Rememeber to edit $RISCV environment variable with value /opt/riscv and make it  _writable_ (chmod ugo+w).
Then run make && make linux 
- Executables to test the emulator: https://github.com/RISC-V-software-src/RISC-V-tests 

## Make the executable ##
Make bin and build directory, both with Debug and Relase mode, by running

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

VScode offers a CMake extension  (https://github.com/microsoft/vscode-cmake-tools.git) that can be configured by editing settins.json file in .vscode directory.
To change default build directory as well as the generator, write

    "cmake.generator" : "Unix Makefile"
    "cmake.buildDirectory" : "${workspaceRoot}/build/${buildType}",

Complete overview of all available options at https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-settings.md#cmake-settings.

## Run emulator ##
The emulator requires a binary file containing the instructions to execute.
By default they're located at test/bin_files/ folder.
To launch the emulator

    riscv-emulator ../../test/bin_files/<name.bin>

**NOTE** 
Every test contains an invalid instruction that terminates the emulator (it runs an exception, attempt to write read only location).
To know whether the program terminates for this reason or not, use test/check\_correctness.py.
For more info see test/README.md

