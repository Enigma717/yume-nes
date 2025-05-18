#pragma once

#include "./ppu_bus.h"
#include "./renderer.h"

class PPU {
public:
    PPU();

    void connect_bus_with_cartridge(std::shared_ptr<Cartridge> cartridge);
    void perform_cycle(bool debug_mode = false);
    void render_whole_frame();

    void handle_register_write_from_cpu(std::uint16_t address, std::uint8_t data);
    std::uint8_t handle_register_read_from_cpu(std::uint16_t address);

    void log_debug_info() const;

    sf::RenderWindow app_screen {};
    bool force_nmi_in_cpu {false};

private:
    void write_to_bus(std::uint16_t address, std::uint8_t data);
    std::uint8_t read_from_bus(std::uint16_t address) const;

    void increment_vram_address();
    void process_ppu_controller_write(std::uint8_t data);
    void process_ppu_mask_write(std::uint8_t data);
    void process_ppu_scroll_write(std::uint8_t data);
    void process_ppu_address_write(std::uint8_t data);
    void process_ppu_data_write(std::uint8_t data);
    std::uint8_t process_ppu_status_read();
    std::uint8_t process_ppu_data_read();

    PPUBus memory_bus {};
    Renderer renderer;

    union Controller {
        struct {
            std::uint8_t nametable      : 2;
            std::uint8_t vram_increment : 1;
            std::uint8_t sprite_table   : 1;
            std::uint8_t bg_table       : 1;
            std::uint8_t sprite_size    : 1;
            std::uint8_t master_slave   : 1;
            std::uint8_t generate_nmi   : 1;
        } flag;

        std::uint8_t word {0x00u};
    };

    union Mask {
        struct {
            std::uint8_t greyscale            : 1;
            std::uint8_t show_background_left : 1;
            std::uint8_t show_sprites_left    : 1;
            std::uint8_t show_background      : 1;
            std::uint8_t show_sprites         : 1;
            std::uint8_t emphasize_red        : 1;
            std::uint8_t emphasize_green      : 1;
            std::uint8_t emphasize_blue       : 1;
        } flag;

        std::uint8_t word {0x00u};
    };

    union Status {
        struct {
            std::uint8_t                 : 5;
            std::uint8_t sprite_overflow : 1;
            std::uint8_t sprite_zero_hit : 1;
            std::uint8_t vblank_start    : 1;
        } flag;

        std::uint8_t word {0xA0u};
    };

    union Loopy {
        struct {
            std::uint16_t coarse_x  : 5;
            std::uint16_t coarse_y  : 5;
            std::uint16_t nametable : 2;
            std::uint16_t fine_y    : 3;
            std::uint16_t           : 1;
        } bits;

        std::uint16_t word {0x0000u};
    };

    union FineX {
        struct {
            std::uint8_t position : 3;
            std::uint8_t          : 5;
        } bits;

        std::uint8_t word {0x00u};
    };

    Controller ppu_controller {};
    Mask ppu_mask {};
    Status  ppu_status {};
    std::uint8_t oam_address {0x00u};
    std::uint8_t oam_data {0x00u};
    Loopy ppu_scroll {};
    Loopy ppu_address {};
    std::uint8_t ppu_data {0x00u};
    std::uint8_t oam_dma {0x00u};

    FineX fine_x {};
    sf::VertexBuffer frame_render_buffer {};
    bool second_address_write_latch {false};
    std::uint8_t ppu_data_read_buffer {0x00u};

    int current_cycle {0};
    int current_scanline {0};

    friend class Renderer;
};
