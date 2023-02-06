/*
    DRAM is implemented as an array of SIZE_DRAM bits. 
    Every virtual address is translated into the physical by adding the BASE_DRAM address value.
    If the result is not inside the range [DRAM_BASE, DRAM_BASE+SIZE_DRAM) than an exception will occur
    Moreover, the DRAM is fragmented into data segment, code segment, input/output (mapped I/O).
    This is basic design that may lead to memory fragmentation, hence it will require a change later. 
    For this reason it would be interest to make the TLB in such a way that 
    represents the real world by setting a table whose entries are pointers and each one has
    a set of flags that identify its properties like I/O or read and write.
    See the rust emulator for more details
    are just pointers
    NOTE: everything is by virtual point of view: the operating system will allocate all this data
    in "real" RAM for us.
*/
