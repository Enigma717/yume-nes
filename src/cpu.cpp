#include "../include/cpu.h"


void CPU::connect_with_ram(Memory& ram)
{
    CPU::ram_ptr = &ram;
}