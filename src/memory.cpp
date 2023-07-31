#include "../include/memory.h"



void Memory::mem_write(uint16_t address, uint8_t data)
{
    if (address >= 0x0000 && address <= mem_size)
        memory[address] = data;
}

uint8_t Memory::mem_read(uint16_t address)
{
    if (address >= 0x0000 && address <= mem_size)
        return memory[address];

    return 0x00;
}

int Memory::mem_read_debug(uint16_t address)
{
    if (address >= 0x0000 && address <= mem_size)
        return static_cast<int>(memory[address]);

    return 0;
}
