#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>


namespace PPUConsts
{
    constexpr size_t oam_size {64};
    constexpr size_t sprites_tiles_size {512};
    constexpr size_t nametables_size {2048};
    constexpr size_t palettes_ram_size {32};
    constexpr size_t rendered_pixels_count {89342};

}

class Cartridge;

using CartridgePtr = std::weak_ptr<Cartridge>;


class PPU {
public:
    PPU();

    union Controller {
        struct {
            uint8_t nametable      : 2;
            uint8_t vram_increment : 1;
            uint8_t sprite_table   : 1;
            uint8_t bg_table       : 1;
            uint8_t sprite_size    : 1;
            uint8_t master_slave   : 1;
            uint8_t generate_nmi   : 1;
        } flag;

        uint8_t word {0x00};
    };

    union Mask {
        struct {
            uint8_t greyscale            : 1;
            uint8_t show_background_left : 1;
            uint8_t show_sprites_left    : 1;
            uint8_t show_background      : 1;
            uint8_t show_sprites         : 1;
            uint8_t emphasize_red        : 1;
            uint8_t emphasize_green      : 1;
            uint8_t emphasize_blue       : 1;
        } flag;

        uint8_t word {0x00};
    };

    union Status {
        struct {
            uint8_t                 : 5;
            uint8_t sprite_overflow : 1;
            uint8_t sprite_zero_hit : 1;
            uint8_t vblank_start    : 1;
        } flag;

        uint8_t word {0xA0};
    };

    union Loopy {
        struct {
            uint8_t coarse_x  : 5;
            uint8_t coarse_y  : 5;
            uint8_t nametable : 2;
            uint8_t fine_y    : 3;
            uint8_t           : 1;
        } internal;

        uint16_t word {0x0000};
    };

    union FineX {
        struct {
            uint8_t position : 3;
            uint8_t          : 5;
        } internal;

        uint8_t word {0x00};
    };

    Controller ppu_controller {};
    Mask       ppu_mask {};
    Status     ppu_status {};
    uint8_t    oam_address {0x00};
    uint8_t    oam_data {0x00};
    Loopy      ppu_scroll {};
    Loopy      ppu_address {};
    uint8_t    ppu_data {0x00};
    uint8_t    oam_mdma {0x00};

    FineX    fine_x {};
    bool     second_address_write_latch {false};
    uint8_t  ppu_data_read_buffer {0x00};

    int  current_cycle {0};
    int  current_scanline {0};
    bool force_nmi_in_cpu {false};

    struct OAMEntry {
        uint8_t position_y {0x00};
        uint8_t tile_index {0x00};
        uint8_t attributes {0x00};
        uint8_t position_x {0x00};
    };

    struct Pixel {
        sf::RectangleShape sfml_pixel;
        int color_index {0};
    };

    struct SpriteTile {
        std::vector<Pixel> pixels;
    };

    std::vector<OAMEntry>   oam              {std::vector<OAMEntry>(PPUConsts::oam_size)};
    std::vector<SpriteTile> sprites_tiles    {std::vector<SpriteTile>(PPUConsts::sprites_tiles_size)};
    std::vector<uint8_t>    nametables       {std::vector<uint8_t>(PPUConsts::nametables_size)};
    std::vector<uint8_t>    palettes_ram     {std::vector<uint8_t>(PPUConsts::palettes_ram_size)};
    std::vector<sf::RectangleShape> pixels_to_render {std::vector<sf::RectangleShape>(PPUConsts::rendered_pixels_count)};

    sf::RenderWindow app_screen {};


    void connect_with_cartridge(std::shared_ptr<Cartridge> cartridge);
    void prepare_sprites_tiles_memory();

    void    memory_write(uint16_t address, uint8_t data);
    uint8_t memory_read(uint16_t address) const;

    void    handle_write_from_cpu(uint16_t address, uint8_t data);
    uint8_t handle_read_from_cpu(uint16_t address);

    void perform_cycle(bool debug_mode = false);
    void dispatch_rendering_mode();
    void render_pre_render_scanline();
    void render_visible_scanline();
    void render_vblank_scanline();
    void process_pixel_rendering();


private:
    CartridgePtr cartridge_ptr {};

    enum class RenderingMode {
        pre_render_scanline,
        visible_scanline,
        post_render_scanline,
        vblank_scanline
    };

    RenderingMode rendering_mode {RenderingMode::pre_render_scanline};

    uint8_t fetched_nametable_tile_byte {0x00};
    uint8_t fetched_attribute_table_byte {0x00};
    uint8_t fetched_tile_first_plane_byte {0x00};
    uint8_t fetched_tile_second_plane_byte {0x00};

    uint16_t tile_data_first_shift_reg {0x0000};
    uint16_t tile_data_second_shift_reg {0x0000};
    uint16_t data_multiplexer {0x0000};


    void log_debug_info() const;
    void log_debug_palettes_ram_data() const;
    void log_debug_register_write(const std::string& register_name) const;
    void log_debug_register_read(const std::string& register_name) const;

    void prepare_pattern_table(int pattern_table_number);

    void    process_rendering_fetches();
    uint8_t fetch_nametable_tile_byte();
    uint8_t fetch_attribute_table_byte();
    uint8_t calculate_attribute_shift();
    uint8_t fetch_tile_plane_byte(uint8_t plane_offset = 0x00);

    void coarse_x_increment_with_wrapping();
    void coarse_y_increment_with_wrapping();
    void copy_horizontal_scroll_to_address();
    void copy_vertical_scroll_to_address();
    void load_next_tile_data_to_shift_registers();
    void move_shift_registers();

    uint16_t normalize_nametables_address(uint16_t address) const;
    uint16_t normalize_palettes_address(uint16_t address) const;
    bool     check_for_palette_mirroring(uint16_t address) const;

    void    send_write_to_mapper_chr_rom(uint16_t address, uint8_t data) const;
    uint8_t send_read_to_mapper_chr_rom(uint16_t address) const;

    void    process_nametables_write(uint16_t address, uint8_t data);
    uint8_t process_nametables_read(uint16_t address) const;

    void    process_palettes_memory_write(uint16_t address, uint8_t data);
    uint8_t process_palettes_memory_read(uint16_t address) const;

    void    process_ppu_controller_write(uint8_t data);
    void    process_ppu_mask_write(uint8_t data);
    void    process_ppu_scroll_write(uint8_t data);
    void    process_ppu_address_write(uint8_t data);
    void    process_ppu_data_write(uint8_t data);

    uint8_t process_ppu_status_read();
    uint8_t process_ppu_data_read();

    void increment_vram_address();
};


namespace PPUColors
{
    static const std::vector<sf::Color> available_colors {
        {0x7C, 0x7C, 0x7C}, {0x00, 0x00, 0xFC}, {0x00, 0x00, 0xBC}, {0x44, 0x28, 0xBC},
        {0x94, 0x00, 0x84}, {0xA8, 0x00, 0x20}, {0xA8, 0x10, 0x00}, {0x88, 0x14, 0x00},
        {0x50, 0x30, 0x00}, {0x00, 0x78, 0x00}, {0x00, 0x68, 0x00}, {0x00, 0x58, 0x00},
        {0x00, 0x40, 0x58}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00},
        {0xBC, 0xBC, 0xBC}, {0x00, 0x78, 0xF8}, {0x00, 0x58, 0xF8}, {0x68, 0x44, 0xFC},
        {0xD8, 0x00, 0xCC}, {0xE4, 0x00, 0x58}, {0xF8, 0x38, 0x00}, {0xE4, 0x5C, 0x10},
        {0xAC, 0x7C, 0x00}, {0x00, 0xB8, 0x00}, {0x00, 0xA8, 0x00}, {0x00, 0xA8, 0x44},
        {0x00, 0x88, 0x88}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00},
        {0xF8, 0xF8, 0xF8}, {0x3C, 0xBC, 0xFC}, {0x68, 0x88, 0xFC}, {0x98, 0x78, 0xF8},
        {0xF8, 0x78, 0xF8}, {0xF8, 0x58, 0x98}, {0xF8, 0x78, 0x58}, {0xFC, 0xA0, 0x44},
        {0xF8, 0xB8, 0x00}, {0xB8, 0xF8, 0x18}, {0x58, 0xD8, 0x54}, {0x58, 0xF8, 0x98},
        {0x00, 0xE8, 0xD8}, {0x78, 0x78, 0x78}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00},
        {0xFC, 0xFC, 0xFC}, {0xA4, 0xE4, 0xFC}, {0xB8, 0xB8, 0xF8}, {0xD8, 0xB8, 0xF8},
        {0xF8, 0xB8, 0xF8}, {0xF8, 0xA4, 0xC0}, {0xF0, 0xD0, 0xB0}, {0xFC, 0xE0, 0xA8},
        {0xF8, 0xD8, 0x78}, {0xD8, 0xF8, 0x78}, {0xB8, 0xF8, 0xB8}, {0xB8, 0xF8, 0xD8},
        {0x00, 0xFC, 0xFC}, {0xF8, 0xD8, 0xF8}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}
    };
}
