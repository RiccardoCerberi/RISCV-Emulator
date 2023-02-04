The project aims to create a RISC-V emulator, which supports the unix operative system nv6. 

# Goal: #
Create a riscv emulator that is able to run nv6 unix system

# Requirements: #
## External tools: ##
   * Compiler to get c code that will be translated in a sequence of instructions following the riscv format that will be executed by the emulator. 
   * A serie of test for the riscv instructions
## Structure: ##
The memory is formed by SRAM, DRAM, Disk. 
SRAM and DRAM are grouped in RAM.
SRAM is the cpu cache, which is the fastest access memory, but it has a problem: the size. 
SRAM can contain megabyte of datas, therefore it's needed a bigger storage that  is provided by DRAM. 
A program runs because the cpu is executing its instruction, whose format is specifically to the process itself. 
The process uses the SRAM to store datas taken from the DRAM that will be used frequently during the execution process. 
Let's say, a program A requires an array of 8 bytes to be stored, the datas are stored in DRAM and when it access to an element the entire block will be stored in SRAM because presumably it's going to access to the other elements. 
This is the principle of locality.
Our memory model will be formed by the cpu and within the cache, ROM, DRAM and I/O because the model is a memory mapped input output.
    * Memory definition
    * RAM, ROM and I/O
    * Registers 
## Implementation: ##
# Big problems: #
    * How to read an executable file in cpp, is that a binary? 
Usefull link:
https://superuser.com/questions/707873/do-emulators-parse-binary-code-within-files
    2. How to create the memory model: RAM and disk. 
            - A natural solution consists in using the RAM and disk just provided by the laptop.
    3. Design the class.


