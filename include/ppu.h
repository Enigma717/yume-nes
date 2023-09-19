#pragma once


#include <cstdint>
#include <vector>


namespace
{
    constexpr size_t oam_size {64};
}


class PPU {
public:
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
        } flag;

        uint16_t word {0x0000};
    };

    struct OAMEntry {
        uint8_t position_y {0x00};
        uint8_t tile_index {0x00};
        uint8_t attributes {0x00};
        uint8_t position_x {0x00};
    };

    Controller ppu_ctrl {};
    Mask       ppu_mask {};
    Status     ppu_status {};
    uint8_t    oam_address {0x00};
    uint8_t    oam_data {0x00};
    Loopy      ppu_scroll {};
    Loopy      ppu_addr {};
    uint8_t    ppu_data {0x00};
    uint8_t    oam_mdma {0x00};

    std::vector<OAMEntry> oam {std::vector<OAMEntry>(oam_size)};
};
