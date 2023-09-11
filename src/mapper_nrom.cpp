#include "../include/mapper_nrom.h"


namespace
{
    constexpr uint16_t cartridge_space_offset {0x8000};
}


uint8_t MapperNROM::map_prg_rom_read(uint16_t address) const
{
    uint16_t mapped_address = address - cartridge_space_offset;

    if (prg_rom_banks_count == 1)
        mapped_address = mapped_address % MapperConsts::prg_rom_bank_size;

    return prg_rom_memory[mapped_address];
}
