#include "../include/memory.h"


void Memory::mem_clear()
{
    std::fill(memory.begin(), memory.end(), 0x00);
}

void Memory::mem_write(uint16_t address, uint8_t data)
{
    if (address >= 0x0000 && address <= memory_size)
        memory[address] = data;
}

uint8_t Memory::mem_read(uint16_t address) const
{
    if (address >= 0x0000 && address <= memory_size)
        return memory[address];

    return 0x00;
}

int Memory::mem_read_debug(uint16_t address) const
{
    if (address >= 0x0000 && address <= memory_size)
        return static_cast<int>(memory[address]);

    return 0;
}

MemoryVec Memory::get_memory_copy() const
{
    return memory;
}
