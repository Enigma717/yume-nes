#include "../include/mapper_nrom.h"


namespace
{
    constexpr uint16_t prg_ram_space_offset {0x6000};
    constexpr uint16_t prg_rom_space_offset {0x8000};
}


void MapperNROM::map_prg_ram_write(uint16_t address, uint8_t data)
{
    if (!prg_ram_presence)
        return;

    prg_ram_memory.at(address - prg_ram_space_offset) = data;
}

uint8_t MapperNROM::map_prg_ram_read(uint16_t address) const
{
    if (!prg_ram_presence)
        return 0x00;

    return prg_ram_memory.at(address - prg_ram_space_offset);
}

uint8_t MapperNROM::map_prg_rom_read(uint16_t address) const
{
    uint16_t mapped_address = address - prg_rom_space_offset;

    if (prg_rom_banks_count == 1)
        mapped_address = mapped_address % MapperConsts::prg_rom_bank_size;

    return prg_rom_memory.at(mapped_address);
}

uint8_t MapperNROM::map_chr_rom_read(uint16_t address) const
{
    return chr_rom_memory[address];
}
