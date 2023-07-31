#ifndef MEMORY_H
#define MEMORY_H


#include <vector>
#include <cstdint>


inline constexpr uint16_t mem_size = 0xFFFF;


class Memory {
public:
    void    mem_write(uint16_t address, uint8_t data);
    uint8_t mem_read(uint16_t address);
    int     mem_read_debug(uint16_t address);
private:
    std::vector<uint8_t> memory = std::vector<uint8_t>(mem_size, 0x00);
};


#endif