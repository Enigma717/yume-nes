#include "../../include/ppu/ppu.h"


namespace
{
    constexpr size_t fetching_subcycle_size {8};
    constexpr size_t pixel_size {1};

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
    constexpr uint16_t multiplexer_default_pointer {0b1000'0000'0000'0000};
    constexpr uint16_t upper_byte_mask {0xFF00};

    bool check_for_pixel_within_visible_screen(int x_coord, int y_coord)
    {
        return x_coord >= 0 && x_coord < visible_screen_width
            && y_coord >= 0 && y_coord < visible_screen_height;
    }
}


Renderer::Renderer(PPU& ppu_ref) : ppu_ref{ppu_ref}
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
}


///////////////////////
// Process rendering //
///////////////////////

void Renderer::prepare_next_pixel()
{
    choose_rendering_mode();
    dispatch_rendering_mode();
    process_pixel_rendering();
}

void Renderer::choose_rendering_mode()
{
    if (ppu_ref.current_scanline >= 0 && ppu_ref.current_scanline < post_render_scanline_number)
        rendering_mode = RenderingMode::visible_scanline;
    else if (ppu_ref.current_scanline == post_render_scanline_number)
        rendering_mode = RenderingMode::post_render_scanline;
    else if (ppu_ref.current_scanline > post_render_scanline_number && ppu_ref.current_scanline < pre_render_scanline_number)
        rendering_mode = RenderingMode::vblank_scanline;
    if (ppu_ref.current_scanline == pre_render_scanline_number)
        rendering_mode = RenderingMode::pre_render_scanline;
}

void Renderer::dispatch_rendering_mode()
{
    using RM = RenderingMode;
    switch (rendering_mode) {
        case RM::pre_render_scanline:  render_pre_render_scanline(); break;
        case RM::visible_scanline:     render_visible_scanline();    break;
        case RM::post_render_scanline:                               break;
        case RM::vblank_scanline:      render_vblank_scanline();     break;
    }
}

void Renderer::render_pre_render_scanline()
{
    if (ppu_ref.current_cycle == clear_ppu_status_cycle)
        ppu_ref.ppu_status.word = 0x00;

    render_visible_scanline();

    if (ppu_ref.current_cycle > vertical_scroll_copy_cycle_start && ppu_ref.current_cycle < vertical_scroll_copy_cycle_end)
        copy_vertical_scroll_to_address();
}

void Renderer::render_visible_scanline()
{
    if ((ppu_ref.current_cycle > 0 && ppu_ref.current_cycle < horizontal_scroll_copy_cycle)
        || (ppu_ref.current_cycle > next_tile_fetches_cycle_start && ppu_ref.current_cycle < next_tile_fetches_cycle_end))
        process_rendering_fetches();

    if (ppu_ref.current_cycle == visible_screen_width)
        coarse_y_increment_with_wrapping();

    if (ppu_ref.current_cycle == horizontal_scroll_copy_cycle)
        copy_horizontal_scroll_to_address();

    if (ppu_ref.current_cycle == next_tile_fetches_cycle_end || ppu_ref.current_cycle == garbage_nametable_fetch_cycle)
        fetched_nametable_tile_byte = fetch_nametable_tile_byte_with_shifters_load();
}

void Renderer::render_vblank_scanline()
{
    if (ppu_ref.current_scanline == vblank_scanline_number && ppu_ref.current_cycle == set_vblank_flag_cycle) {
        ppu_ref.ppu_status.flag.vblank_start = 1;

        if (ppu_ref.ppu_controller.flag.generate_nmi)
            ppu_ref.force_nmi_in_cpu = true;
    }
}

void Renderer::process_pixel_rendering()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    data_multiplexer = multiplexer_default_pointer >> ppu_ref.fine_x.internal.position;

    const auto pixel_color_lsb = static_cast<uint8_t>(
        (tile_data_first_shift_reg & data_multiplexer) >> (pixel_color_lsb_default_shift - ppu_ref.fine_x.internal.position));
    const auto pixel_color_msb = static_cast<uint8_t>(
        (tile_data_second_shift_reg & data_multiplexer) >> (pixel_color_msb_default_shift - ppu_ref.fine_x.internal.position));

    const uint8_t pixel_color = pixel_color_msb | pixel_color_lsb;
    const auto address_to_read = static_cast<uint16_t>(
        palettes_space_start + (fetched_attribute_table_byte << 2) + pixel_color);

    const auto final_color = PPUColors::available_colors.at(ppu_ref.read_from_bus(address_to_read));

    const auto x_coord = ppu_ref.current_cycle - 1;
    const auto y_coord = ppu_ref.current_scanline;

    if (check_for_pixel_within_visible_screen(x_coord, y_coord)) {
        const auto pixel_index {y_coord * visible_screen_width + x_coord};
        frame_buffer.at(pixel_index).setFillColor(final_color);
    }
}


////////////////////////////////
// Rendering subcycle fetches //
////////////////////////////////

// https://www.nesdev.org/wiki/PPU_scrolling#Tile_and_attribute_fetching
void Renderer::process_rendering_fetches()
{
    const auto subcycle_dot {ppu_ref.current_cycle % fetching_subcycle_size};

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

uint8_t Renderer::fetch_nametable_tile_byte_with_shifters_load()
{
    const uint16_t address_to_read = nametables_space_start | (ppu_ref.ppu_address.word & loopy_no_fine_y_mask);
    load_next_tile_data_to_shift_registers();

    return ppu_ref.read_from_bus(address_to_read);
}

uint8_t Renderer::fetch_attribute_table_byte() const
{
    const uint16_t coarse_x_high_bits = ppu_ref.ppu_address.internal.coarse_x >> 2;
    const uint16_t coarse_y_high_bits = (ppu_ref.ppu_address.internal.coarse_y >> 2) << 3;
    const uint16_t nametable_bits = ppu_ref.ppu_address.internal.nametable << 10;
    const uint16_t address_to_read = first_attribute_table_start | nametable_bits | coarse_y_high_bits | coarse_x_high_bits;

    const auto attribute_quadrant_shift {calculate_attribute_shift()};
    const auto attribute_table_byte {ppu_ref.read_from_bus(address_to_read)};

    return (attribute_table_byte >> attribute_quadrant_shift) & first_two_bits_mask;
}

uint8_t Renderer::calculate_attribute_shift() const
{
    const uint16_t horizontal_half_choice = ppu_ref.ppu_address.internal.coarse_y & second_bit_mask;
    const uint16_t vertical_half_choice = ppu_ref.ppu_address.internal.coarse_x & second_bit_mask;
    const uint8_t shift = (horizontal_half_choice << 1) | vertical_half_choice;

    return shift;
}

uint8_t Renderer::fetch_tile_plane_byte(uint8_t plane_offset) const
{
    const uint16_t current_row_offset = ppu_ref.ppu_address.internal.fine_y;
    const uint16_t current_tile_offset = fetched_nametable_tile_byte * tile_column_offset;
    const uint16_t pattern_table_offset = ppu_ref.ppu_controller.flag.bg_table * second_pattern_table_offset;
    const auto address_to_read = static_cast<uint16_t>(pattern_table_offset + current_tile_offset + current_row_offset + plane_offset);

    return ppu_ref.read_from_bus(address_to_read);
}


//////////////////////////////
// Fetches helper functions //
//////////////////////////////

// https://www.nesdev.org/wiki/PPU_scrolling#Coarse_X_increment
void Renderer::coarse_x_increment_with_wrapping()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    if (ppu_ref.ppu_address.internal.coarse_x == nametable_coarse_bound) {
        ppu_ref.ppu_address.internal.coarse_x = 0x00;
        ppu_ref.ppu_address.internal.nametable ^= first_bit_mask;
    }
    else {
        ppu_ref.ppu_address.internal.coarse_x++;
    }
}

// https://www.nesdev.org/wiki/PPU_scrolling#Y_increment
void Renderer::coarse_y_increment_with_wrapping()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    if (ppu_ref.ppu_address.internal.fine_y < fine_y_max_value) {
        ppu_ref.ppu_address.internal.fine_y++;
    }
    else {
        ppu_ref.ppu_address.internal.fine_y = 0x00;

        if (ppu_ref.ppu_address.internal.coarse_y == nametable_change_to_attribute_bound) {
            ppu_ref.ppu_address.internal.coarse_y = 0x00;
            ppu_ref.ppu_address.internal.nametable ^= second_bit_mask;
        }
        else if (ppu_ref.ppu_address.internal.coarse_y == nametable_coarse_bound) {
            ppu_ref.ppu_address.internal.coarse_y = 0x00;
        }
        else {
            ppu_ref.ppu_address.internal.coarse_y++;
        }
    }
}

// https://www.nesdev.org/wiki/PPU_scrolling#At_dot_257_of_each_scanline
void Renderer::copy_horizontal_scroll_to_address()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    const uint8_t horizontal_nametable_bit = ppu_ref.ppu_scroll.internal.nametable & first_bit_mask;

    ppu_ref.ppu_address.internal.coarse_x = ppu_ref.ppu_scroll.internal.coarse_x;
    ppu_ref.ppu_address.internal.nametable = (ppu_ref.ppu_scroll.internal.nametable & second_bit_mask) | horizontal_nametable_bit;
}

// https://www.nesdev.org/wiki/PPU_scrolling#During_dots_280_to_304_of_the_pre-render_scanline_(end_of_vblank)
void Renderer::copy_vertical_scroll_to_address()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    const uint8_t vertical_nametable_bit = ppu_ref.ppu_scroll.internal.nametable & second_bit_mask;

    ppu_ref.ppu_address.internal.coarse_y = ppu_ref.ppu_scroll.internal.coarse_y;
    ppu_ref.ppu_address.internal.nametable = (ppu_ref.ppu_scroll.internal.nametable & first_bit_mask) | vertical_nametable_bit;
    ppu_ref.ppu_address.internal.fine_y = ppu_ref.ppu_scroll.internal.fine_y;
}

void Renderer::load_next_tile_data_to_shift_registers()
{
    tile_data_first_shift_reg = (tile_data_first_shift_reg & upper_byte_mask) | fetched_tile_first_plane_byte;
    tile_data_second_shift_reg = (tile_data_second_shift_reg & upper_byte_mask) | fetched_tile_second_plane_byte;
}

void Renderer::move_shift_registers()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    tile_data_first_shift_reg <<= 1;
    tile_data_second_shift_reg <<= 1;
}
