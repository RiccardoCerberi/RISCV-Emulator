## Python files ##

### Get Tests ###
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

### Execute all ###
Every binary file is divided into blocks, each one is a test that ends with a conditional jump. 
If the condition is true the next instruction is marked as fail, so something went wrong, otherwise the next block is executed.
The last test has two conditional jumps to the fail or pass instruction.
Check_correctness.py runs the executable, accept mode (i.e Release or Debug), and checks the presence of \<pass\>  instruction address and the absence of \<fail\>.
For each test the script also measures the amount of time spend to execute the instructions and, if all tests are passed, shows all measurements in a graph.

The directory also contains a makefile to turn assembly file into binary file, to make your own test.
