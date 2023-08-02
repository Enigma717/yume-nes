#ifndef MEMORY_H
#define MEMORY_H


#include <vector>
#include <cstdint>


using Memory_vec = std::vector<uint8_t>;

inline constexpr uint16_t mem_size = 0x0800;


class Memory {
public:

    void    mem_clear();
    void    mem_write(uint16_t address, uint8_t data);
    uint8_t mem_read(uint16_t address);
    int     mem_read_debug(uint16_t address);

    Memory_vec get_memory_copy();
private:
    Memory_vec memory = std::vector<uint8_t>(mem_size, 0x00);
};


#endif