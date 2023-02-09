/*
 * In the I/O model, the peripherals are mapped to the memory, that means
 * we can access to them using load and store instructions. Therefore, our
 * model will be something like 
 *  0x40[...]0 |    Input   |
 *  0x40[...]1 |    Output  |
 *  
 *  0x80[...]0 |    DRAM    |
 *
 */
