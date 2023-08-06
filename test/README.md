## Python files 

### Get Tests
Run the following commands to clone and build riscv-tests:
    git clone https://github.com/riscv/riscv-tests
    cd riscv-tests
    git submodule update --init --recursive
    autoconf
    ./configure
    make
    make install
    cd ..

Run gen_test.py:
    ./gen_test.py
The command will generate all binary files to test the emulator.

### Execute all
Check_correctness.py runs the executable and checks that  \<pass\>  instruction address is present and \<fail\> is not.

The makefile contains command to get the binary from test.s file, just to test basic operations.
