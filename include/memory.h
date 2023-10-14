#pragma once

#include <cstdint>
#include <vector>


namespace MemoryConsts
{
    constexpr size_t memory_size {65536};

    constexpr uint16_t stack_offset {0x0100};
    constexpr uint16_t ppu_registers_space_start {0x2000};
    constexpr uint16_t apu_and_io_space_start {0x4000};
    constexpr uint16_t prg_ram_space_start {0x6000};
    constexpr uint16_t prg_rom_space_start {0x8000};

    constexpr uint16_t nmi_vector_lsb {0xFFFA};
    constexpr uint16_t nmi_vector_msb {0xFFFB};
    constexpr uint16_t reset_vector_lsb {0xFFFC};
    constexpr uint16_t reset_vector_msb {0xFFFD};
    constexpr uint16_t irq_vector_lsb {0xFFFE};
    constexpr uint16_t irq_vector_msb {0xFFFF};
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
