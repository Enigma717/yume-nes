#ifndef MAPPER_NROM_H
#define MAPPER_NROM_H


#include <cstdint>
#include <vector>

namespace MapperConsts
{
    constexpr size_t prg_rom_bank_size {16384};
    constexpr size_t chr_rom_bank_size {8192};
    constexpr size_t trainer_size      {512};
}

using CartridgeContents = std::vector<uint8_t>;


class MapperNROM {
public:
    int  prg_rom_banks_count {0};
    int  chr_rom_banks_count {0};
    bool trainer_presence    {false};

    CartridgeContents prg_rom_memory {
        CartridgeContents(MapperConsts::prg_rom_bank_size, 0x00)};
    CartridgeContents chr_rom_memory {
        CartridgeContents(MapperConsts::chr_rom_bank_size, 0x00)};


    uint8_t map_cpu_read();
    void    map_cpu_write();
};


#endif