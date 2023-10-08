#include "../include/ppu.h"

#include "../include/cartridge.h"


namespace
{
    constexpr uint16_t attribute_table_offset {0x03C0};

    constexpr uint16_t nametables_space_start {0x2000};
    constexpr uint16_t palettes_space_start {0x3F00};
}


void PPU::connect_with_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    cartridge_ptr = cartridge;
}

void PPU::memory_write(uint16_t address, uint8_t value)
{
    if (address < nametables_space_start)
        cartridge_ptr.lock()->mapper.map_chr_rom_write(address, value);
    else if (address >= nametables_space_start && address < palettes_space_start)
        process_nametables_write(address, value);
    else
        process_palettes_write(address, value);
}

uint8_t PPU::memory_read(uint16_t address) const
{
    if (address < nametables_space_start)
        return cartridge_ptr.lock()->mapper.map_chr_rom_read(address);
    else if (address >= nametables_space_start && address < palettes_space_start)
        return process_nametables_read(address);
    else
        return process_palettes_read(address);
}


void PPU::process_nametables_write(uint16_t address, uint8_t value)
{
    return;
}

uint8_t PPU::process_nametables_read(uint16_t address) const
{
    return 0x00;
}

void PPU::process_palettes_write(uint16_t address, uint8_t value)
{
    return;
}

uint8_t PPU::process_palettes_read(uint16_t address) const
{
    return 0x00;
}
