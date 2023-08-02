#ifndef CPU_H
#define CPU_H


#include <memory>

#include "./memory.h"


class Memory;


class CPU {
public:
    /////  Memory connection  /////
    void    connect_with_ram(Memory& ram);
    Memory* get_ram_address();


    /////  Memory I/O  /////
    void    cpu_mem_write(uint16_t address, uint8_t data);
    uint8_t cpu_mem_read(uint16_t address);
    int     cpu_mem_read_debug(uint16_t address);


    /////  Status manipulation  /////  (looks retarded, may change it later) 
    void    set_carry_flag(bool value);
    void    set_zero_flag(bool value);
    void    set_interrupt_flag(bool value);
    void    set_decimal_flag(bool value);
    void    set_brk_flag(bool value);
    void    set_unused_flag(bool value);
    void    set_overflow_flag(bool value);
    void    set_negative_flag(bool value);
    void    set_status_word(uint8_t mask);
    uint8_t read_status_word();

    /////  Reset system  /////
    void reset(); 

private:
    /////  Console internal memory  /////
    Memory* ram_ptr {nullptr};


    /////  Flags  /////
    union Status {
        struct {
            uint8_t carry     : 1;
            uint8_t zero      : 1;
            uint8_t interrupt : 1;
            uint8_t decimal   : 1;
            uint8_t brk       : 1;
            uint8_t unused    : 1;
            uint8_t overflow  : 1;
            uint8_t negative  : 1;
        } flag;

        uint8_t word;
    };


    /////  Registers  /////
    uint8_t  acc     {0x00};
    uint8_t  x_reg   {0x00};
    uint8_t  y_reg   {0x00};
    uint8_t  stk_ptr {0x00};
    uint16_t pc      {0x0000};
    Status   status  {0x00};
};


#endif