#include "../include/cpu.h"


void CPU::connect_with_ram(Memory& ram)
{
    CPU::ram_ptr = &ram;
}

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

Memory* CPU::get_ram_address()
{
    return ram_ptr;
}
