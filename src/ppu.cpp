#include "../include/ppu.h"

#include "../include/cartridge.h"


namespace RegistersAddresses
{
    constexpr uint16_t PPUCTRL   {0x0000};
    constexpr uint16_t PPUMASK   {0x0001};
    constexpr uint16_t PPUSTATUS {0x0002};
    constexpr uint16_t OAMADDR   {0x0003};
    constexpr uint16_t OAMDATA   {0x0004};
    constexpr uint16_t PPUSCROLL {0x0005};
    constexpr uint16_t PPUADDR   {0x0006};
    constexpr uint16_t PPUDATA   {0x0007};
}

namespace
{
    constexpr size_t ppu_registers_space_size {8};

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
        send_write_to_mapper_chr_rom(address, value);
    else if (address >= nametables_space_start && address < palettes_space_start)
        process_nametables_write(address, value);
    else
        process_palettes_memory_write(address, value);
}

uint8_t PPU::memory_read(uint16_t address) const
{
    if (address < nametables_space_start)
        return send_read_to_mapper_chr_rom(address);
    else if (address >= nametables_space_start && address < palettes_space_start)
        return process_nametables_read(address);
    else
        return process_palettes_memory_read(address);
}

void PPU::handle_write_from_cpu(uint16_t address, uint8_t value) // TODO: Unfinished placeholders
{
    address = address % ppu_registers_space_size;

    namespace RA = RegistersAddresses;
    switch (address) {
        case RA::PPUCTRL:   ppu_ctrl.word = value;   break;
        case RA::PPUMASK:   ppu_mask.word = value;   break;
        case RA::PPUSTATUS: ppu_status.word = value; break;
        case RA::OAMADDR:   oam_address = value;     break;
        case RA::OAMDATA:   oam_data = value;        break;
        case RA::PPUSCROLL: ppu_scroll.word = value; break;
        case RA::PPUADDR:   ppu_addr.word = value;   break;
        case RA::PPUDATA:   ppu_data = value;        break;
        default: break;
    }
}

uint8_t PPU::handle_read_from_cpu(uint16_t address) const // TODO: Unfinished placeholders
{
    address = address % ppu_registers_space_size;

    namespace RA = RegistersAddresses;
    switch (address) {
        case RA::PPUCTRL:   return ppu_ctrl.word;   break;
        case RA::PPUMASK:   return ppu_mask.word;   break;
        case RA::PPUSTATUS: return ppu_status.word; break;
        case RA::OAMADDR:   return oam_address;     break;
        case RA::OAMDATA:   return oam_data;        break;
        case RA::PPUSCROLL: return static_cast<uint8_t>(ppu_scroll.word); break;
        case RA::PPUADDR:   return static_cast<uint8_t>(ppu_addr.word);   break;
        case RA::PPUDATA:   return ppu_data;        break;
        default: return 0x00; break;
    }
}

void PPU::perform_cycle()
{
    current_cycle++;
}


uint16_t PPU::normalize_nametables_address(uint16_t address) const
{
    using Mirroring = Cartridge::MirroringType;
    const auto mirroring_mode {cartridge_ptr.lock()->mirroring_mode};
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

void PPU::send_write_to_mapper_chr_rom(uint16_t address, uint8_t value) const
{
    cartridge_ptr.lock()->mapper.map_chr_rom_write(address, value);
}

uint8_t PPU::send_read_to_mapper_chr_rom(uint16_t address) const
{
    return cartridge_ptr.lock()->mapper.map_chr_rom_read(address);
}

void PPU::process_nametables_write(uint16_t address, uint8_t value)
{
    const auto normalized_address {normalize_nametables_address(address)};

    nametables[normalized_address] = value;
}

uint8_t PPU::process_nametables_read(uint16_t address) const
{
    const auto normalized_address {normalize_nametables_address(address)};

    return nametables[normalized_address];
}

void PPU::process_palettes_memory_write(uint16_t address, uint8_t value)
{
    const auto normalized_address {normalize_palettes_address(address)};

    palettes_memory[normalized_address] = value;
}

uint8_t PPU::process_palettes_memory_read(uint16_t address) const
{
    const auto normalized_address {normalize_palettes_address(address)};

    return palettes_memory[normalized_address];
}
