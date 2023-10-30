#include "../include/ppu.h"

#include "../include/cartridge.h"

#include <bitset>
#include <iostream>
#include <iomanip>


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
    constexpr size_t ppu_memory_size {16384};

    constexpr size_t pixel_size {1};
    constexpr size_t sprite_tile_size {8};
    constexpr size_t sprite_tiles_count_in_row {16};
    constexpr size_t sprite_tiles_count_in_col {16};
    constexpr size_t sprite_tiles_row_offset {0x0100};
    constexpr size_t sprite_tiles_col_offset {0x0010};
    constexpr size_t sprite_second_plane_offset {0x0008};

    constexpr uint8_t first_byte_mask {0b0000'0001};

    constexpr uint8_t vram_increment_enabled_value {0x20};
    constexpr uint8_t vram_increment_disabled_value {0x01};

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

void PPU::memory_write(uint16_t address, uint8_t data)
{
    if (address < nametables_space_start)
        send_write_to_mapper_chr_rom(address, data);
    else if (address >= nametables_space_start && address < palettes_space_start)
        process_nametables_write(address, data);
    else
        process_palettes_memory_write(address, data);
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

void PPU::handle_write_from_cpu(uint16_t address, uint8_t data) // TODO: Unfinished placeholders
{
    std::cout << "[DEBUG PPU] WRITE REQUESTED FROM CPU" << std::hex
        << " | ADDRESS: 0x" << static_cast<short>(address)
        << " | DATA: 0x" << static_cast<short>(data)
        << std::dec << "\n";

    address = address % ppu_registers_space_size;

    namespace RA = RegistersAddresses;
    switch (address) {
        case RA::PPUCTRL:   process_ppu_controller_write(data); break;
        case RA::PPUMASK:   process_ppu_mask_write(data);       break;
        case RA::OAMADDR:   oam_address = data;                 break;
        case RA::OAMDATA:   oam_data = data;                    break;
        case RA::PPUSCROLL: ppu_scroll.word = data;             break;
        case RA::PPUADDR:   process_ppu_address_write(data);    break;
        case RA::PPUDATA:   process_ppu_data_write(data);       break;
        default: break;
    }

    log_debug_info();
}

uint8_t PPU::handle_read_from_cpu(uint16_t address) // TODO: Unfinished placeholders
{
    std::cout << "[DEBUG PPU] READ REQUESTED FROM CPU" << std::hex
        << " | AT ADDRESS: 0x" << static_cast<short>(address)
        << std::dec << "\n";

    address = address % ppu_registers_space_size;

    log_debug_info();

    namespace RA = RegistersAddresses;
    switch (address) {
        case RA::PPUSTATUS: return process_ppu_status_read(); break;
        case RA::OAMDATA:   return oam_data;                  break;
        case RA::PPUDATA:   return process_ppu_data_read();   break;
        default: return 0x00; break;
    }

}

void PPU::perform_cycle()
{
    render_next_cycle();

    current_cycle++;

    if (current_cycle == 341) {
        current_cycle = 0;
        current_scanline++;

        if (current_scanline == 261)
            current_scanline = -1;
    }
}

void PPU::render_next_cycle()
{

}


void PPU::log_debug_info() const
{
    std::cout << "[DEBUG PPU] CYCLE: " << std::setw(10) << std::left << std::setfill(' ') << current_cycle;
    std::cout << std::hex << std::uppercase << std::setfill('0')
        << " | PPUCTRL: 0x" << std::setw(2) << std::right << static_cast<short>(ppu_controller.word)
        << " | PPUMASK: 0x" << std::setw(2) << std::right << static_cast<short>(ppu_mask.word)
        << " | PPUSTATUS: 0x" << std::setw(2) << std::right << static_cast<short>(ppu_status.word)
        << " | OAMADDR: 0x" << std::setw(2) << std::right << static_cast<short>(oam_address)
        << " | OAMDATA: 0x" << std::setw(2) << std::right << static_cast<short>(oam_data)
        << " | PPUSCROLL: 0x" << std::setw(4) << std::right << static_cast<short>(ppu_scroll.word)
        << " | PPUADDR: 0x" << std::setw(4) << std::right << static_cast<short>(ppu_address.word)
        << " | PPUDATA: 0x" << std::setw(2) << std::right << static_cast<short>(ppu_data)
        << std::dec << "\n";
}

void PPU::log_debug_palettes_ram_data() const
{
    std::cout << "[DEBUG PPU] CYCLE: " << std::setw(10) << std::left << std::setfill(' ') << current_cycle;
    std::cout << std::hex << std::uppercase << std::setfill('0')
        << " | BACKGROUND: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[0])
        << " || BG PALETTE 0: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[1])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[2])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[3])
        << " || BG PALETTE 1: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[5])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[6])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[7])
        << " || BG PALETTE 2: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[9])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[10])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[11])
        << " || BG PALETTE 3: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[13])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[14])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[15])
        << std::dec << "\n";

    std::cout << "[DEBUG PPU] CYCLE: " << std::setw(10) << std::left << std::setfill(' ') << current_cycle;
    std::cout << std::hex << std::uppercase << std::setfill('0')
        << " | FG PALETTE 0: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[17])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[18])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[19])
        << " || FG PALETTE 1: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[21])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[22])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[23])
        << " || FG PALETTE 2: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[25])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[26])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[27])
        << " || FG PALETTE 3: 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[29])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[30])
        << " | 0x" << std::setw(2) << std::right << static_cast<short>(palettes_ram[31])
        << std::dec << "\n";
}

void PPU::log_debug_register_write(const std::string& register_name) const
{
    std::cout << "[DEBUG PPU] WRITE TO " << register_name << "\n";
}

void PPU::log_debug_register_read(const std::string& register_name) const
{
    std::cout << "[DEBUG PPU] READ FROM " << register_name << "\n";
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
                        col_tile * sprite_tile_size + ((sprite_tile_size - 1) - col_pixel) + (128 * pattern_table_number));
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

    log_debug_palettes_ram_data();

    return normalized_address;
}

bool PPU::check_for_palette_mirroring(uint16_t address) const
{
    return address == palette_mirror_mask
        || address == (palette_mirror_mask + 0x0004)
        || address == (palette_mirror_mask + 0x0008)
        || address == (palette_mirror_mask + 0x000C);
}

void PPU::send_write_to_mapper_chr_rom(uint16_t address, uint8_t data) const
{
    cartridge_ptr.lock()->mapper.map_chr_rom_write(address, data);
}

uint8_t PPU::send_read_to_mapper_chr_rom(uint16_t address) const
{
    return cartridge_ptr.lock()->mapper.map_chr_rom_read(address);
}

void PPU::process_nametables_write(uint16_t address, uint8_t data)
{
    const auto normalized_address {normalize_nametables_address(address)};

    nametables[normalized_address] = data;
}

uint8_t PPU::process_nametables_read(uint16_t address) const
{
    const auto normalized_address {normalize_nametables_address(address)};

    return nametables[normalized_address];
}

void PPU::process_palettes_memory_write(uint16_t address, uint8_t data)
{
    const auto normalized_address {normalize_palettes_address(address)};

    palettes_ram[normalized_address] = data;
}

uint8_t PPU::process_palettes_memory_read(uint16_t address) const
{
    const auto normalized_address {normalize_palettes_address(address)};

    return palettes_ram[normalized_address];
}

void PPU::process_ppu_controller_write(uint8_t data)
{
    log_debug_register_write(std::string("PPU CONTROLLER"));

    ppu_controller.word = data;
}

void PPU::process_ppu_mask_write(uint8_t data)
{
    log_debug_register_write("PPU MASK");

    ppu_mask.word = data;
}

void PPU::process_ppu_address_write(uint8_t data)
{
    if (!second_address_write_latch) {
        log_debug_register_write("PPU ADDRESS FIRST WRITE");

        temp_ppu_address_msb = data;
        second_address_write_latch = !second_address_write_latch;
    }
    else {
        log_debug_register_write("PPU ADDRESS SECOND WRITE");

        ppu_address.word = (temp_ppu_address_msb << 8) | data;
        ppu_address.word = ppu_address.word % ppu_memory_size;
        second_address_write_latch = !second_address_write_latch;
    }
}

void PPU::process_ppu_data_write(uint8_t data)
{
    log_debug_register_write("PPU DATA");

    memory_write(ppu_address.word, data);

    if (ppu_controller.flag.vram_increment)
        ppu_address.word += vram_increment_enabled_value;
    else
        ppu_address.word += vram_increment_disabled_value;
}

uint8_t PPU::process_ppu_status_read()
{
    log_debug_register_read("PPU STATUS");

    ppu_status.flag.vblank_start = 0;
    second_address_write_latch = false;
    perform_cycle();            //
                                //
    if (current_cycle > 0)      //
        ppu_status.word = 0x80; // TO REMOVE, DEBUG PURPOUSES

    return ppu_status.word;
}

uint8_t PPU::process_ppu_data_read()
{
    log_debug_register_read("PPU DATA");

    ppu_data = data_read_buffer;
    data_read_buffer = memory_read(ppu_address.word);

    if (ppu_controller.flag.vram_increment)
        ppu_address.word += vram_increment_enabled_value;
    else
        ppu_address.word += vram_increment_disabled_value;

    return ppu_data;
}
