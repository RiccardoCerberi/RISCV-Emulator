#ifndef TLB_H
#define TLB_H
/*
 * TODO: see how riscv handles page-walking.
 * We'll use the Sv32 model, which involves two level page walking.
 * Therefore the PPN (physical page number) is divided in two chuncks, each one of 64 - log(MEMORY_SIZE/PAGE_SIZE) bits size long, which represents the offest in the page table of the next level, whose  address is stored inside 
 * tha page table entry. 
 * The address of the first page table is stored in the satp register that must be set every time a context switch occurs.
*

class TLB {
    public:
    //static 
};


#endif