#ifndef MAPPER_NROM_H
#define MAPPER_NROM_H


#include <cstdint>
#include <vector>

using CartridgeContents = std::vector<uint8_t>;


class MapperNROM {
public:
    int  prg_rom_banks_count {0};
    int  chr_rom_banks_count {0};
    bool trainer_presence    {false};

    CartridgeContents prg_rom_memory {};
    CartridgeContents chr_rom_memory {};


    uint8_t map_cpu_read();
    void    map_cpu_write();
};


#endif
