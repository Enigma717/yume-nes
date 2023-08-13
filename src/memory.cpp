#include "../include/memory.h"
#include <algorithm>


void Memory::mem_clear()
{
    std::fill(memory.begin(), memory.end(), 0x00);
}

void Memory::mem_load_program(MemoryVec program, uint16_t offset)
{
    std::copy(program.begin(), program.end(), memory.begin() + offset);
}


void Memory::mem_write(uint16_t address, uint8_t value)
{
    memory[address] = value;
}

uint8_t Memory::mem_read(uint16_t address) const
{
    return memory[address];
}

int Memory::mem_read_debug(uint16_t address) const
{
    return static_cast<int>(memory[address]);
}

MemoryVec Memory::get_memory_copy() const
{
    return memory;
}
