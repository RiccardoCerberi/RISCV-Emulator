The project aims to create a RISC-V emulator, which supports the unix operative system nv6. 

# Goal:
Create a riscv emulator that is able to run nv6 unix system

# Requirements:
## External tools:
   * Compiler to get c code that will be translated in a sequence of instructions following the riscv format that will be executed by the emulator. 
   * A serie of test for the riscv instructions
## Structure:
    * Memory definition
        * RAM, ROM and I/O
    * Registers 
## Implementation:
# Big problems: 
    * How to read an executable file in cpp, is that a binary? 
Usefull link:
https://superuser.com/questions/707873/do-emulators-parse-binary-code-within-files
    2. How to create the memory model: RAM and disk. 
            - A natural solution consists in using the RAM and disk just provided by the laptop.
    3. Design the class.


