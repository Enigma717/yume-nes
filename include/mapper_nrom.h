#pragma once

#include <cstdint>
#include <vector>


namespace MapperConsts
{
    constexpr size_t prg_ram_bank_size {8192};
    constexpr size_t prg_rom_bank_size {16384};
    constexpr size_t chr_rom_bank_size {8192};
}

using CartridgeContents = std::vector<uint8_t>;


class MapperNROM {
public:
    int prg_ram_banks_count {0};
    int prg_rom_banks_count {0};
    int chr_rom_banks_count {0};

    bool prg_ram_presence {true};
    bool trainer_presence {false};

    CartridgeContents prg_ram_memory {
        CartridgeContents(MapperConsts::prg_ram_bank_size, 0x00)};
    CartridgeContents prg_rom_memory {
        CartridgeContents(MapperConsts::prg_rom_bank_size, 0x00)};
    CartridgeContents chr_rom_memory {
        CartridgeContents(MapperConsts::chr_rom_bank_size, 0x00)};


    void    map_prg_ram_write(uint16_t address, uint8_t value);
    uint8_t map_prg_ram_read(uint16_t address) const;

    void    map_prg_rom_write(uint16_t address, uint8_t value);
    uint8_t map_prg_rom_read(uint16_t address) const;

    void    map_chr_rom_write(uint16_t address, uint8_t value);
    uint8_t map_chr_rom_read(uint16_t address) const;
};
