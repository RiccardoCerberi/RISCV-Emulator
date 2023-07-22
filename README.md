# Presentation 
This is an implementation in C++ of riscv emulator.
It's a single cycle, thus every instruction is executed sequentially.

## Requirements: 
    - Cmake to configure the buildsystem which makes the executable file;
    - Riscv gnu compiler:  go to https://github.com/riscv/riscv-gnu-toolchain and install all required packages. 
    Rememebr to edit $RISCV environment variable with value /opt/riscv and make riscv directory writable (chmod ugo+w).
    Then run  

    ```
    make && make linux 
    ```

    - A serie of test for the riscv instructions: https://github.com/riscv-software-src/riscv-tests

## Make the executable
Make bin and build directory, both with Debug and Relase mode, by running
    '''
    mkdir build  bin
    cd bin
    mkdir Debug Release
    cd ../build
    mkdir Debug Release
    '''
Then choose a mode (either Debug or Release), let's suppose Debug,  and from there run
    '''
    cmake ../..
    cmake --build -DCMAKE_BUILD_TYPE=Debug
    '''
This will generate the debug version of the executable in bin/Debug folder.
VScode offers a Cmake extension which automatically generates a build folder for the Debug mode.
To have the same result as the previous commands edit cmake.buildDirectory variable in setting.json file: cmake.buildDirectory = "build/Debug".
Complete overview of all available options at https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-settings.md#cmake-settings.

### Debug ###
The directory .vscode contains launch.json file to set the binary file to pass to the program, otherwise it will stop by returning an error

## Compiler flags ##
#set(ld_flags "-fsanitize=address")
#add_link_options(
#        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${ld_flags}>>"
#        )