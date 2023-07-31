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
    ////////// flags //////////
    union Status {
        struct {
            uint8_t carry     : 1;
            uint8_t zero      : 1;
            uint8_t interrupt : 1;
            uint8_t decimal   : 1;
            uint8_t unused    : 2;
            uint8_t overflow  : 1;
            uint8_t negative  : 1;
        } flag;

        uint8_t word;
    };
    ///////////////////////////

    //////// registers ////////
    uint8_t  acc {0x00};
    uint8_t  x_reg {0x00};
    uint8_t  y_reg {0x00};
    uint8_t  stk_ptr {0x00};
    uint16_t pc {0x0000};
    Status   status {0x00};
    ///////////////////////////

    Memory* ram_ptr {nullptr};
};


#endif