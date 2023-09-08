#include "./cartridge_tests.h"

#include "../test_main.h"
#include "../../include/cartridge.h"


namespace
{
    CartridgeContents nes_logo {0x4E, 0x45, 0x53, 0x1A};
}

void test_decoding_nes_logo()
{
    Cartridge cartridge;
    CartridgeContents correct_nes_logo {0x4E, 0x45, 0x53, 0x1A};

    cartridge.load_cartridge("./cartridge_tests/roms/nestest.nes");
    CartridgeContents logo_in_header {cartridge.header.begin(), cartridge.header.begin() + 4};

    MY_ASSERT(logo_in_header == correct_nes_logo);
}

void test_decoding_prg_rom_banks_count()
{
    Cartridge cartridge;
    auto target_banks_count {3};

    cartridge.load_cartridge("./cartridge_tests/roms/dummy_header.nes");

    MY_ASSERT(cartridge.mapper.prg_rom_banks_count == target_banks_count);
}

void test_decoding_chr_rom_banks_count()
{
    Cartridge cartridge;
    auto target_banks_count {4};

    cartridge.load_cartridge("./cartridge_tests/roms/dummy_header.nes");

    MY_ASSERT(cartridge.mapper.chr_rom_banks_count == target_banks_count);
}

void test_decoding_mapper_id()
{
    Cartridge cartridge;
    auto target_mapper_id {105};

    cartridge.load_cartridge("./cartridge_tests/roms/dummy_header.nes");

    MY_ASSERT(cartridge.current_mapper_id == target_mapper_id);
}

void test_decoding_trainer_presence()
{
    Cartridge cartridge;
    auto target_trainer_presence {true};

    cartridge.load_cartridge("./cartridge_tests/roms/dummy_header.nes");

    MY_ASSERT(cartridge.mapper.trainer_presence == target_trainer_presence);
}

void test_decoding_mirroring_mode()
{
    Cartridge cartridge;
    auto target_mirroring_mode {Cartridge::MirroringType::vertical};

    cartridge.load_cartridge("./cartridge_tests/roms/dummy_header.nes");

    MY_ASSERT(cartridge.mirroring_mode == target_mirroring_mode);
}

void test_prg_rom_memory_resizing()
{
    Cartridge cartridge;
    auto target_prg_rom_size {MapperConsts::prg_rom_bank_size * 3};

    cartridge.load_cartridge("./cartridge_tests/roms/dummy_header.nes");

    MY_ASSERT(cartridge.mapper.prg_rom_memory.size() == target_prg_rom_size);
}

void test_chr_rom_memory_resizing()
{
    Cartridge cartridge;
    auto target_chr_rom_size {MapperConsts::chr_rom_bank_size * 4};

    cartridge.load_cartridge("./cartridge_tests/roms/dummy_header.nes");

    MY_ASSERT(cartridge.mapper.chr_rom_memory.size() == target_chr_rom_size);
}


void ut_cartridge_header_decoding()
{
    TEST_SET;

    test_decoding_nes_logo();
    test_decoding_prg_rom_banks_count();
    test_decoding_chr_rom_banks_count();
    test_decoding_mapper_id();
    test_decoding_trainer_presence();
    test_decoding_mirroring_mode();
    test_prg_rom_memory_resizing();
    test_chr_rom_memory_resizing();
}
