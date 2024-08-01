#include "../../include/cartridge/mapper_nrom.h"

namespace
{
    constexpr std::uint16_t prg_ram_space_offset {0x6000u};
    constexpr std::uint16_t prg_rom_space_offset {0x8000u};
}

/////////
// API //
/////////

void MapperNROM::map_prg_ram_write(std::uint16_t address, std::uint8_t data)
{
    if (!prg_ram_presence)
        return;

    prg_ram_memory.at(address - prg_ram_space_offset) = data;
}

std::uint8_t MapperNROM::map_prg_ram_read(std::uint16_t address) const
{
    if (!prg_ram_presence)
        return 0x00u;

    return prg_ram_memory.at(address - prg_ram_space_offset);
}

std::uint8_t MapperNROM::map_prg_rom_read(std::uint16_t address) const
{
    auto mapped_address {static_cast<std::uint16_t>(address - prg_rom_space_offset)};

    if (prg_rom_banks_count == 1)
        mapped_address = mapped_address % MapperConsts::prg_rom_bank_size;

    return prg_rom_memory.at(mapped_address);
}

std::uint8_t MapperNROM::map_chr_rom_read(std::uint16_t address) const
{
    return chr_rom_memory[address];
}
