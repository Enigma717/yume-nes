#include "../include/ppu_bus.h"


namespace
{
    constexpr uint16_t nametables_space_start {0x2000};
    constexpr uint16_t palettes_space_start {0x3F00};

    constexpr uint16_t second_nametable_offset {0x0400};
    constexpr uint16_t third_nametable_offset {0x0800};

    constexpr uint16_t current_nametable_mask {0x0FFF};
    constexpr uint16_t current_palette_mask {0x0020};
    constexpr uint16_t palette_mirror_mask {0x0010};
    constexpr uint16_t single_screen_mirroring_mask {0x0400};
    constexpr uint16_t vertical_mirroring_mask {0x0800};
}


void PPUBus::insert_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    cartridge_ptr = cartridge;
    current_mirroring_mode = cartridge_ptr.lock()->mirroring_mode;
}

void PPUBus::dispatch_write_to_device(uint16_t address, uint8_t data)
{
    if (address < nametables_space_start)
        return;
    else if (address >= nametables_space_start && address < palettes_space_start)
        process_vram_write(address, data);
    else
        process_palettes_ram_write(address, data);
}

uint8_t PPUBus::dispatch_read_to_device(uint16_t address) const
{
    if (address < nametables_space_start)
        return send_read_to_mapper_chr_rom(address);
    else if (address >= nametables_space_start && address < palettes_space_start)
        return process_vram_read(address);
    else
        return process_palettes_ram_read(address);
}

void PPUBus::process_vram_write(uint16_t address, uint8_t data)
{
    const auto normalized_address {normalize_vram_address(address)};

    vram.at(normalized_address) = data;
}

void PPUBus::process_palettes_ram_write(uint16_t address, uint8_t data)
{
    const auto normalized_address {normalize_palettes_address(address)};

    palettes_ram.at(normalized_address) = data;
}

uint8_t PPUBus::send_read_to_mapper_chr_rom(uint16_t address) const
{
    return cartridge_ptr.lock()->mapper.map_chr_rom_read(address);
}

uint8_t PPUBus::process_vram_read(uint16_t address) const
{
    const auto normalized_address {normalize_vram_address(address)};

    return vram.at(normalized_address);
}

uint8_t PPUBus::process_palettes_ram_read(uint16_t address) const
{
    const auto normalized_address {normalize_palettes_address(address, true)};

    return palettes_ram.at(normalized_address);
}


uint16_t PPUBus::normalize_vram_address(uint16_t address) const
{
    using Mirroring = Cartridge::MirroringType;
    const uint16_t current_nametable = address & current_nametable_mask;
    uint16_t normalized_address {0x0000};

    switch (current_mirroring_mode) {
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

uint16_t PPUBus::normalize_palettes_address(uint16_t address, bool is_reading) const
{
    uint16_t normalized_address = address % current_palette_mask;

    if (check_for_palette_mirroring(normalized_address))
        normalized_address -= palette_mirror_mask;

    if (is_reading && check_for_background_read(normalized_address))
        normalized_address = 0x0000;

    return normalized_address;
}

bool PPUBus::check_for_palette_mirroring(uint16_t address) const
{
    return address == palette_mirror_mask
        || address == (palette_mirror_mask + 0x0004)
        || address == (palette_mirror_mask + 0x0008)
        || address == (palette_mirror_mask + 0x000C);
}

bool PPUBus::check_for_background_read(uint16_t address) const
{
    return address == 0x0004
        || address == 0x0008
        || address == 0x000C;
}
