#ifndef MEMORY_H
#define MEMORY_H


#include <cstdint>
#include <vector>


namespace MemoryConsts
{
    constexpr uint32_t memory_size      {0x10000};
    constexpr uint16_t stack_offset     {0x0100};
    constexpr uint16_t nmi_vector_lsb   {0xFFFA};
    constexpr uint16_t nmi_vector_msb   {0xFFFB};
    constexpr uint16_t reset_vector_lsb {0xFFFC};
    constexpr uint16_t reset_vector_msb {0xFFFD};
    constexpr uint16_t irq_vector_lsb   {0xFFFE};
    constexpr uint16_t irq_vector_msb   {0xFFFF};
}

using SystemMemory = std::vector<uint8_t>;


class Memory {
public:
    void    memory_clear();
    void    memory_load_program(SystemMemory program, uint16_t offset);
    void    memory_write(uint16_t address, uint8_t value);
    uint8_t memory_read(uint16_t address) const;

    SystemMemory get_memory_copy() const;

private:
    SystemMemory memory {SystemMemory(MemoryConsts::memory_size, 0x00)};
};


#endif
