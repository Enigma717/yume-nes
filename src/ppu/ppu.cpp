#include "../../include/ppu/ppu.h"

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
    constexpr size_t center_screen_in_x_axis {448};
    constexpr size_t center_screen_in_y_axis {60};
    constexpr size_t final_screen_width {1024};
    constexpr size_t final_screen_height {960};
    constexpr size_t framerate_cap {60};

    constexpr int actual_screen_height {262};
    constexpr int actual_screen_width {341};
    constexpr int visible_screen_height {240};
    constexpr int visible_screen_width {256};

    constexpr uint8_t vram_increment_enabled_value {0x20};
    constexpr uint8_t vram_increment_disabled_value {0x01};
    constexpr uint8_t fine_registers_bits_mask {0b0000'0111};
    constexpr uint8_t first_address_write_mask {0b0011'1111};
    constexpr uint8_t first_two_bits_mask {0b0000'0011};

    constexpr uint16_t palettes_space_start {0x3F00};
    constexpr uint16_t lower_byte_mask {0x00FF};
    constexpr uint16_t palette_bg_color_mask {0x3F00};
    constexpr uint16_t upper_byte_mask {0xFF00};
}


/////////
// API //
/////////

PPU::PPU()
: app_screen{sf::VideoMode(visible_screen_width, visible_screen_height), "Yume NES"},
  renderer{*this}
{
    app_screen.setSize({final_screen_width, final_screen_height});
    app_screen.setPosition({center_screen_in_x_axis, center_screen_in_y_axis});
    app_screen.setFramerateLimit(framerate_cap);
}

void PPU::connect_bus_with_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    memory_bus.insert_cartridge(cartridge);
}

// https://www.nesdev.org/wiki/PPU_rendering#Line-by-line_timing
void PPU::perform_cycle(bool debug_mode)
{
    if (debug_mode)
        log_debug_info();

    renderer.prepare_next_pixel();

    current_cycle++;

    if (current_cycle == actual_screen_width) {
        current_cycle = 0;
        current_scanline++;

        if (current_scanline == actual_screen_height) {
            current_scanline = 0;
        }
    }
}

void PPU::render_whole_frame()
{
    const auto& bg_color {PPUColors::available_colors.at(read_from_bus(palette_bg_color_mask))};

    app_screen.setSize({final_screen_width, final_screen_height});
    app_screen.clear(bg_color);

    for (const auto& pixel : renderer.frame_buffer) {
        if (pixel.getFillColor() != bg_color)
            app_screen.draw(pixel);
    }

    app_screen.display();
}

void PPU::log_debug_info() const
{
    std::cout << "[DEBUG PPU] LINE: " << std::setw(4) << std::left << std::setfill(' ') << current_scanline
        << " | CYCLE: " << std::setw(4) << std::left << std::setfill(' ') << current_cycle;
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


////////////////////
// Bus management //
////////////////////

void PPU::write_to_bus(uint16_t address, uint8_t data)
{
    memory_bus.dispatch_write_to_device(address, data);
}

uint8_t PPU::read_from_bus(uint16_t address) const
{
    return memory_bus.dispatch_read_to_device(address);
}


//////////////////////////
// Registers management //
//////////////////////////

// https://www.nesdev.org/wiki/PPU_scrolling#$2007_reads_and_writes
void PPU::increment_vram_address()
{
    if (ppu_controller.flag.vram_increment)
        ppu_address.word += vram_increment_enabled_value;
    else
        ppu_address.word += vram_increment_disabled_value;
}

void PPU::handle_register_write_from_cpu(uint16_t address, uint8_t data)
{
    address = address % ppu_registers_space_size;

    namespace RA = RegistersAddresses;
    switch (address) {
        case RA::PPUCTRL:   process_ppu_controller_write(data); break;
        case RA::PPUMASK:   process_ppu_mask_write(data);       break;
        case RA::OAMADDR:   oam_address = data;                 break;
        case RA::OAMDATA:   oam_data = data;                    break;
        case RA::PPUSCROLL: process_ppu_scroll_write(data);     break;
        case RA::PPUADDR:   process_ppu_address_write(data);    break;
        case RA::PPUDATA:   process_ppu_data_write(data);       break;
    }
}

void PPU::process_ppu_controller_write(uint8_t data)
{
    ppu_scroll.internal.nametable = data & first_two_bits_mask;
    ppu_controller.word = data;
}

void PPU::process_ppu_mask_write(uint8_t data)
{
    ppu_mask.word = data;
}

// https://www.nesdev.org/wiki/PPU_scrolling#$2005_first_write_(w_is_0)
// https://www.nesdev.org/wiki/PPU_scrolling#$2005_second_write_(w_is_1)
void PPU::process_ppu_scroll_write(uint8_t data)
{
    if (second_address_write_latch == false) {
        ppu_scroll.internal.coarse_x = data >> 3;
        fine_x.internal.position = data & fine_registers_bits_mask;
        second_address_write_latch = true;
    }
    else {
        ppu_scroll.internal.coarse_y = data >> 3;
        ppu_scroll.internal.fine_y = data & fine_registers_bits_mask;
        second_address_write_latch = false;
    }
}

// https://www.nesdev.org/wiki/PPU_scrolling#$2006_first_write_(w_is_0)
// https://www.nesdev.org/wiki/PPU_scrolling#$2006_second_write_(w_is_1)
void PPU::process_ppu_address_write(uint8_t data)
{
    if (second_address_write_latch == false) {
        uint16_t temp_address = (data & first_address_write_mask) << 8;
        ppu_scroll.word = (ppu_scroll.word & lower_byte_mask) | temp_address;
        second_address_write_latch = true;
    }
    else {
        ppu_scroll.word = (ppu_scroll.word & upper_byte_mask) | data;
        ppu_address.word = ppu_scroll.word;
        second_address_write_latch = false;
    }
}

void PPU::process_ppu_data_write(uint8_t data)
{
    write_to_bus(ppu_address.word, data);

    increment_vram_address();
}

uint8_t PPU::handle_register_read_from_cpu(uint16_t address)
{
    address = address % ppu_registers_space_size;

    namespace RA = RegistersAddresses;
    switch (address) {
        case RA::PPUSTATUS: return process_ppu_status_read(); break;
        case RA::OAMDATA:   return oam_data;                  break;
        case RA::PPUDATA:   return process_ppu_data_read();   break;
        default: return 0x00; break;
    }
}

uint8_t PPU::process_ppu_status_read()
{
    const uint8_t current_status = ppu_status.word;

    ppu_status.flag.vblank_start = 0;
    second_address_write_latch = false;

    return current_status;
}

// https://www.nesdev.org/wiki/PPU_registers#The_PPUDATA_read_buffer_(post-fetch)
uint8_t PPU::process_ppu_data_read()
{
    const auto pre_increment_address {ppu_address.word};

    ppu_data = ppu_data_read_buffer;
    ppu_data_read_buffer = read_from_bus(ppu_address.word);

    increment_vram_address();

    if (pre_increment_address >= palettes_space_start)
        return ppu_data_read_buffer;
    else
        return ppu_data;
}
