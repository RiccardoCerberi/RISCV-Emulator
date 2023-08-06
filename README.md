# Presentation #
This is an implementation in C++ of RISC-V emulator.
It's a single cycle, thus every instruction is executed sequentially.

## Requirements:  ##
- Cmake to configure the buildsystem which makes the executable file;
- RISC-V gnu compiler:  go to https://github.com/RISC-V/RISC-V-gnu-toolchain and install all required packages. 
Rememebr to edit $RISCV environment variable with value /opt/RISC-V and make _RISC-V directory writable_ (chmod ugo+w).
Then run make && make linux 
- A serie of test for the RISC-V instructions: see test/README.md or 
https://github.com/RISC-V-software-src/RISC-V-tests 

## Make the executable ##
Make bin and build directory, both with Debug and Relase mode, by running

    mkdir build  bin
    cd bin
    mkdir Debug Release
    cd ../build
    mkdir Debug Release

Then choose a mode (either Debug or Release), let's suppose Debug,  and from there run

    cmake ../..
    cmake --build -DCMAKE_BUILD_TYPE=Debug

This will generate the debug version of the executable in bin/Debug folder.
VScode offers a Cmake extension which automatically generates a build folder for the Debug mode.
To have the same result as the previous commands edit cmake.buildDirectory variable in setting.json file: cmake.buildDirectory = "build/Debug".
Complete overview of all available options at https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-settings.md#cmake-settings.
To run the program go to bin/\<mode\> and launch the executable

    RISC-V-emualtor ../../test/bin_files/\<name.bin\>

It's important to know that the exception in csrs' method (attempt to write read only register) is needed to terminate the execution of the program:
it's an illegal instruction that causes exit.
### Debug ###
The directory .vscode contains launch.json file to set the binary file to pass to the program, otherwise it will stop by returning an error

## Input ##
The emulator supports user-integer instructions on 32 bits registers.
To run the emulator go to the executable location (either bin/Debug or big/Release) and type:
    ./riscv-emulator <path_to_bin_file>/name_of_bin_file

Follow instructions in test/README.md to build all test binary files.
