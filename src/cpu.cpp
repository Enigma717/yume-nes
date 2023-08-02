#include "../include/cpu.h"


/////////////////////////
//  Memory connection  // 
/////////////////////////

void CPU::connect_with_ram(Memory& ram)
{
    CPU::ram_ptr = &ram;
}

Memory* CPU::get_ram_address()
{
    return ram_ptr;
}


//////////////////
//  Memory I/O  // 
//////////////////

void CPU::cpu_mem_write(uint16_t address, uint8_t data)
{
    ram_ptr->mem_write(address, data);
}

uint8_t CPU::cpu_mem_read(uint16_t address)
{
    return ram_ptr->mem_read(address);
}

int CPU::cpu_mem_read_debug(uint16_t address)
{
    return ram_ptr->mem_read_debug(address);
}


///////////////////////////
//  Status manipulation  // 
///////////////////////////

void CPU::set_carry_flag(bool value)
{
    status.flag.carry = value;
}

void CPU::set_zero_flag(bool value)
{
    status.flag.zero = value;
}

void CPU::set_interrupt_flag(bool value)
{
    status.flag.interrupt = value;
}

void CPU::set_decimal_flag(bool value)
{
    status.flag.decimal = value;
}

void CPU::set_brk_flag(bool value)
{
    status.flag.brk = value;
}

void CPU::set_unused_flag(bool value)
{
    status.flag.unused = value;
}

void CPU::set_overflow_flag(bool value)
{
    status.flag.overflow = value;
}

void CPU::set_negative_flag(bool value)
{
    status.flag.negative = value;
}

void CPU::set_status_word(uint8_t mask)
{
    status.word = mask;
}

uint8_t CPU::read_status_word()
{
    return status.word;
}


//////////////////////////
//  Hard reset console  // 
//////////////////////////

void CPU::hard_reset()
{
    acc = 0;
    x_reg = 0;
    y_reg = 0;
    stk_ptr = 0xFD;
    status.word = 0x34;
    ram_ptr->mem_clear();
} 
