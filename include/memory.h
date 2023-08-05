#ifndef MEMORY_H
#define MEMORY_H


#include <vector>
#include <cstdint>


using MemoryVec = std::vector<uint8_t>;

inline constexpr uint16_t mem_size = 0x0800;


class Memory {
public:
    void    mem_clear();
    void    mem_write(uint16_t address, uint8_t data);
    uint8_t mem_read(uint16_t address) const;
    int     mem_read_debug(uint16_t address) const;

    MemoryVec get_memory_copy() const;
private:
    MemoryVec memory = std::vector<uint8_t>(mem_size, 0x00);
};


#endif