#ifndef CPU_H
#define CPU_H


#include <memory>

#include "./memory.h"


class Memory;


class CPU {
public:
    void connect_with_ram(Memory& ram);
    Memory* ram_ptr;
private:
};


#endif