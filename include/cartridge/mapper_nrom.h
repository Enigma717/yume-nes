#pragma once

#include <cstdint>
#include <vector>


using CartridgeContents = std::vector<std::uint8_t>;

namespace MapperConsts
{
    constexpr std::size_t chr_rom_bank_size {8192uz};
    constexpr std::size_t prg_ram_bank_size {8192uz};
    constexpr std::size_t prg_rom_bank_size {16384uz};
}


class MapperNROM {
public:
    void map_prg_ram_write(std::uint16_t address, std::uint8_t data);
    std::uint8_t map_prg_ram_read(std::uint16_t address) const;
    std::uint8_t map_prg_rom_read(std::uint16_t address) const;
    std::uint8_t map_chr_rom_read(std::uint16_t address) const;

private:
    int prg_ram_banks_count {0};
    int prg_rom_banks_count {0};
    int chr_rom_banks_count {0};

    bool prg_ram_presence {true};
    bool trainer_presence {false};

    CartridgeContents prg_ram_memory {
        CartridgeContents(MapperConsts::prg_ram_bank_size, 0x00u)};
    CartridgeContents prg_rom_memory {
        CartridgeContents(MapperConsts::prg_rom_bank_size, 0x00u)};
    CartridgeContents chr_rom_memory {
        CartridgeContents(MapperConsts::chr_rom_bank_size, 0x00u)};

    friend class Cartridge;
};
