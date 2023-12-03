#pragma once

#include "./ppu_bus.h"
#include "./renderer.h"


class PPU {
public:
    PPU();


    sf::RenderWindow app_screen {};
    bool force_nmi_in_cpu {false};


    void connect_bus_with_cartridge(std::shared_ptr<Cartridge> cartridge);
    void perform_cycle(bool debug_mode = false);
    void render_whole_frame();

    void    handle_register_write_from_cpu(uint16_t address, uint8_t data);
    uint8_t handle_register_read_from_cpu(uint16_t address);

    void log_debug_info() const;

private:
    PPUBus memory_bus {};
    Renderer renderer;

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
            uint16_t coarse_x  : 5;
            uint16_t coarse_y  : 5;
            uint16_t nametable : 2;
            uint16_t fine_y    : 3;
            uint16_t           : 1;
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

    FineX   fine_x {};
    bool    second_address_write_latch {false};
    uint8_t ppu_data_read_buffer {0x00};

    int  current_cycle {0};
    int  current_scanline {0};


    void    write_to_bus(uint16_t address, uint8_t data);
    uint8_t read_from_bus(uint16_t address) const;

    void increment_vram_address();
    void process_ppu_controller_write(uint8_t data);
    void process_ppu_mask_write(uint8_t data);
    void process_ppu_scroll_write(uint8_t data);
    void process_ppu_address_write(uint8_t data);
    void process_ppu_data_write(uint8_t data);
    uint8_t process_ppu_status_read();
    uint8_t process_ppu_data_read();


    friend class Renderer;
};
