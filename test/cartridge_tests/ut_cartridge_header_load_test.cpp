#include "./cartridge_tests.h"

#include "../test_main.h"
#include "../../include/cartridge.h"


void test_loading_correct_nestest_header()
{
    Cartridge cartridge;
    CartridgeContents target_header {0x4E, 0x45, 0x53, 0x1A, 0x01, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    cartridge.dump_cartridge_into_vector("./cartridge_tests/roms/nestest.nes");
    cartridge.load_header();

    MY_ASSERT(cartridge.header == target_header);
}


void ut_cartridge_header_load_test()
{
    TEST_SET;

    test_loading_correct_nestest_header();
}
