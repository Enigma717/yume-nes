#include "../include/memory.h"

#include <algorithm>


namespace
{
    constexpr size_t   cpu_ram_bank_size {2048};
    constexpr uint16_t cpu_ram_upper_bound {0x1FFF};
}


void Memory::memory_clear()
{
    std::fill(memory.begin(), memory.end(), 0x00);
}

void Memory::memory_load_program(SystemMemory program, uint16_t offset)
{
    std::copy(program.begin(), program.end(), memory.begin() + offset);
}

void Memory::memory_write(uint16_t address, uint8_t value)
{
    if (address <= cpu_ram_upper_bound)
        memory[address % cpu_ram_bank_size] = value;
    else
        memory[address] = value;
}

uint8_t Memory::memory_read(uint16_t address) const
{
    if (address <= cpu_ram_upper_bound)
        return memory[address % cpu_ram_bank_size];

    return memory[address];
}

SystemMemory Memory::get_memory_copy() const
{
    return memory;
}
