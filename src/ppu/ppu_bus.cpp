#include "../../include/ppu/ppu_bus.h"

namespace
{
    constexpr std::uint16_t nametables_space_start {0x2000u};
    constexpr std::uint16_t palettes_space_start {0x3F00u};

    constexpr std::uint16_t second_nametable_offset {0x0400u};
    constexpr std::uint16_t third_nametable_offset {0x0800u};

    constexpr std::uint16_t current_nametable_mask {0x0FFFu};
    constexpr std::uint16_t current_palette_mask {0x0020u};
    constexpr std::uint16_t palette_mirror_mask {0x0010u};
    constexpr std::uint16_t single_screen_mirroring_mask {0x0400u};
    constexpr std::uint16_t vertical_mirroring_mask {0x0800u};
}

/////////
// API //
/////////

void PPUBus::insert_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    cartridge_ptr = cartridge;
    current_mirroring_mode = cartridge_ptr.lock()->mirroring_mode;
}

void PPUBus::dispatch_write_to_device(std::uint16_t address, std::uint8_t data)
{
    if (address < nametables_space_start)
        return;
    else if (address >= nametables_space_start && address < palettes_space_start)
        process_vram_write(address, data);
    else
        process_palettes_ram_write(address, data);
}

std::uint8_t PPUBus::dispatch_read_to_device(std::uint16_t address) const
{
    if (address < nametables_space_start)
        return send_read_to_mapper_chr_rom(address);
    else if (address >= nametables_space_start && address < palettes_space_start)
        return process_vram_read(address);
    else
        return process_palettes_ram_read(address);
}

///////////////////
// Write methods //
///////////////////

void PPUBus::process_vram_write(std::uint16_t address, std::uint8_t data)
{
    const auto normalized_address {normalize_vram_address(address)};

    vram.at(normalized_address) = data;
}

void PPUBus::process_palettes_ram_write(std::uint16_t address, std::uint8_t data)
{
    const auto normalized_address {normalize_palettes_address(address)};

    palettes_ram.at(normalized_address) = data;
}

//////////////////
// Read methods //
//////////////////

std::uint8_t PPUBus::send_read_to_mapper_chr_rom(std::uint16_t address) const
{
    return cartridge_ptr.lock()->mapper.map_chr_rom_read(address);
}

std::uint8_t PPUBus::process_vram_read(std::uint16_t address) const
{
    const auto normalized_address {normalize_vram_address(address)};

    return vram.at(normalized_address);
}

std::uint8_t PPUBus::process_palettes_ram_read(std::uint16_t address) const
{
    const auto normalized_address {normalize_palettes_address(address, true)};

    return palettes_ram.at(normalized_address);
}

///////////////////////
// Address preparing //
///////////////////////

std::uint16_t PPUBus::normalize_vram_address(std::uint16_t address) const
{
    using Mirroring = Cartridge::MirroringType;
    const auto current_nametable {
        static_cast<std::uint16_t>(address & current_nametable_mask)};
    std::uint16_t normalized_address {0x0000u};

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
            normalized_address = address;
            break;
    }

    return normalized_address;
}

std::uint16_t PPUBus::normalize_palettes_address(std::uint16_t address, bool is_reading) const
{
    auto normalized_address {static_cast<std::uint16_t>(address % current_palette_mask)};

    if (check_for_palette_mirroring(normalized_address))
        normalized_address -= palette_mirror_mask;

    if (is_reading && check_for_background_read(normalized_address))
        normalized_address = 0x0000u;

    return normalized_address;
}

bool PPUBus::check_for_palette_mirroring(std::uint16_t address) const
{
    return address == palette_mirror_mask
        || address == (palette_mirror_mask + 0x0004u)
        || address == (palette_mirror_mask + 0x0008u)
        || address == (palette_mirror_mask + 0x000Cu);
}

bool PPUBus::check_for_background_read(std::uint16_t address) const
{
    return address == 0x0004u
        || address == 0x0008u
        || address == 0x000Cu;
}
