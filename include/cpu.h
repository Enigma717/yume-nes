#ifndef CPU_H
#define CPU_H


#include <memory>

#include "./memory.h"


class Memory;


class CPU {
public:
    void    connect_with_ram(Memory& ram);
    void    cpu_mem_write(uint16_t address, uint8_t data);
    uint8_t cpu_mem_read(uint16_t address);
    int     cpu_mem_read_debug(uint16_t address);
    Memory* get_ram_address();
private:
    Memory* ram_ptr {nullptr};

    // registers
    uint8_t  x {0x00};
    uint8_t  y {0x00};
    uint8_t  a {0x00};
    uint8_t  stack_ptr {0x00};
    uint8_t  status {0x00};
    uint16_t pc {0x0000};
};


#endif