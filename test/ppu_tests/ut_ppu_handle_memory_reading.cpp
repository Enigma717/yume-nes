#include "./ppu_tests.h"

#include "../test_main.h"
#include "../../include/system.h"


void test_read_from_pattern_table()
{
    System nes;

    uint8_t zero_sprite_first_plane_first_byte {0b0011'1110};
    uint16_t zero_sprite_address_start {0x0300};

    nes.cartridge->load_cartridge("./cartridge_tests/roms/nestest.nes");
    const auto read_byte {nes.ppu.memory_read(zero_sprite_address_start)};

    MY_ASSERT(read_byte == zero_sprite_first_plane_first_byte);
}


void ut_ppu_handle_memory_reading()
{
    TEST_SET;

    test_read_from_pattern_table();
}
