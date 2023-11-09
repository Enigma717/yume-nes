#pragma once

#include <cstdint>
#include <vector>


namespace MemoryConsts
{
    constexpr size_t memory_size {65536};
}

using SystemMemory = std::vector<uint8_t>;


class Memory {
public:
    void    memory_clear();
    void    memory_load_program(SystemMemory program, uint16_t offset);
    void    memory_write(uint16_t address, uint8_t data);
    uint8_t memory_read(uint16_t address) const;

    SystemMemory get_memory_copy() const;

private:
    SystemMemory memory {SystemMemory(MemoryConsts::memory_size, 0x00)};
};
