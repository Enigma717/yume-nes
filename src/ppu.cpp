#include "../include/ppu.h"

#include "../include/cartridge.h"


namespace
{
    constexpr uint16_t second_nametable_offset {0x0400};
    constexpr uint16_t third_nametable_offset {0x0800};
    constexpr uint16_t attribute_table_offset {0x03C0};

    constexpr uint16_t nametables_space_start {0x2000};
    constexpr uint16_t palettes_space_start {0x3F00};

    constexpr uint16_t current_nametable_mask {0x0FFF};
    constexpr uint16_t vertical_mirroring_mask {0x0800};
    constexpr uint16_t single_screen_mirroring_mask {0x0400};

    constexpr uint16_t current_palette_mask {0x0020};
    constexpr uint16_t palette_mirror_mask {0x0010};
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


uint16_t PPU::normalize_nametables_address(uint16_t address) const
{
    using Mirroring = Cartridge::MirroringType;
    const auto& mirroring_mode {cartridge_ptr.lock()->mirroring_mode};
    const uint16_t current_nametable = address & current_nametable_mask;
    uint16_t normalized_address {0x0000};

    switch (mirroring_mode) {
        case Mirroring::horizontal:
            normalized_address = address % single_screen_mirroring_mask;

            if (current_nametable >= third_nametable_offset)
                normalized_address += second_nametable_offset;

            break;
        case Mirroring::vertical:
            normalized_address = address % vertical_mirroring_mask;
            break;
        case Mirroring::single_screen:
            normalized_address = address % single_screen_mirroring_mask;
            break;
        case Mirroring::four_screen:
            normalized_address = address; // TODO
            break;
    }

    return normalized_address;
}

uint16_t PPU::normalize_palettes_address(uint16_t address) const
{
    uint16_t normalized_address = address % current_palette_mask;

    if (check_for_palette_mirroring(normalized_address))
        normalized_address -= palette_mirror_mask;

    return normalized_address;
}

bool PPU::check_for_palette_mirroring(uint16_t address) const
{
    return address == palette_mirror_mask
        || address == (palette_mirror_mask + 0x0004)
        || address == (palette_mirror_mask + 0x0008)
        || address == (palette_mirror_mask + 0x000C);
}

void PPU::process_nametables_write(uint16_t address, uint8_t value)
{
    const uint16_t normalized_address {normalize_nametables_address(address)};

    nametables[normalized_address] = value;
}

uint8_t PPU::process_nametables_read(uint16_t address) const
{
    const uint16_t normalized_address {normalize_nametables_address(address)};

    return nametables[normalized_address];
}

void PPU::process_palettes_write(uint16_t address, uint8_t value)
{
    const uint16_t normalized_address {normalize_palettes_address(address)};

    nametables[normalized_address] = value;
}

uint8_t PPU::process_palettes_read(uint16_t address) const
{
    const uint16_t normalized_address {normalize_palettes_address(address)};

    return nametables[normalized_address];
}
