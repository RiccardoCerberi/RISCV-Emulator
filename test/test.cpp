#include <cstdint>
#include<iostream>
#include<cstdio>

#define BASE 0x80000000
#define SIZE 3

int main() {
    uint64_t arr[SIZE]={1,5,7};
    uint64_t base_ptr = (uint64_t) &arr[0];
    uint64_t p0 = BASE, p1 = BASE + 1;


    // without sizeof() it will cause an error because it didn't switch to the next
    // element causing a wrong read
    std::cout << *((uint64_t*) (base_ptr + (p1-p0)*sizeof(uint64_t))) << "\n";

}