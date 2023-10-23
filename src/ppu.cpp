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

    constexpr size_t pixel_size {1};
    constexpr size_t sprite_tile_size {8};
    constexpr size_t sprite_tiles_count_in_row {16};
    constexpr size_t sprite_tiles_count_in_col {16};
    constexpr size_t sprite_tiles_row_offset {0x0100};
    constexpr size_t sprite_tiles_col_offset {0x0010};
    constexpr size_t sprite_second_plane_offset {0x0008};

    constexpr uint8_t transparent_pixel_value {0x00};

    constexpr uint8_t first_byte_mask {0b0000'0001};

    constexpr uint16_t second_nametable_offset {0x0400};
    constexpr uint16_t third_nametable_offset {0x0800};
    constexpr uint16_t attribute_table_offset {0x03C0};
    constexpr uint16_t second_pattern_table_offset {0x1000};

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

void PPU::prepare_sprites_tiles_memory()
{
    prepare_pattern_table(0);
    prepare_pattern_table(1);
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
        case RA::PPUSTATUS: return process_ppu_status_read(); break;
        case RA::OAMDATA:   return oam_data; break;
        case RA::PPUDATA:   return ppu_data; break;
        default: return 0x00; break;
    }
}

void PPU::perform_cycle()
{
    current_cycle++;
}


void PPU::prepare_pattern_table(int pattern_table_number)
{
    for (size_t row_tile {0}; row_tile < sprite_tiles_count_in_row; row_tile++) {
        for (size_t col_tile {0}; col_tile < sprite_tiles_count_in_col; col_tile++) {
            SpriteTile current_tile;
            const auto current_tile_index {
                row_tile * sprite_tiles_row_offset + col_tile * sprite_tiles_col_offset};

            for (size_t row_pixel {0}; row_pixel < sprite_tile_size; row_pixel++) {
                const auto default_tile_index {
                    (pattern_table_number * second_pattern_table_offset) + current_tile_index + row_pixel};

                const auto tile_row_lsb_index = static_cast<uint16_t>(default_tile_index);
                const auto tile_row_msb_index = static_cast<uint16_t>(default_tile_index + sprite_second_plane_offset);

                auto tile_row_lsb {memory_read(tile_row_lsb_index)};
                auto tile_row_msb {memory_read(tile_row_msb_index)};

                for (size_t col_pixel {0}; col_pixel < sprite_tile_size; col_pixel++) {
                    const auto pixel_color_index {
                        ((tile_row_msb & first_byte_mask) << 1) | (tile_row_lsb & first_byte_mask)};

                    tile_row_lsb >>= 1;
                    tile_row_msb >>= 1;

                    const auto pixel_x_coord = static_cast<float>(
                        col_tile * sprite_tile_size + (7 - col_pixel) + (128 * pattern_table_number));
                    const auto pixel_y_coord = static_cast<float>(
                        row_tile * sprite_tile_size + row_pixel);

                    Pixel current_pixel;
                    sf::RectangleShape pixel(sf::Vector2f(pixel_size, pixel_size));

                    pixel.setPosition(pixel_x_coord, pixel_y_coord);

                    current_pixel.sfml_pixel = pixel;
                    current_pixel.color_index = pixel_color_index;

                    current_tile.pixels.push_back(current_pixel);
                }
            }

            sprites_tiles.push_back(current_tile);
        }
    }
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

    palettes_ram[normalized_address] = value;
}

uint8_t PPU::process_palettes_memory_read(uint16_t address) const
{
    const auto normalized_address {normalize_palettes_address(address)};

    return palettes_ram[normalized_address];
}

uint8_t PPU::process_ppu_status_read()
{
    ppu_status.vblank_start = 0;
    first_read_done_latch = false;

    return ppu_status.word;
}
