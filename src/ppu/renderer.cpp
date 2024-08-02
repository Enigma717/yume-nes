#include "../../include/ppu/ppu.h"

namespace
{
    constexpr std::size_t fetching_subcycle_size {8uz};
    constexpr std::size_t pixel_size {1uz};
    constexpr std::size_t vertices_in_pixel {4uz};

    constexpr std::size_t visible_pixels_count {61440uz};
    constexpr std::size_t visible_screen_height {240uz};
    constexpr std::size_t visible_screen_width {256};

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

    constexpr std::uint8_t fine_y_max_value {0x07u};
    constexpr std::uint8_t nametable_change_to_attribute_bound {0x1Du};
    constexpr std::uint8_t nametable_coarse_bound {0x1Fu};
    constexpr std::uint8_t pixel_color_lsb_default_shift {0x0Fu};
    constexpr std::uint8_t pixel_color_msb_default_shift {0x0Eu};

    constexpr std::uint8_t first_bit_mask {0b0000'0001u};
    constexpr std::uint8_t first_two_bits_mask {0b0000'0011u};
    constexpr std::uint8_t second_bit_mask {0b0000'0010u};

    constexpr std::uint16_t second_pattern_table_offset {0x1000u};
    constexpr std::uint16_t second_plane_offset {0x0008u};
    constexpr std::uint16_t tile_column_offset {0x0010u};

    constexpr std::uint16_t first_attribute_table_start {0x23C0u};
    constexpr std::uint16_t nametables_space_start {0x2000u};
    constexpr std::uint16_t palettes_space_start {0x3F00u};

    constexpr std::uint16_t loopy_no_fine_y_mask {0x0FFFu};
    constexpr std::uint16_t multiplexer_default_pointer {0b1000'0000'0000'0000u};
    constexpr std::uint16_t upper_byte_mask {0xFF00u};


    bool check_for_pixel_within_visible_screen(std::size_t x_coord, std::size_t y_coord)
    {
        return x_coord < visible_screen_width && y_coord < visible_screen_height;
    }
}

Renderer::Renderer(PPU& ppu_ref) : ppu_ref{ppu_ref}
{
    frame_buffer.resize(visible_pixels_count * vertices_in_pixel);
    frame_buffer.setPrimitiveType(sf::Quads);

    for (std::size_t i {0uz}; i < visible_screen_height; i++) {
        for (std::size_t j {0uz}; j < visible_screen_width; j++) {
            const auto index {(i * visible_screen_width + j) * vertices_in_pixel};
            const auto base_x_coord {static_cast<float>(j * pixel_size)};
            const auto base_y_coord {static_cast<float>(i * pixel_size)};

            std::array<sf::Vector2f, vertices_in_pixel> coords {
                sf::Vector2f{base_x_coord, base_y_coord},
                sf::Vector2f{base_x_coord + pixel_size, base_y_coord},
                sf::Vector2f{base_x_coord + pixel_size, base_y_coord + pixel_size},
                sf::Vector2f{base_x_coord, base_y_coord + pixel_size}
            };

            for (std::size_t k {0uz}; k < vertices_in_pixel; k++)
                frame_buffer[index + k].position = coords[k];
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
    const auto visible_section {
        ppu_ref.current_scanline >= 0 &&
        ppu_ref.current_scanline < post_render_scanline_number};

    const auto post_render_section {
        ppu_ref.current_scanline == post_render_scanline_number};

    const auto vblank_section {
        ppu_ref.current_scanline > post_render_scanline_number &&
        ppu_ref.current_scanline < pre_render_scanline_number};

    const auto pre_render_section {
        ppu_ref.current_scanline == pre_render_scanline_number};

    if (visible_section)
        rendering_mode = RenderingMode::visible_scanline;
    else if (post_render_section)
        rendering_mode = RenderingMode::post_render_scanline;
    else if (vblank_section)
        rendering_mode = RenderingMode::vblank_scanline;
    else if (pre_render_section)
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
        ppu_ref.ppu_status.word = 0x00u;

    render_visible_scanline();

    if (ppu_ref.current_cycle > vertical_scroll_copy_cycle_start
        && ppu_ref.current_cycle < vertical_scroll_copy_cycle_end)
        copy_vertical_scroll_to_address();
}

void Renderer::render_visible_scanline()
{
    const auto is_after_first_cycle {ppu_ref.current_cycle > 0};
    const auto is_horizontal_copy_cycle{
        ppu_ref.current_cycle < horizontal_scroll_copy_cycle};
    const auto is_fetching_next_tile {
        ppu_ref.current_cycle > next_tile_fetches_cycle_start &&
        ppu_ref.current_cycle < next_tile_fetches_cycle_end};

    if ((is_after_first_cycle && is_horizontal_copy_cycle) || is_fetching_next_tile)
        process_rendering_fetches();

    if (ppu_ref.current_cycle == visible_screen_width)
        coarse_y_increment_with_wrapping();

    if (ppu_ref.current_cycle == horizontal_scroll_copy_cycle)
        copy_horizontal_scroll_to_address();


    const auto is_fetch_cycle_finished {
        ppu_ref.current_cycle == next_tile_fetches_cycle_end};
    const auto is_garbage_fetch_cycle {
        ppu_ref.current_cycle == garbage_nametable_fetch_cycle};

    if (is_fetch_cycle_finished || is_garbage_fetch_cycle)
        fetched_nametable_tile_byte = fetch_nametable_tile_byte_with_shifters_load();
}

void Renderer::render_vblank_scanline()
{
    if (ppu_ref.current_scanline == vblank_scanline_number
        && ppu_ref.current_cycle == set_vblank_flag_cycle) {
        ppu_ref.ppu_status.flag.vblank_start = 1;

        if (ppu_ref.ppu_controller.flag.generate_nmi)
            ppu_ref.force_nmi_in_cpu = true;
    }
}

void Renderer::process_pixel_rendering()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    data_multiplexer = multiplexer_default_pointer >> ppu_ref.fine_x.bits.position;

    const auto pixel_color_lsb {
        static_cast<std::uint8_t>(
            (tile_data_first_shift_reg & data_multiplexer) >>
            (pixel_color_lsb_default_shift - ppu_ref.fine_x.bits.position))};
    const auto pixel_color_msb {
        static_cast<std::uint8_t>(
            (tile_data_second_shift_reg & data_multiplexer) >>
            (pixel_color_msb_default_shift - ppu_ref.fine_x.bits.position))};
    const auto pixel_color {
        static_cast<std::uint8_t>(pixel_color_msb | pixel_color_lsb)};

    const auto address_to_read {
        static_cast<std::uint16_t>(
            palettes_space_start + (fetched_attribute_table_byte << 2) + pixel_color)};

    const auto& final_color {
        PPUColors::available_colors[ppu_ref.read_from_bus(address_to_read)]};

    const auto x_coord {static_cast<std::size_t>(ppu_ref.current_cycle - 1)};
    const auto y_coord {static_cast<std::size_t>(ppu_ref.current_scanline)};

    if (check_for_pixel_within_visible_screen(x_coord, y_coord)) {
        const auto pixel_index {(y_coord * visible_screen_width + x_coord) * 4};

        for (std::size_t i {0uz}; i < vertices_in_pixel; i++)
            frame_buffer[pixel_index + i].color = final_color;
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

std::uint8_t Renderer::fetch_nametable_tile_byte_with_shifters_load()
{
    const std::uint16_t address_to_read {
        static_cast<std::uint16_t>(
            nametables_space_start | (ppu_ref.ppu_address.word & loopy_no_fine_y_mask))};
    load_next_tile_data_to_shift_registers();

    return ppu_ref.read_from_bus(address_to_read);
}

std::uint8_t Renderer::fetch_attribute_table_byte() const
{
    const auto coarse_x_high_bits {
        static_cast<std::uint16_t>(ppu_ref.ppu_address.bits.coarse_x >> 2)};
    const auto coarse_y_high_bits {
        static_cast<std::uint16_t>((ppu_ref.ppu_address.bits.coarse_y >> 2) << 3)};
    const auto nametable_bits {
        static_cast<std::uint16_t>(ppu_ref.ppu_address.bits.nametable << 10)};
    const auto address_to_read {
        static_cast<std::uint16_t>(
            first_attribute_table_start | nametable_bits | coarse_y_high_bits | coarse_x_high_bits)};

    const auto attribute_quadrant_shift {calculate_attribute_shift()};
    const auto attribute_table_byte {ppu_ref.read_from_bus(address_to_read)};

    return (attribute_table_byte >> attribute_quadrant_shift) & first_two_bits_mask;
}

std::uint8_t Renderer::calculate_attribute_shift() const
{
    const auto horizontal_half_choice {
        static_cast<std::uint16_t>(ppu_ref.ppu_address.bits.coarse_y & second_bit_mask)};
    const auto vertical_half_choice {
        static_cast<std::uint16_t>(ppu_ref.ppu_address.bits.coarse_x & second_bit_mask)};

    return (horizontal_half_choice << 1) | vertical_half_choice;
}

std::uint8_t Renderer::fetch_tile_plane_byte(std::uint8_t plane_offset) const
{
    const auto current_row_offset{ppu_ref.ppu_address.bits.fine_y};
    const auto current_tile_offset {
        static_cast<std::uint16_t>(fetched_nametable_tile_byte * tile_column_offset)};
    const auto pattern_table_offset {
        static_cast<std::uint16_t>(
            ppu_ref.ppu_controller.flag.bg_table * second_pattern_table_offset)};
    const auto address_to_read {
        static_cast<std::uint16_t>(
            pattern_table_offset + current_tile_offset + current_row_offset + plane_offset)};

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

    if (ppu_ref.ppu_address.bits.coarse_x == nametable_coarse_bound) {
        ppu_ref.ppu_address.bits.coarse_x = 0x00;
        ppu_ref.ppu_address.bits.nametable ^= first_bit_mask;
    }
    else {
        ppu_ref.ppu_address.bits.coarse_x++;
    }
}

// https://www.nesdev.org/wiki/PPU_scrolling#Y_increment
void Renderer::coarse_y_increment_with_wrapping()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    if (ppu_ref.ppu_address.bits.fine_y < fine_y_max_value) {
        ppu_ref.ppu_address.bits.fine_y++;
    }
    else {
        ppu_ref.ppu_address.bits.fine_y = 0x00u;

        if (ppu_ref.ppu_address.bits.coarse_y == nametable_change_to_attribute_bound) {
            ppu_ref.ppu_address.bits.coarse_y = 0x00u;
            ppu_ref.ppu_address.bits.nametable ^= second_bit_mask;
        }
        else if (ppu_ref.ppu_address.bits.coarse_y == nametable_coarse_bound) {
            ppu_ref.ppu_address.bits.coarse_y = 0x00u;
        }
        else {
            ppu_ref.ppu_address.bits.coarse_y++;
        }
    }
}

// https://www.nesdev.org/wiki/PPU_scrolling#At_dot_257_of_each_scanline
void Renderer::copy_horizontal_scroll_to_address()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    const auto horizontal_nametable_bit {
        static_cast<std::uint8_t>(ppu_ref.ppu_scroll.bits.nametable & first_bit_mask)};

    ppu_ref.ppu_address.bits.coarse_x = ppu_ref.ppu_scroll.bits.coarse_x;
    ppu_ref.ppu_address.bits.nametable =
        (ppu_ref.ppu_scroll.bits.nametable & second_bit_mask) | horizontal_nametable_bit;
}

// https://www.nesdev.org/wiki/PPU_scrolling#During_dots_280_to_304_of_the_pre-render_scanline_(end_of_vblank)
void Renderer::copy_vertical_scroll_to_address()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    const auto vertical_nametable_bit {
        static_cast<std::uint8_t>(ppu_ref.ppu_scroll.bits.nametable & second_bit_mask)};

    ppu_ref.ppu_address.bits.coarse_y = ppu_ref.ppu_scroll.bits.coarse_y;
    ppu_ref.ppu_address.bits.nametable =
        (ppu_ref.ppu_scroll.bits.nametable & first_bit_mask) | vertical_nametable_bit;
    ppu_ref.ppu_address.bits.fine_y = ppu_ref.ppu_scroll.bits.fine_y;
}

void Renderer::load_next_tile_data_to_shift_registers()
{
    tile_data_first_shift_reg =
        (tile_data_first_shift_reg & upper_byte_mask) | fetched_tile_first_plane_byte;
    tile_data_second_shift_reg =
        (tile_data_second_shift_reg & upper_byte_mask) | fetched_tile_second_plane_byte;
}

void Renderer::move_shift_registers()
{
    if (ppu_ref.ppu_mask.flag.show_background == 0)
        return;

    tile_data_first_shift_reg <<= 1;
    tile_data_second_shift_reg <<= 1;
}
