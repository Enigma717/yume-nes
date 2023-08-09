#ifndef MEMORY_H
#define MEMORY_H


#include <cstdint>
#include <vector>


inline constexpr uint32_t memory_size = 0x10000;
inline constexpr uint16_t stack_offset = 0x0100;

using MemoryVec = std::vector<uint8_t>;


class Memory {
public:
    void    mem_clear();
    void    mem_write(uint16_t address, uint8_t data);
    uint8_t mem_read(uint16_t address) const;
    int     mem_read_debug(uint16_t address) const;


    MemoryVec get_memory_copy() const;
private:
    MemoryVec memory {std::vector<uint8_t>(memory_size, 0x00)};
};


#endif
