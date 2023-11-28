#include "../include/ppu.h"

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
    constexpr size_t fetching_subcycle_size {8};
    constexpr size_t pixel_size {1};
    constexpr size_t ppu_registers_space_size {8};

    constexpr size_t center_screen_in_x_axis {448};
    constexpr size_t center_screen_in_y_axis {60};
    constexpr size_t final_screen_width {1024};
    constexpr size_t final_screen_height {960};
        constexpr size_t framerate_cap {60};

    constexpr int actual_screen_height {262};
    constexpr int actual_screen_width {341};
    constexpr int visible_pixels_count {61440};
    constexpr int visible_screen_height {240};
    constexpr int visible_screen_width {256};

    constexpr int clear_ppu_status_cycle {1};
    constexpr int garbage_nametable_fetch_cycle {339};
    constexpr int horizontal_scroll_copy_cycle {257};
    constexpr int next_tile_fetches_cycle_end {337};
    constexpr int next_tile_fetches_cycle_start {320};
    constexpr int post_render_scanline_number {240};
    constexpr int pre_render_scanline_number {261};
    constexpr int set_vblank_flag_cycle {1};
    constexpr int vblank_scanline_number {241};
    constexpr int vertical_scroll_copy_cycle_end {305};
    constexpr int vertical_scroll_copy_cycle_start {279};

    constexpr uint8_t fine_y_max_value {0x07};
    constexpr uint8_t nametable_change_to_attribute_bound {0x1D};
    constexpr uint8_t nametable_coarse_bound {0x1F};
    constexpr uint8_t pixel_color_lsb_default_shift {0x0F};
    constexpr uint8_t pixel_color_msb_default_shift {0x0E};
    constexpr uint8_t vram_increment_enabled_value {0x20};
    constexpr uint8_t vram_increment_disabled_value {0x01};

    constexpr uint8_t fine_registers_bits_mask {0b0000'0111};
    constexpr uint8_t first_address_write_mask {0b0011'1111};
    constexpr uint8_t first_bit_mask {0b0000'0001};
    constexpr uint8_t first_two_bits_mask {0b0000'0011};
    constexpr uint8_t second_bit_mask {0b0000'0010};

    constexpr uint16_t second_pattern_table_offset {0x1000};
    constexpr uint16_t second_plane_offset {0x0008};
    constexpr uint16_t tile_column_offset {0x0010};

    constexpr uint16_t first_attribute_table_start {0x23C0};
    constexpr uint16_t nametables_space_start {0x2000};
    constexpr uint16_t palettes_space_start {0x3F00};

    constexpr uint16_t loopy_no_fine_y_mask {0x0FFF};
    constexpr uint16_t lower_byte_mask {0x00FF};
    constexpr uint16_t multiplexer_default_pointer {0b1000'0000'0000'0000};
    constexpr uint16_t palette_bg_color_mask {0x3F00};
    constexpr uint16_t upper_byte_mask {0xFF00};

    bool check_for_pixel_within_visible_screen(int x_coord, int y_coord)
    {
        return x_coord >= 0 && x_coord < visible_screen_width
            && y_coord >= 0 && y_coord < visible_screen_height;
    }
}


/////////
// API //
/////////

PPU::PPU() : app_screen{sf::VideoMode(visible_screen_width, visible_screen_height), "Yume NES"}
{
    frame_buffer.reserve(visible_pixels_count);

    for (auto i {0}; i < visible_screen_height; i++) {
        for (auto j {0}; j < visible_screen_width; j++) {
            sf::RectangleShape square(sf::Vector2f(pixel_size, pixel_size));
            const auto x_coord = static_cast<float>(j);
            const auto y_coord = static_cast<float>(i);
            square.setPosition(x_coord, y_coord);

            frame_buffer.push_back(square);
        }
    }

    app_screen.setSize({final_screen_width, final_screen_height});
    app_screen.setPosition({center_screen_in_x_axis, center_screen_in_y_axis});
    app_screen.setFramerateLimit(framerate_cap);
    app_screen.setVerticalSyncEnabled(false);
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

    if (current_scanline >= 0 && current_scanline < post_render_scanline_number)
        rendering_mode = RenderingMode::visible_scanline;
    else if (current_scanline == post_render_scanline_number)
        rendering_mode = RenderingMode::post_render_scanline;
    else if (current_scanline > post_render_scanline_number && current_scanline < pre_render_scanline_number)
        rendering_mode = RenderingMode::vblank_scanline;
    if (current_scanline == pre_render_scanline_number)
        rendering_mode = RenderingMode::pre_render_scanline;

    dispatch_rendering_mode();
    process_pixel_rendering();

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

    for (const auto& pixel : frame_buffer) {
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


///////////////////////
// Process rendering //
///////////////////////

void PPU::dispatch_rendering_mode()
{
    using RM = RenderingMode;
    switch (rendering_mode) {
        case RM::pre_render_scanline:  render_pre_render_scanline(); break;
        case RM::visible_scanline:     render_visible_scanline();    break;
        case RM::post_render_scanline:                               break;
        case RM::vblank_scanline:      render_vblank_scanline();     break;
    }
}

void PPU::render_pre_render_scanline()
{
    if (current_cycle == clear_ppu_status_cycle)
        ppu_status.word = 0x00;

    render_visible_scanline();

    if (current_cycle > vertical_scroll_copy_cycle_start && current_cycle < vertical_scroll_copy_cycle_end)
        copy_vertical_scroll_to_address();
}

void PPU::render_visible_scanline()
{
    if ((current_cycle > 0 && current_cycle < horizontal_scroll_copy_cycle)
        || (current_cycle > next_tile_fetches_cycle_start && current_cycle < next_tile_fetches_cycle_end))
        process_rendering_fetches();

    if (current_cycle == visible_screen_width)
        coarse_y_increment_with_wrapping();

    if (current_cycle == horizontal_scroll_copy_cycle)
        copy_horizontal_scroll_to_address();

    if (current_cycle == next_tile_fetches_cycle_end || current_cycle == garbage_nametable_fetch_cycle)
        fetched_nametable_tile_byte = fetch_nametable_tile_byte_with_shifters_load();
}

void PPU::render_vblank_scanline()
{
    if (current_scanline == vblank_scanline_number && current_cycle == set_vblank_flag_cycle) {
        ppu_status.flag.vblank_start = 1;

        if (ppu_controller.flag.generate_nmi)
            force_nmi_in_cpu = true;
    }
}

void PPU::process_pixel_rendering()
{
    if (ppu_mask.flag.show_background == 0) {
        return;
    }

    data_multiplexer = multiplexer_default_pointer >> fine_x.internal.position;

    const auto pixel_color_lsb = static_cast<uint8_t>(
        (tile_data_first_shift_reg & data_multiplexer) >> (pixel_color_lsb_default_shift - fine_x.internal.position));
    const auto pixel_color_msb = static_cast<uint8_t>(
        (tile_data_second_shift_reg & data_multiplexer) >> (pixel_color_msb_default_shift - fine_x.internal.position));

    const uint8_t pixel_color = pixel_color_msb | pixel_color_lsb;
    const auto address_to_read = static_cast<uint16_t>(
        palettes_space_start + (fetched_attribute_table_byte << 2) + pixel_color);

    const auto final_color = PPUColors::available_colors.at(read_from_bus(address_to_read));

    const auto x_coord = current_cycle - 1;
    const auto y_coord = current_scanline;

    if (check_for_pixel_within_visible_screen(x_coord, y_coord)) {
        frame_buffer.at(y_coord * visible_screen_width + x_coord).setFillColor(final_color);
    }
}


////////////////////////////////
// Rendering subcycle fetches //
////////////////////////////////

// https://www.nesdev.org/wiki/PPU_scrolling#Tile_and_attribute_fetching
void PPU::process_rendering_fetches()
{
    const auto subcycle_dot {current_cycle % fetching_subcycle_size};

    move_shift_registers();

    if (subcycle_dot == 0)
        coarse_x_increment_with_wrapping();
    else if (subcycle_dot == 1)
        fetched_nametable_tile_byte = fetch_nametable_tile_byte_with_shifters_load();
    else if (subcycle_dot == 3)
        fetched_attribute_table_byte = fetch_attribute_table_byte();
    else if (subcycle_dot == 5)
        fetched_tile_first_plane_byte = fetch_tile_plane_byte();
    else if (subcycle_dot == 7)
        fetched_tile_second_plane_byte = fetch_tile_plane_byte(second_plane_offset);
}

uint8_t PPU::fetch_nametable_tile_byte_with_shifters_load()
{
    const uint16_t address_to_read = nametables_space_start | (ppu_address.word & loopy_no_fine_y_mask);
    load_next_tile_data_to_shift_registers();

    return read_from_bus(address_to_read);
}

uint8_t PPU::fetch_attribute_table_byte() const
{
    const uint16_t coarse_x_high_bits = ppu_address.internal.coarse_x >> 2;
    const uint16_t coarse_y_high_bits = (ppu_address.internal.coarse_y >> 2) << 3;
    const uint16_t nametable_bits = ppu_address.internal.nametable << 10;
    const uint16_t address_to_read = first_attribute_table_start | nametable_bits | coarse_y_high_bits | coarse_x_high_bits;

    const auto attribute_quadrant_shift {calculate_attribute_shift()};
    const auto attribute_table_byte {read_from_bus(address_to_read)};

    return (attribute_table_byte >> attribute_quadrant_shift) & first_two_bits_mask;
}

uint8_t PPU::calculate_attribute_shift() const
{
    const uint16_t horizontal_half_choice = (ppu_address.internal.coarse_y & second_bit_mask) << 1;
    const uint16_t vertical_half_choice = ppu_address.internal.coarse_x & second_bit_mask;

    return static_cast<uint8_t>(horizontal_half_choice | vertical_half_choice);
}

uint8_t PPU::fetch_tile_plane_byte(uint8_t plane_offset) const
{
    const uint16_t current_row_offset = ppu_address.internal.fine_y;
    const uint16_t current_tile_offset = fetched_nametable_tile_byte * tile_column_offset;
    const uint16_t pattern_table_offset = ppu_controller.flag.bg_table * second_pattern_table_offset;
    const auto address_to_read = static_cast<uint16_t>(pattern_table_offset + current_tile_offset + current_row_offset + plane_offset);

    return read_from_bus(address_to_read);
}


//////////////////////////////
// Fetches helper functions //
//////////////////////////////

// https://www.nesdev.org/wiki/PPU_scrolling#Coarse_X_increment
void PPU::coarse_x_increment_with_wrapping()
{
    if (ppu_mask.flag.show_background == 0) {
        return;
    }

    if (ppu_address.internal.coarse_x == nametable_coarse_bound) {
        ppu_address.internal.coarse_x = 0x00;
        ppu_address.internal.nametable ^= first_bit_mask;
    }
    else {
        ppu_address.internal.coarse_x++;
    }
}

// https://www.nesdev.org/wiki/PPU_scrolling#Y_increment
void PPU::coarse_y_increment_with_wrapping()
{
    if (ppu_mask.flag.show_background == 0) {
        return;
    }

    if (ppu_address.internal.fine_y < fine_y_max_value) {
        ppu_address.internal.fine_y++;
    }
    else {
        ppu_address.internal.fine_y = 0x00;

        if (ppu_address.internal.coarse_y == nametable_change_to_attribute_bound) {
            ppu_address.internal.coarse_y = 0x00;
            ppu_address.internal.nametable ^= second_bit_mask;
        }
        else if (ppu_address.internal.coarse_y == nametable_coarse_bound) {
            ppu_address.internal.coarse_y = 0x00;
        }
        else {
            ppu_address.internal.coarse_y++;
        }
    }
}

// https://www.nesdev.org/wiki/PPU_scrolling#At_dot_257_of_each_scanline
void PPU::copy_horizontal_scroll_to_address()
{
    if (ppu_mask.flag.show_background == 0) {
        return;
    }

    const uint8_t horizontal_nametable_bit = ppu_scroll.internal.nametable & first_bit_mask;

    ppu_address.internal.coarse_x = ppu_scroll.internal.coarse_x;
    ppu_address.internal.nametable = (ppu_scroll.internal.nametable & second_bit_mask) | horizontal_nametable_bit;
}

// https://www.nesdev.org/wiki/PPU_scrolling#During_dots_280_to_304_of_the_pre-render_scanline_(end_of_vblank)
void PPU::copy_vertical_scroll_to_address()
{
    if (ppu_mask.flag.show_background == 0) {
        return;
    }

    const uint8_t vertical_nametable_bit = ppu_scroll.internal.nametable & second_bit_mask;

    ppu_address.internal.coarse_y = ppu_scroll.internal.coarse_y;
    ppu_address.internal.nametable = (ppu_scroll.internal.nametable & first_bit_mask) | vertical_nametable_bit;
    ppu_address.internal.fine_y = ppu_scroll.internal.fine_y;
}

void PPU::load_next_tile_data_to_shift_registers()
{
    tile_data_first_shift_reg = (tile_data_first_shift_reg & upper_byte_mask) | fetched_tile_first_plane_byte;
    tile_data_second_shift_reg = (tile_data_second_shift_reg & upper_byte_mask) | fetched_tile_second_plane_byte;
}

void PPU::move_shift_registers()
{
    if (ppu_mask.flag.show_background == 0) {
        return;
    }

    tile_data_first_shift_reg <<= 1;
    tile_data_second_shift_reg <<= 1;
}
