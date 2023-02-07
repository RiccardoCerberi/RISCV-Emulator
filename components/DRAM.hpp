/*
    DRAM is implemented as an array of SIZE_DRAM bits. 
    DRAM will contain data releated to the processes.
    The model adopted is little-endian (is the one of x86 systems), that means the most significant byte
    is stored at the highest address and the least significant byte at the lowest. 
    Therefore, if we had to store 0x01[...]04 in memory, we would have this memory model:
        0x0[...]0 | 0x04 |
            ...   | ...  |
        0x0[...]1 | 0x01 |
The opposite model is big-endian. 
*/
